! chessboard.h
! The chessboard, and related objects and code.

! The chessboard.

array chessboard_array --> 64;

! Objects of this class represent the chess pieces on the board.

constant NEITHER -1;
constant BLACK 0;
constant WHITE 1;

constant KING 1;
constant QUEEN 2;
constant ROOK 3;
constant BISHOP 4;
constant KNIGHT 5;
constant PAWN 6;

constant TAB_SPACE 8;
constant RIGHT_COLUMN 47;

global cheating = 0;
global whitescore = 0;
global blackscore = 0;
global playeris = WHITE;
global game_on = 0;
global chessboard_in_status_bar = 1;
global progressx = 0;
global progressy = 0;
global winner = NEITHER;
global z_prompt = 0;
global spinner = 0;

! Prints the current player's colour.

[ BlackOrWhite caps;
	if (caps)
	{
		if (cinvoke(_MSCP_WhiteToMove))
		{
			print "White";
			return;
		}
		print "Black";
		return;
	}
	if (cinvoke(_MSCP_WhiteToMove))
	{
		print "white";
		return;
	}
	print "black";
];

! Prints a piece name.

[ DescribePiece caps sym;
	if (caps)
	{
		switch (sym)
		{
			'K', 'k': print "King";
			'Q', 'q': print "Queen"; 
			'B', 'b': print "Bishop";
			'N', 'n': print "Knight";
			'R', 'r': print "Rook";
			'P', 'p': print "Pawn";
		}
		return;
	}
	switch (sym)
	{
		'K', 'k': print "king";
		'Q', 'q': print "queen"; 
		'B', 'b': print "bishop";
		'N', 'n': print "knight";
		'R', 'r': print "rook";
		'P', 'p': print "pawn";
	}
];

! Prints a location.

[ DescribeLocation loc;
	print (char) ('A' + (loc/8));
	print (char) ('1' + (loc%8));
];

