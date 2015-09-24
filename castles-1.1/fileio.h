! fileio.h
! Initial book I/O.

#ifndef FAST_BOOK;
[ load_file ptr size name  i;
	@erase_window 0;
	print "^I'm about to try and load a file.
		Your interpreter may prompt you for the filename; you're
		strongly recommended just to press RETURN and accept it.^
		^";
	@restore ptr size name -> i;
	@erase_window 0;
	return i;
];

[ save_file ptr size name i;
	@erase_window 0;
	print "^I'm about to try and save a file.
		Your interpreter may prompt you for the filename; you're
		strongly recommended just to press RETURN and accept it.^
		^";
	@save ptr size name -> i;
	@erase_window 0;
	return i;
];
#endif;

! Display something while the book is loaded.

[ _load_book_progress xp i;
	if (i && (i % 100))
		return;
	print "[", i, "] ";
	flush_output();
];

! The name of the book file.

#ifndef FAST_BOOK;
array bookfilename string "book";
#endif;

! These stubs are used by the C code to load and save the book.

[ _load_book_from_file xp bookptr booksize;
#ifdef FAST_BOOK;
	_make_book_from_table(xp, bookptr, booksize);
#ifnot;
	return load_file(bookptr, booksize, bookfilename);
#endif;
];

[ _save_book_to_file xp bookptr booksize;
#ifndef FAST_BOOK;
	return save_file(bookptr, booksize, bookfilename);
#endif;
];

