! grammar.h

#include "Grammar";

[ OnOff;
	switch (NextWord())
	{
		'on', 'yes':
			parsed_number = 1;
			return 1;

		'off', 'no':
			parsed_number = 0;
			return 1;
	}
	return -1;
];

[ AlgebraicMove;
	parsed_number = cinvoke(_MSCP_ParseMove, WordAddress(wn), WordLength(wn));
	wn++;
	return 1;
];

[ AlgebraicLocation p  i;
	if (WordLength(wn) ~= 2)
		return 0;
	p = WordAddress(wn);
	i = p->0;
	if ((i<'a') || (i>'h'))
		return 0;
	i = p->1;
	if ((i<'1') || (i>'8'))
		return 0;
	parsed_number = p-->0;
	wn++;
	return 1;
];

[ IsChesspiece;
	return (noun ofclass Chesspiece);
];

verb meta "chessboard"
	* OnOff					-> Chessboard;

verb "play"
	* "chess"				-> PlayGame
	* "game"				-> PlayGame
	* 					-> PlayGame;

verb "layout"
	* "board"				-> LayoutBoard
	* "pieces"				-> LayoutBoard
	* "piece"				-> LayoutBoard
	*					-> LayoutBoard;

verb "lay"
	* "out"					-> LayoutBoard
	* "out" "board"				-> LayoutBoard;

verb "setup"
	* "board"				-> LayoutBoard
	* "pieces"				-> LayoutBoard
	* "piece"				-> LayoutBoard
	* 					-> LayoutBoard;

extend "set" first
	* "up"					-> LayoutBoard
	* "up" "board"				-> LayoutBoard
	* "up" "piece"				-> LayoutBoard
	* "up" "pieces"				-> LayoutBoard;

extend "move" last
	* noun=IsChesspiece "to" AlgebraicLocation -> PieceToLocMove
	* AlgebraicMove				-> AlgebraicMove
	* AlgebraicLocation AlgebraicLocation 	-> LocToLocMove
	* AlgebraicLocation "to" AlgebraicLocation -> LocToLocMove;

verb "resign"
	* 					-> Resign;

verb "surrender"
	* 					-> Resign;

verb "capitulate"
	* 					-> Resign;

extend "give" first
	* "up" 					-> Resign;

verb meta "timedinput"
	* OnOff					-> TimedInput;

verb meta "credits"
	*					-> Credits;

verb meta "buggers"
	*					-> Buggers;