Class Chesspiece(32)
	class
		Object,
	with
		name
			'chesspiece' 'piece' 'dummy1' 'dummy2' 'dummy3',
		short_name
		[;
			print (address) self.&name-->3;
			rtrue;
		],
		plural
		[;
			self.short_name();
			print "s";
		],
		description
		[ w;
			w = self.&name-->3;
			<<Ask Genie w>>;
		],
		create
		[ c t;
			self.type = t;
			switch (t)
			{
				KING:
					self.&name-->3 = 'king';
					self.rawsymbol = 'K';

				QUEEN:
					self.&name-->3 = 'queen';
					self.rawsymbol = 'Q';

				ROOK:
					self.&name-->3 = 'rook';
					self.&name-->4 = 'castle';
					self.rawsymbol = 'R';

				BISHOP:
					self.&name-->3 = 'bishop';
					self.rawsymbol = 'B';

				KNIGHT:
					self.&name-->3 = 'knight';
					self.rawsymbol = 'N';

				PAWN:
					self.&name-->3 = 'pawn';
					self.rawsymbol = 'P';
			}

			self.colour = c;
			switch (c)
			{
				BLACK:
					self.symbol = self.rawsymbol;

				WHITE:
					self.symbol = self.rawsymbol + ('a'-'A');
			}
		],
		parse_name
		[ i;
			! Help the parser out a bit.

			if (parser_action == ##TheSame)
				if (parser_one.&name-->3 == parser_two.&name-->3)
					return -1;
				return -2;

			i = 0;
			while (NextWord() == self.&name-->3)
				i++;
			return i;
		],
		before
		[;
			Take:
				cheating++;
				switch (cheating)
				{
					1:
						"~Hey!~ the genie says sharply.
						~Leave that alone. If you want
						to move it, just move it. Don't
						pick it up.~";

					2:
						"~I've already warned you about that.~";

					3:
						"~I'm not going to tell you again.~";

					4:
						deadflag = 3;
						"~I told you.~";
				}

			Push, Pull:
				"~You have to say where you want to move it to.~";
		],
		symbol
			'#',
		rawsymbol
			'#',
		colour
			0,
		type
			0;

Object Chessboard "chessboard"
	with
		name
			'chessboard' 'board',
		description
		[;
			if (game_on && ~~chessboard_in_status_bar)
			{
				self.show_chessboard();
				rtrue;
			}

			"Like the table, it is elegant and simple. It seems to
			be made out of some kind of metal, or glass, or plastic;
			the white squares shine with a cool lunar light and the
			black squares gleam with the dark sheen of the empty
			sky.";
		],
		before
		[;
			Take, Remove, Push, Pull:
				"You can't move it. It doesn't appear to be fastened to the table, just very, very heavy.";
		],
		start_game
		[ x y;
			game_on = 1;
			cheating = 0;
			whitescore = 0;
			blackscore = 0;
			winner = NEITHER;

			cinvoke(_MSCP_NewGame);
			cinvoke(_MSCP_LoadBook);

			for (y=0: y<8: y++)
				for (x=0: x<8: x++)
					chessboard_array-->(y*8 + x) = 0;
			self.load_chessboard();

			StartDaemon(self);
		],
		stop_game
		[ x y o;
			game_on = 0;
			StopDaemon(self);
			
			for (y=0: y<8: y++)
				for (x=0: x<8: x++)
				{
					o = chessboard_array-->(y*8 + x);
					if (o)
						Chesspiece.destroy(o);
				}
		],
		load_chessboard
		[ x y o b colour;
			! Wipe our current copy of the board.

			for (y=0: y<8: y++)
				for (x=0: x<8: x++)
				{
					b = y*8 + x;
					o = chessboard_array-->b;
					if (o)
					{
						remove o;
						Chesspiece.destroy(o);
						chessboard_array-->b = 0;
					}
				}
					
			! Translate MSCP's chessboard structure into ours.
				
			b = cinvoke(_MSCP_GetChessboard);
			for (y=0: y<8: y++)
				for (x=0: x<8: x++)
				{
					o = b->(x*8 + (7-y));
					if (~~o)
						continue;
					colour = WHITE;
					if (o > 6)
					{
						o = o - 6;
						colour = BLACK;
					}
					o = Chesspiece.create(colour, o);
					move o to Chessboard;
					chessboard_array-->(y*8 + x) = o;
				}
		],
		show_chessboard
		[ r  x y o;
			font off;
			if (r)
				style reverse;
			else
				style roman;
			print "   ";
			for (x=0: x<8: x++)
				print " ", (char) (65+x), " ";
			print "^";

			for (y=0: y<8: y++)
			{
				if (r)
					style reverse;
				else
					style roman;

				print " ", (8-y), " ";
				for (x=0: x<8: x++)
				{
					if (((y*7+x) & 1) == r)
						style reverse;
					else
						style roman;

					o = chessboard_array-->(y*8+x);
					print " ";
					if (o)
						print (char) o.symbol;
					else
						print ".";
					print " ";
				}
				print "^";
			}
			if (r)
				style reverse;
			else
				style roman;
			font on;
		],
		draw_piece
		[ x y c cursor;
			@set_window 1;
			if ((y*7+x) & 1)
				style reverse;
			else
				style roman;
			x = 4 + x*3;
			y = 4 + y;
			@set_cursor y x;
			if (cursor)
				print ">", (char) c, "<";
			else
				print " ", (char) c, " ";
			@set_window 0;
			style roman;
		],
		react_before
		[ i;
			Wait:
				if (game_on && (cinvoke(_MSCP_WhiteToMove) ~= playeris))
				{
					if (chessboard_in_status_bar)
					{
						progressx = RIGHT_COLUMN;
						progressy = 8;
						@set_window 1;
						@set_cursor progressy progressx;
						style reverse;
						print "Thinking...";
						style roman;
						@set_window 0;
						flush_output();
					}
					
					i = cinvoke(_MSCP_GetComputerMove);
					cinvoke(_MSCP_AnalyseMove, i);
					cinvoke(_MSCP_MakeMove, i);
					Chessboard.change_chessboard();
					rtrue;
				}
		],
		daemon
		[ wtm;
			wtm = cinvoke(_MSCP_WhiteToMove);
			if (winner ~= NEITHER)
			{
				self.stop_game();
				if (winner == playeris)
				{
					"^The genie studies the board
					thoughtfuly, and frowns.
					~That's... not possible.~^
					^
					His lips move. ~I don't believe
					it,~ he says indignity. ~You
					shouldn't have been able to do
					that! You've won! On level ",
					cinvoke(_MSCP_GetIntelligence),
					", too!~^
					^
					He sits back and crosses his arms. ~Pah.~";
					Genie.cross = 1;
				}
				if (playeris == NEITHER)
				{
					"~There. I've won. Happy, now?~";
				}
				"~Hah!~ the genie says triumphantly.  ~Your
				puny intellect is no match for my, er, mighty
					one!  You could never beat me, mortal!
					I am the greatest champion in the
					history of...~ He goes on at some
					length. You feel depressed.";
			}

			if (wtm == playeris)
				"^~It's your move.~";
			print "^The genie studies the board thoughtfully.";

			if (~~z_prompt)
			{
				z_prompt = 1;
				style bold;
				print "^^[Type 'wait' when you're ready for the genie to move.]";
				style roman;
			}
			"";
		],
		change_chessboard
		[;
			self.load_chessboard();
			if (~~chessboard_in_status_bar)
				self.show_chessboard(0);
		],
	has
		supporter;

! Turn chessboard display on and off.

[ ChessboardSub;
	style bold;
	if (noun)
	{
		chessboard_in_status_bar = 1;
		print "[The chessboard is now being displayed in the status bar.]^";
	}
	else
	{
		chessboard_in_status_bar = 0;
		print "[The chessboard is now being displayed with the main text.]^";
	}
	style roman;
];

! Draw the status bar.

[ DrawStatusLine  x y i;
	if (game_on && chessboard_in_status_bar)
	{
		@split_window 12;
		@set_window 1;
		style reverse;
		for (y=1: y<=12: y++)
		{
			@set_cursor y 1;
			spaces (0->33-1);
		}
		@set_cursor 1 2;
		print (b) "Silicon Castles";
		@set_cursor 3 1;
		Chessboard.show_chessboard(1);
		style reverse;

		@set_cursor 3 30;
		print "K  King";
		@set_cursor 4 30;
		print "Q  Queen";
		@set_cursor 5 30;
		print "B  Bishop";
		@set_cursor 6 30;
		print "N  Knight";
		@set_cursor 7 30;
		print "R  Rook";
		@set_cursor 8 30;
		print "P  Pawn";
		@set_cursor 10 30;
		print "KQBNRP is black";
		@set_cursor 11 30;
		print "kqbnrp is white";

		@set_cursor 3 RIGHT_COLUMN;
		print "White score: ", whitescore;
		if (playeris == WHITE)
			print " (you)";
		else
			print " (the genie)";

		@set_cursor 4 RIGHT_COLUMN;
		print "Black score: ", blackscore;
		if (playeris == BLACK)
			print " (you)";
		else if (playeris == WHITE)
			print " (the genie)";
		else
			print " (also the genie)";

		@set_cursor 5 RIGHT_COLUMN;
		i = cinvoke(_MSCP_GetPly);
		print "Total ply:   ", i;

		@set_cursor 6 RIGHT_COLUMN;
		BlackOrWhite(1);
		print " to move";

		style roman;
		@set_window 0;
	}
	else
	{
		@split_window 1;
		@set_window 1;
		@set_cursor 1 1;
		style reverse;
		spaces (0->33-1);
		@set_cursor 1 2;
		print (b) "Silicon Castles";
		style roman;
		@set_window 0;
	}
];

! Ask the player whether it wants to play white, black, or neither.

[ AskPlayerWhiteOrBlack  i;
	print "~Do you want to play white?~^YES or NO >>> ";
	i = YesOrNo();
	if (i)
	{
		playeris = WHITE;
		rfalse;
	}
	else
	{
		print "^~Well, do you want to play black?~^YES or NO >>> ";
		i = YesOrNo();
		if (i)
		{
			playeris = BLACK;
			rfalse;
		}
		else
		{
			print "^He looks at you oddly. ~You want me to play both sides?~^YES or NO >>> ";
			i = YesOrNo();
			if (i)
			{
				print "^He shakes his head sadly. ~Some people.~^";
				playeris = NEITHER;
				rfalse;
			}
		}
	}
	rtrue;
];

! The user wants to play.

[ PlayGameSub  i;
	if (~~game_on)
	{
		if (Genie in Dreaming)
		{
			print "^~At last,~ the genie mutters. ";
			if (AskPlayerWhiteOrBlack())
			{
				print "^~All right, all right, I give
				up. Ask me again when you're feeling
				more serious.~";
				Genie.cross = 1;
				return;
			}

			print "^~Right,~ the genie says, and briskly pulls out a
				bundle of chess pieces from inside his saggy
				robes and lays them out on the board.^
				^
				Now you're looking at him from across the
				chessboard, he suddenly seems rather less
				ridiculous.^";
			Chessboard.start_game();
			Genie.cross = 0;
		}
		else
			"You don't have any pieces.";
	}
	else
		"~But you're already in the middle of a game.~";
];

! The user wants to set up the board.

[ LayoutBoardSub  oldcstate o c i x y;
	if (game_on)
		"^~But we're in the middle of a game.~";
	
	print "^~You want me to lay out a preset position, right?~^YES or NO >>> ";
	i = YesOrNo();
	if (~~i)
		"^~Suit yourself.~";
	print "^";
	
	if (AskPlayerWhiteOrBlack())
	{
		Genie.cross = 1;
		"^~Oh, for heaven's sake...~";
	}

	Chessboard.start_game();
	Genie.cross = 0;

	oldcstate = chessboard_in_status_bar;
	chessboard_in_status_bar = 1;
	DrawStatusLine();

	style bold;
	print "^[Use the cursor keys or 8, 6, 2 and 4 to move the cursor. Press
	a letter key to place a piece; capital letters for black, lower case
	for white. Pressing '.' will remove the piece under the cursor. Once
	you have finished, press RETURN. You can have at most 32 pieces on the
	board, although they don't have to be in legal positions (bear in mind
			the genie might get confused).]^";
	style roman;

	do {
		o = chessboard_array-->(x + y*8);
		if (o)
			c = o.symbol;
		else
			c = '.';

		Chessboard.draw_piece(x, y, c, 1);

		@read_char 1 -> i;

		Chessboard.draw_piece(x, y, c, 0);
		switch (i)
		{
			129, 153, '8': ! Up
				if (y > 0)
					y--;

			130, 147, '2': ! Down
				if (y < 7)
					y++;

			131, 149, '4': ! Left
				if (x > 0)
					x--;

			132, 151, '6': ! Right
				if (x < 7)
					x++;

			'P', 'R', 'N', 'B', 'Q', 'K',
			'p', 'r', 'n', 'b', 'q', 'k':
				! Destroy old object.
				if (o)
					Chesspiece.destroy(o);

				! Work out the new object type.

				switch (i)
				{
					'P': c = BLACK; i = PAWN;
					'R': c = BLACK; i = ROOK;
					'N': c = BLACK; i = KNIGHT;
					'B': c = BLACK; i = BISHOP;
					'Q': c = BLACK; i = QUEEN;
					'K': c = BLACK; i = KING;
					'p': c = WHITE; i = PAWN;
					'r': c = WHITE; i = ROOK;
					'n': c = WHITE; i = KNIGHT;
					'b': c = WHITE; i = BISHOP;
					'q': c = WHITE; i = QUEEN;
					'k': c = WHITE; i = KING;
				}

				! Create the new object.

				o = Chesspiece.create(c, i);
				i = 0;
				chessboard_array-->(x + y*8) = o;

			'.':
				! Destroy old object.
				if (o)
					Chesspiece.destroy(o);
				chessboard_array-->(x + y*8) = 0;

		}
	} until ((i == 13) || (i == 10));
		
	! Now our copy of the chessboard's been updated, we need to update the
	! engine's.

	c = cinvoke(_MSCP_GetChessboard);
	for (y=0: y<8: y++)
		for (x=0: x<8: x++)
		{
			o = chessboard_array-->(x + y*8);
			if (o)
			{
				i = o.type;
				if (o.colour == BLACK)
					i = i + 6;
			}
			else
				i = 0;

			c->(x*8 + (7-y)) = i;
		}
	
	chessboard_in_status_bar = oldcstate;
];

