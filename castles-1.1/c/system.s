! Z-machine syscall interface.

! --- File I/O --------------------------------------------------------------

! The Z-machine doesn't do files (in any way useful to C). We support exactly
! four file descriptors:
!  0: the keyboard
!  1: the screen
!  2: equivalent to 1
!  3: the pseudo-file (if configured)

#ifdef WANT_PSEUDO_FILE;
! The pseudo-file is always stored as an array of packed strings. Because C
! wants to read it byte by byte, we need to unpack each line into a temporary
! buffer before use. This function loads the next line in the file into the
! buffer.

global stdio_lineptr = 0;	! Pointer into array of packed strings
global stdio_charptr;		! Pointer into line buffer

[ load_line  l;
	! Run out of data?

	if (stdio_lineptr-->0 == 0)
		return -1;
	
	! Otherwise, unpack the line being pointed at into the line buffer.

	@output_stream 3 __data_buffer;
	print (string) stdio_lineptr-->0;
	@output_stream -3;

	! Reset character pointer to point to the beginning of the string
	! proper, and make sure the string is zero-terminated.

	stdio_charptr = __data_buffer+2;
	stdio_charptr->(__data_buffer-->0) = 0;

	! Move line pointer on to the next line.

	stdio_lineptr = stdio_lineptr + 2;

	return 0;
];
#endif;
	
! int read(int fd, void* buf, size_t count)
[ _read xp fd buf count  c;
	if (count == 0)
		return 0;
		
	switch (fd)
	{
		0:
			@read_char 1 -> c;
			@print_char c;
			buf->0 = c;
			return 1;

		1, 2:
			return -1;

#ifdef WANT_PSEUDO_FILE;
		3:
			if (stdio_lineptr == 0)
			{
				stdio_lineptr = __data_start;
				c = load_line();
				if (c == -1)
					return -1;
			}

			c = (stdio_charptr++)->0;
			if (c == 0)
			{
				c = load_line();
				if (c == -1)
					return -1;
				c = 10;
			}
			
			buf->0 = c;
			return 1;
#endif;

		default:
			print "[invalid fd on read()]";
			@quit;
	}
];

! int write(int fd, void* buf, size_t count)
[ _write xp fd buf count  c i;
	switch (fd)
	{
		0:
			return -1;

		1, 2:
			c = count;
			while (c > 0)
			{
				c--;
				i = (buf++)->0;
				if (i == 10)
					i = 13;
				print (char) i;
			}
			return count;

#ifdef WANT_PSEUDO_FILE;
		3:
			return -1;
#endif;

		default:
			print "[invalid fd on write()]";
			@quit;
	}
];

! int close(int fd)
[ _close xp fd;
	return 0;
];

! int open(char* filename, int flags)
[ _open xp filename flags;
#ifdef WANT_PSEUDO_FILE;
	return 3;
#ifnot;
	return -1;
#endif;
];

! --- Miscellaneous ----------------------------------------------------------

! Exits the game.

! void exit(int status)
[ _exit xp status;
	@quit;
];

! Gets the current time.

! time_t time(time_t* t)
! Remember vbcc's structure returning ABI!
[ _time xp t _retparm;
	_retparm-->0 = 0;
	_retparm-->1 = 0;
	if (t ~= 0)
	{
		t-->0 = 0;
		t-->1 = 1;
	}
];

