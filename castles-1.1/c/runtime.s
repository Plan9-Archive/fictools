! Z-machine C runtime
! Copyright (c) 2001, David Given
! All rights reserved.
!
! Permission is hereby granted, free of charge, to any person obtaining a
! copy of this software and associated documentation files (the "Software"),
! to deal in the Software without restriction, including without limitation
! the rights to use, copy, modify, merge, publish, distribute, sublicense,
! and/or sell copies of the Software, and to permit persons to whom the
! Software is furnished to do so, subject to the following conditions:
!
! The above copyright notice and this permission notice shall be included in
! all copies or substantial portions of the Software.
!
! THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
! IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
! FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
! AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
! LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
! FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
! DEALINGS IN THE SOFTWARE.

! There's an Inform bug that stops the @not opcode from assembling correctly,
! so we have to use a conventional expression.

[ __not q1;
	return ~q1;
];

! And the Z-machine doesn't have xor. How bizarre.

[ __xor q1 q2  t;
	return (q1 & (~q2)) | ((~q1) & q2);
];

! Unsigned arithmetic is hard. These helper functions do it for us.
! Thanks to Jay Foad for the algorithm for this.

[ __unsigned_div q1 q2  t;
	if (q1 == 0)
		return q1;
	else if (q2 == 0)
	{
		print "[zlibc error: division by zero in __unsigned_div]";
		return 0;
	}
	else if (q2 == 1)
		return q1;
	else if ((q1 > 0) && (q2 > 0))
		return q1/q2;
		
	! Optimisation query: given that when executing Z-machine instructions,
	! the decoding is by far the slowest part of the process, is it
	! useful to have these special cases?

	!else if ((q1-32768) < (q2-32768))
	!	return 0;

	else if (q1 == q2)
		return 1;
	else if (q2 < 0)
	{
		! If q2 is high, then the result can only be 0 or 1.
		! The only way it can be 1 is if q1 > q2.
		return ((q1-32768) > (q2-32768));
	}

	! Lose one bit of precision, and do the calculation.

	@log_shift q1 0-1 -> t;
	t = t / q2;
	@log_shift t 1 -> t;
	
	! Now multiply back out and calculate the remainder. This tells
	! us how much to modify the result by, to restore lost precision.

	!print "{", t, "}";
	!print "[", (q1 - t*q2), ">", q2, "]";

	if (((q1 - t*q2)-32768) >= (q2-32768))
		t++;
	return t;
];
	
[ __unsigned_mod q1 q2  t;
	t = __unsigned_div(q1, q2) * q2;
	return q1 - t;
];

! These wrapper functions do all the long arithmetic.

Array __long_temp1 -> 4;
Array __long_temp2 -> 4;
Array __long_temp3 -> 4;

[ __long_copy q1 z; ! z = q1
	z-->0 = q1-->0;
	z-->1 = q1-->1;
];

[ __long_loadconst z hi lo; ! z = hi.lo
	z-->0 = hi;
	z-->1 = lo;
];

[ __long_fromint z q1; ! z = (long)q1, with sign extension
	z-->1 = q1;
	if (q1 < 0)
		z-->0 = -1;
	else
		z-->0 = 0;
];

[ __long_and q1 q2 z;
	z-->0 = q1-->0 & q2-->0;
	z-->1 = q1-->1 & q2-->1;
];

[ __long_or q1 q2 z;
	z-->0 = q1-->0 | q2-->0;
	z-->1 = q1-->1 | q2-->1;
];

[ __long_asr q1 q2 z  s t;
	if ((q2-->0 ~= 0) || (((q2-->1)-32767) > (31-32767)))
	{
		! All bits shifted off; so we just propagate the sign.

		if (q2-->0 & $8000)
		{
			z-->0 = -1;
			z-->1 = -1;
		}
		else
		{
			z-->0 = 0;
			z-->1 = 0;
		}

		return;
	}
	
	q2 = -(q2-->1 & $1F);
	s = 16 + q2;

	t = q1-->1;
	@log_shift t q2 -> t;
	z-->1 = t;

	t = q1-->0;
	@log_shift t s -> t;
	z-->1 = z-->1 | t;

	t = q1-->0;
	@art_shift t q2 -> t;
	z-->0 = t;
];
	