! The user's asked to make a raw algebraic move.

[ AlgebraicMoveSub i;
	! Check to see if it's the player's move.
	if (cinvoke(_MSCP_WhiteToMove) ~= playeris)
		"~It's not your move.~";

	if (noun == -1)
		"~That's not a valid move.~";
	else if (noun == -2)
		"~That can refer to more than one move.~";
	else if (noun == 0)
		"~That's not a valid move.~";
	cinvoke(_MSCP_AnalyseMove, noun);
	cinvoke(_MSCP_MakeMove, noun);
	Chessboard.change_chessboard();
];

! The user's asked to move a named piece to a location.

[ PieceToLocMoveSub;
	noun = cinvoke(_MSCP_PieceToLocMove, noun.rawsymbol, second);
	return AlgebraicMoveSub();
];

! The user's asked to move one location to another.

[ LocToLocMoveSub;
	noun = cinvoke(_MSCP_LocToLocMove, noun, second);
	return AlgebraicMoveSub();
];

! The user wants to resign.

[ ResignSub;
	! Check to see if it's the player's move.
	if (cinvoke(_MSCP_WhiteToMove) ~= playeris)
		"^~It's not your move.~";

	print "^~You're sure you want to resign?~^YES or NO >>> ";
	if (YesOrNo())
	{
		Chessboard.stop_game();
		"^~Coward.~";
	}
];
	
