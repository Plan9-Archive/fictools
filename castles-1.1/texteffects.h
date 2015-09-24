! texteffects.h
! A little library dealing with text output.

[ tt s;
	font on;
	print (string) s;
	font off;
];

[ rev s;
	style reverse;
	print (string) s;
	style roman;
];

[ b s;
	style bold;
	print (string) s;
	style roman;
];

[ ul s;
	style underline;
	print (string) s;
	style roman;
];

! These routines do output flushing and delays. They rely on timed input.

[ flush_output_routine;
	return 1;
];

global timedinput = 1;

[ flush_output i;
	if (timedinput)
		@read_char 1 1 flush_output_routine -> i;
];

[ pause t;
	if (timedinput)
		@read_char 1 t flush_output_routine -> t;
];

[ TimedInputSub;
	style bold;
	if (noun)
	{
		timedinput = 1;
		print "[Now using timed input for delays and output flushing.]^";
	}
	else
	{
		timedinput = 0;
		print "[Now not using timed input for delays and output
		flushing. The animations will no longer work.]^";
	}
	style roman;
];

! Prints spaces sufficient to center something on the screen.

[ center i;
	i = (screen_width/2) - (i/2);
	while (i--)
		print " ";
];