[ __long_lsr q1 q2 z  s t;
	if ((q2-->0 ~= 0) || ((q2-->1-32767) > (31-32767)))
	{
		! All bits shifted off; the result is zero.

		z-->0 = 0;
		z-->1 = 0;
		return;
	}
	
	q2 = -(q2-->1 & $1F);
	s = 16 + q2;

	t = q1-->1;
	@log_shift t q2 -> t;
	z-->1 = t;

	t = q1-->0;
	@log_shift t s -> t;
	z-->1 = z-->1 | t;

	t = q1-->0;
	@log_shift t q2 -> t;
	z-->0 = t;
];
	
[ __long_neg q1 z  a b;
	a = ~(q1-->0);
	b = ~(q1-->1) + 1;
	if (~~b)
		a++;
	z-->0 = a;
	z-->1 = b;
];

[ __long_xor q1 q2 z  a b;
	a = q1-->0;
	b = q2-->0;
	z-->0 = (a & (~b)) | ((~a) & b);

	a = q1-->1;
	b = q2-->1;
	z-->1 = (a & (~b)) | ((~a) & b);
];

[ __long_add q1 q2 z  a b c cc;
	! Add the low word, and detect overflow.

	a = q1-->1;
	b = q2-->1;
	c = a + b;
	z-->1 = c;
	@log_shift a 0-15 -> a;
	@log_shift b 0-15 -> b;
	@log_shift c 0-15 -> c;
	cc = a;
	if ((~~a) && b && (~~c))
		cc = 1;
	else if (a && b && (~~c))
		cc = 0;

	! Add the high word, plus one if the low word overflowed.

	z-->0 = q1-->0 + q2-->0 + cc;
];

[ __long_sub q1 q2 z  a b c cc;
	! Subtract the low word, and detect overflow.

	a = q1-->1;
	b = q2-->1;
	c = a - b;
	z-->1 = c;
	@log_shift a 0-15 -> a;
	@log_shift b 0-15 -> b;
	@log_shift c 0-15 -> c;

	! Carry table:
	! a b c  c
	! 0 0 0  0
	! 0 0 1	 1
	! 0 1 0	 1
	! 0 1 1	 1
	! 1 0 0	 0
	! 1 0 1	 0
	! 1 1 0	 0
	! 1 1 1	 1

	cc = ~~a;
	if ((~~a) && (~~b) && (~~c))
		cc = 0;
	else if (a && b && c)
		cc = 1;

	! Subtract the high word, plus one if the low word overflowed.

	z-->0 = q1-->0 - q2-->0 - cc;
];

! Algorithm converted from MIPS assembly, at:
! http://www.cz3.nus.edu.sg/~wangjs/CZ101/assembly-examples/divide.s
[ __long_unsigned_divmod q1 q2 d r  r1 r2 r3 r4 count t1 t2;
	! Check for division by zero.

	if ((~~(q2-->0)) && (~~(q2-->1)))
	{
		print "[zlibc error: division by zero in __long_unsigned_divmod]";
		return 0;
	}

	count = 0;
	r1 = 0;
	r2 = 0;
	r3 = q1-->0;
	r4 = q1-->1;
	!print "[q1=", r3, " ", r4, " q2=", q2-->0, " ", q2-->1, " ";

	do {
		count++;

		! Shift r1..r4 left by one bit.

		@log_shift r4 0-15 -> t1;
		@log_shift r4 1 -> r4;

		@log_shift r3 0-15 -> t2;
		@log_shift r3 1 -> r3;
		@or r3 t1 -> r3;

		@log_shift r2 0-15 -> t1;
		@log_shift r2 1 -> r2;
		@or r2 t2 -> r2;

		@log_shift r1 1 -> r1;
		@or r1 t1 -> r1;
		
		! Subtract divisor from r1..r2.

		__long_temp3-->0 = r1;
		__long_temp3-->1 = r2;
		__long_sub(__long_temp3, q2, __long_temp3);

		! Is the remainder non-negative?

		if (__long_temp3-->0 >= 0)
		{
			! Yes. Quotient gets a one; commit subtraction.

			r1 = __long_temp3-->0;
			r2 = __long_temp3-->1;

			r4 = r4 | 1;
			!print "1";
		}
		!else print "0";
		! Otherwise the quotient gets a zero and the subtraction is not
		! committed. No operation.
	} until (count == 32);

	! Save results.

	!print " r=", r1, " ", r2;
	if (r)
	{
		r-->0 = r1;
		r-->1 = r2;
	}
	!print " d=", r3, " ", r4, "]";
	if (d)
	{
		d-->0 = r3;
		d-->1 = r4;
	}
];