! The engine wants to notify us that something's happened. This gets called
! even when the engine is condering a move, so we have a global that tells
! us whether to ignore the notification or not.

[ _notify_move xp piece from to promotes takes flags  x y c i sd;
	! Describe the move to the player.

	if (flags & 1)
	{
		BlackOrWhite(1);
		print " castles";
	}
	else
	{
		print "~";
		DescribePiece(1, piece);
		print " to ";
		DescribeLocation(to);
	}

	if (takes)
	{
		print ", taking the ";
		switch (takes)
		{
			'p', 'P': sd = 1; print "pawn";
			'n', 'N': sd = 3; print "knight";
			'b', 'B': sd = 3; print "bishop";
			'r', 'R': sd = 5; print "rook";
			'q', 'Q': sd = 9; print "queen";
		}
		
		c = cinvoke(_MSCP_WhiteToMove);
		if (c)
			whitescore = whitescore + sd;
		else
			blackscore = blackscore + sd;
	}
	
	print ".";
	if (promotes)
	{
		print " It's promoted to a ";
		DescribePiece(0, promotes);
		print ".";
	}

	@log_shift flags 0-1 -> flags;
	if (flags == 1)
		print " Check.";
	else if (flags == 2)
	{
		print " Checkmate.";
		if (cinvoke(_MSCP_WhiteToMove))
			winner = WHITE;
		else
			winner = BLACK;
	}
	print "~^";

	if (sd && (playeris == cinvoke(_MSCP_WhiteToMove)))
	{
		style bold;
		print "^[You have scored ", sd, " point";
		if (sd > 1)
			print "s";
		print ".]^";
		style roman;
	}

	! And animate it on the chessboard (if displayed).

	if (~~chessboard_in_status_bar)
		return;

	x = from / 8;
	y = 7 - (from % 8);
	c = chessboard_array-->(x + y*8);
	c = c.symbol;
	
	for (i=0: i<2; i++)
	{
		Chessboard.draw_piece(x, y, '.');
		pause(2);
		Chessboard.draw_piece(x, y, c);
		pause(2);
	}
	Chessboard.draw_piece(x, y, '.');

	x = to / 8;
	y = 7 - (to % 8);
	for (i=0: i<3; i++)
	{
		Chessboard.draw_piece(x, y, '.');
		pause(2);
		Chessboard.draw_piece(x, y, c);
		pause(2);
	}
];

! The engine wants to emit progress information.

[ _progress_reset xp  y s;
	if (chessboard_in_status_bar)
	{
		@set_window 1;
		style reverse;
		s = (screen_width-1) - RIGHT_COLUMN;
		for (y=8: y<12: y++)
		{
			@set_cursor y RIGHT_COLUMN;
			spaces s;
		}
		progressx = RIGHT_COLUMN;
		progressy = 8;
		style roman;
		@set_window 0;
	}
];
	
[ _progress_start xp;
	if (chessboard_in_status_bar)
	{
		@set_window 1;
		style reverse;
		@set_cursor progressy progressx;
	}
	else
		style bold;
];

[ _progress_update xp;
	flush_output();
];

[ _progress_tab xp  x y;
	if (chessboard_in_status_bar)
	{
		progressx = progressx + 8;
		if (progressx >= (screen_width-TAB_SPACE))
		{
			progressx = RIGHT_COLUMN;
			progressy++;
		}
		@set_cursor progressy progressx;
	}
	else
		print ", ";
];

[ _progress_stop xp;
	style roman;
	if (chessboard_in_status_bar)
	{
		@set_window 0;
		progressx = RIGHT_COLUMN;
		progressy++;
	}
	else
	{
		print "^";
	}
];

[ _notify_thinking xp;
#ifdef undefined;
	spinner++;
	@set_window 1;
	@set_cursor 8 48;
	style reverse;
	if (spinner & 1)
		print (char) '+';
	else
		print (char) '*';
	flush_output();
#endif;
];