[ __long_div q1 q2 z  t sign;
	! Calculate final sign, and convert parameters to unsigned.

	t = q1-->0;
	if (t < 0)
		sign = 1;
	__long_temp1-->0 = t & $7FFF;
	__long_temp1-->1 = q1-->1;

	t = q2-->0;
	if (t < 0)
		sign = ~~sign;
	__long_temp2-->0 = t & $7FFF;
	__long_temp2-->1 = q2-->1;

	! Do the actual divide.

	__long_unsigned_divmod(__long_temp1, __long_temp2, z, 0);

	! Adjust sign.

	if (sign)
		__long_neg(z);
];

[ __long_mod q1 q2 z  t sign;
	! Calculate final sign, and convert parameters to unsigned.

	t = q1-->0;
	if (t < 0)
		sign = 1;
	__long_temp1-->0 = t & $7FFF;
	__long_temp1-->1 = q1-->1;

	t = q2-->0;
	if (t < 0)
		sign = ~~sign;
	__long_temp2-->0 = t & $7FFF;
	__long_temp2-->1 = q2-->1;

	! Do the actual modulo.

	__long_unsigned_divmod(__long_temp1, __long_temp2, 0, z);

	! Adjust sign.

	if (sign)
		__long_neg(z);
];

[ __long_unsigned_div q1 q2 z;
	__long_unsigned_divmod(q1, q2, z, 0);
];

[ __long_unsigned_mod q1 q2 z;
	__long_unsigned_divmod(q1, q2, 0, z);
];

! Algorithm my own. Probably buggy (although it passes every test I've
! thrown at it).
[ __long_mul q1 q2 z  a b c d aa bb cc dd sign t;
	! What we're doing here is long multiplication in base 256; so each
	! digit is a byte.
	!
	!    A   B   C   D
	! *  A'  B'  C'  D'
	! = ---------------
	!   AD' BD' CD' DD' +
	!   BC' CC' DC'     +
	!   CB' DB'         +
	!   DA'
	!
	! We need to add up the columns, remembering to overflow into the
	! next column. (Don't forget to make everything positive.)

	if (q1->0 >= $80)
	{
		! q1 is negative.
		__long_neg(q1, __long_temp1);
		q1 = __long_temp1;
		sign = 1;
	}

	a  = q1->0;
	b  = q1->1;
	c  = q1->2;
	d  = q1->3;

	if (q2->0 >= $80)
	{
		! q2 is negative.
		__long_neg(q2, __long_temp1);
		q2 = __long_temp1;
		sign = ~~sign;
	}
	
	aa = q2->0;
	bb = q2->1;
	cc = q2->2;
	dd = q2->3;

	! D column.

	t = d*dd;
	z->3 = t;
	@log_shift t 0-8 -> t;

	! C column.

	t = t + c*dd + d*cc;
	z->2 = t;
	@log_shift t 0-8 -> t;

	! B column.
	t = t + b*dd + c*cc + d*bb;
	z->1 = t;
	@log_shift t 0-8 -> t;

	! A column.
	t = t + a*dd + b*cc + c*bb + d*aa;
	!t = t & $7F;
	z->0 = t;

	! Apply sign bit.

	if (sign)
		__long_neg(z, z);

	! LongMul can't use the same output as one of its inputs.
	!LongMul(__long_temp1, q1, q2);
	!@copy_table __long_temp1 z 4;
];

[ __long_compare q1 q2  a b;
	a = q1-->0;
	b = q2-->0;
	if (a == b)
	{
		a = q1-->1 - 32768;
		b = q2-->1 - 32768;
	}

	if (a > b)
		return 1;
	if (a < b)
		return -1;
	return 0;
];

[ __long_unsigned_compare q1 q2  a b;
	a = q1-->0 - 32768;
	b = q2-->0 - 32768;
	if (a == b)
	{
		a = q1-->1 - 32768;
		b = q2-->1 - 32768;
	}

	if (a > b)
		return 1;
	if (a < b)
		return -1;
	return 0;
];
	
! And finally, the routine that calls a C function from Inform.

Constant __c_stack_size 2048;
Array __c_stack -> __c_stack_size;

[ cinvoke func l0 l1 l2 l3 l4 l5  xp;
	xp = __c_stack + __c_stack_size;
	return func(xp, l0, l1, l2, l3, l4, l5);
];

