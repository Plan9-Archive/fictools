! history.h
! Tim Eagen's history of chess.
! (C) Tim Eagen 1997, David Given 2001

! A potted history of chess.

[ HistoryShaturanga i;
	if (i)
		print "^", (b) "Shaturanga", "^^";

	print "~Chess originated in India, where it evolved from a game called
	Shaturanga. The antiquity of chess seems to be more legendary than
	actual, as is the case with so many games. According to some sources
	(Forbes, History of Chess, 1860) the game was invented between four or
	five thousand years ago, by the wife of King Ravana of Ceylon, when the
	capital was besieged by Rama. The earliest extant description of the
	game is contained in the Bhavishya Purana, which dates roughly from AD
	300 to AD 600, as nearly as I can ascertain from conflicting sources,
	and which is quite old enough.^
	^
	~Shaturanga was played on a board of 64 squares, on which four opposing
	forces were arrayed, one in each corner of the board: black, red, green, and
	yellow. Each player had a rajah, which moves as the modern king; an elephant,
	with moves equivalent to the modern rook; a horse, equivalent to the modern
	knight; a ship (roka in Sanskrit), which could move two squares diagonally,
	leaping over intervening pieces; and four pawns, which could move one square
	forward, capturing along the diagonal. The players sitting opposite each other
	were loosely allied against the other two players. Each player moved in turn by
	rolling an oblong die, the long sides marked 2, 3, 4, and 5. The number thrown
	determined which piece could be moved that turn:^
	^";
	font off;
	print (ul) "Roll Piece moved", "^";
	print " 2   Ship^";
	print " 3   Horse^";
	print " 4   Elephant^";
	print " 5   Rajah or Pawn^";
	font on;
	print "^
	~Shaturanga was a gambling game with complex rules, which I will not endeavor to
	explain here. When Hindu law prohibited gambling, players evaded the penalties
	by dispensing with the die rolls. Later, the allied sides were combined to form
	two forces. The second rajah was made a prime minister, and its movement
	reduced to one square along the diagonal. The moves of the elephant and the
	ship were transposed. At this point the game became known as Shatranj.";

	if (~~i)
		"~";
];

[ HistoryShatranj i  x y;
	if (i)
		print "^", (b) "Shatranj", "^^";

	print "~The first written reference to the game Shatranj occurs in a
	Persian work dating from about AD 600. The oldest chess problem on
	record dates from this time. The story concerns a prince who, having
	lost all of his possessions in previous games, staked his favorite
	wife, Dilaram, in a final attempt to mend his fortunes. For a time it
	seemed he would succeed, but presently he found himself one move away
	from being mated. Dilaram was observing the game from behind the
	purdha, the screen that separates the men and women in common areas of
	the Persian household.^^";

	font off;
	for (y=0: y<8: y++)
	{
		for (x=0: x<8: x++)
		{
			if ((y*7+x) & 1)
				style reverse;
			else
				style roman;

			switch (y*8+x)
			{
				1: print " R ";
				6: print " K ";
				21 to 22: print " p ";
				24: print " k ";
				38: print " n ";
				39: print " r ";
				47: print " b ";
				49: print " R ";
				63: print " r ";
				default: print " . ";
			}
		}
		print "^";
	}
	style roman;
	font on;

	print "^~Seeing her husband in despair and on the point of resignation,
	she cried out: 'O Prince, sacrifice your two rooks, and save Dilaram;
	forward with your elephant and pawn, and with the horse give checkmate'
	(translation after N Bland, Persian Chess, 1850). So guided the Prince
	saw the solution, and won the game.^
	^
	~Shatranj spread from Persia through Arabia and to Byzantium. How and
	when it entered Europe is not known. Three possible routes include
	Moorish Spain in the 7th century, through Byzantium at about the same
	time, and via the Crusades in the 12th century. The moves changed
	little in the ensuing centuries, and a text on the game of chess
	written in 1474 described a game essentialy identical to Shatranj.^
	^
	~The rules of the game, the setup, and the moves of the pieces resemble
	those of modern chess, but without the scope granted to the equivalent
	of the bishop (elephant) and queen (prime minister). Also, the initial
	positions of the king and prime minister were opposite those of the
	king and queen in modern chess.  The moves of the pieces are given in
	the table below, with the Persian names for the pieces.^^";

	font off;
	style bold;
	print "Name    Translation    no/pieces  Move^";
	style roman;
	print "Shah    King               1      Like a modern king^
	       Firz    Prime Minister     1      One square diagonally^
	       Fil     Elephant           2      Two squares diagonally, may leap^
	       Faras   War Horse          2      Like a modern knight^
	       Ruhk    Ship               2      Like a modern rook^
	       Baidaq  Pawn               8      Like a modern pawn; promotes to a firz^";
	font on;

	print "^~The game could be won in three ways:^
	^
	1. Checkmate: when the opponent's king is unable to avoid capture on
	the next move.^
	^
	2. Isolation: when all of the opponent's pieces, except for the king,
	have been captured.^
	^
	3. Stalemate: If the opponent has no legal moves, he is allowed to
	switch the position of his king with any other of his pieces that
	remain on the board, provided that the exchange does not place the king
	in check. The exchanged piece is known as the 'victim', as it is
	usually captured. If the opponent has no legal moves or exchanges, he
	is lost.^
	^
	~Draws occur by agreement, or by perpetual check.";

	if (~~i)
		"~";
];

[ DilaramsSolution;
	"~Oh, how Dilaram won her husband's chess game? It goes like this. It
	is white's move; he is in danger of being mated by the movement of the
	rook at B8 to A8, so he must force black to make other moves. The rook
	at H4 moves to H8, giving check.  The king is forced to capture the
	rook, whereupon the elephant at H3 moves to F5, exposing the black king
	to check from the rook at H1. The king moves back to G8. The rook at H1
	moves to H8, placing the king in check, and again forcing the king to
	capture. White then plays the pawn at G6 to G7, giving check; once
	again, the king must move back to G8. White now plays the horse to H6,
	giving checkmate.~";
];
	
[ HistoryIndiaAndTheWest header  x y i;
	if (header)
		print "^", (b) "Variants: India and the West", "^^";

	print "~The 'Great Chess', or 'Tamerlane's Chess' was the variation
	played by the Mogul conqueror Tamerlane. The game board held 112
	squares, and featured 28 pieces on each side. This form of chess had
	been lost for several hundred years, until it was rediscovered in a
	Persian manuscript.^
	^
	~Byzantine Chess, or Circular Chess, was an odd variant played on a
	circular board having 64 squares and 4 citadels. The moves were similar
	to those of Shatranj, except that there was no pawn promotion. If two
	of a player's pawns circled the board and came face-to-face, the
	player's adversary lifted both pawns from the board before making his
	own move. If a player's king sought refuge in his opponent's citadel,
	the game was drawn.^
	^
	~Courier Chess was played in Germany at the beginning of the 13th
	century, and for several centuries thereafter. A painting by Van
	Leyden, produced circa 1520, portrays a game of courier chess. The
	village of Strobeck was presented a board by Elector-Prince Frederick
	William of Brandenburg in 1651, which the village still possesses. The
	board measures 12 by 8 squares, and features the addition of three
	pieces: the sage, the jester, and the courier.^
	^";

	font off;
	for (y=0: y<8: y++)
	{
		for (x=0: x<12: x++)
		{
			i = y*11+x;
			if (i & 1)
				style reverse;
			else
				style roman;

			switch (y*12+x)
			{
				0: print " R ";
				1: print " N ";
				2: print " B ";
				3: print " C ";
				4: print " J ";
				5: print " K ";
				6: print " Q ";
				7: print " S ";
				8: print " C ";
				9: print " B ";
				10: print " N ";
				11: print " R ";
				12 to 23: print " P ";
				72 to 83: print " p ";
				84: print " r ";
				85: print " n ";
				86: print " b ";
				87: print " c ";
				88: print " s ";
				89: print " k ";
				90: print " q ";
				91: print " j ";
				92: print " c ";
				93: print " b ";
				94: print " n ";
				95: print " r ";
				default: print " . ";
			}
		}
		print "^";
	}
	style roman;


	style bold;
	print "^Symbol  Name  no/pieces  Move^";
	style roman;
	print "  K     King      1      Like a modern king^";
	print "  Q     Queen     1      One square diagonally [1]^";
	print "  B     Bishop    2      Two squares diagonally, may leap^";
	print "  N     Knight    2      Like a modern knight^";
	print "  R     Rook      2      Like a modern rook^";
	print "  C     Courier   2      Like a modern bishop^";
	print "  J     Jester    1      One square orthogonally^";
	print "  S     Sage      1      Like a modern king^";
	print "  P     Pawn      12     Like a modern pawn [2]^";
	font on;

	print "^[1] On the first move the queen may 'joy leap' vertically
	forward to the 3rd rank.^
	[2] The rook and queen pawns can move two squares on their first move.^
	^
	~A game of courier chess frequently began with both players moving their
	rook and queen pawns to the fourth rank, and leaping the queen to the
	third rank, in order to speed the game.^
	^
	~On reaching the 8th rank a pawn was not automatically promoted. The
	pawn must leap backward to the 6th, 4th, and 2nd ranks, whereupon it
	was promoted to a queen. The pawn could make no captures nor any other
	moves during these leaps, and could not leap over intervening pieces.
	These leaps did not have to be made on consecutive moves. While on the
	8th rank, the pawn was immune to capture.";

	if (~~header)
		"~";
];

[ HistoryEastOfIndia header;
	if (header)
		print "^", (b) "Variants: East of India", "^^";

	print "~From India chess also spread into the orient. One of the
	general features of chess in the far east is that draws by repetition
	are not allowed; the player first repeating his moves must vary the
	pattern, even if the variance is to his disadvantage.^
	^
	~Chess in Burma, called Sittuyin, is unusual in that the initial
	arrangement of the major pieces on the board are the opening moves of
	the game. Each player places his soldiers (pawns) in predesignated
	positions, four on the third rank, and four on the fourth. Then each
	player in turn places one major piece anywhere on his own side of the
	board, until all of the pieces are on the board. Players may continue
	to shift their pieces on their own side of the board until a soldier is
	moved, at which point normal play begins.^
	^
	~Siamese chess (Mak-ruk) uses cowrie shells for the pawns, which are
	lined up on each player's third rank at the start of the game. A cowrie
	that reaches the opponent's third rank is promoted; this status is
	indicated by turning the cowrie over.^
	^
	~The versions of chess played in China and Japan have drifted quite a
	distance from their Indian origins, I will describe them seperately.";
	
	if (~~header)
		"~";
];

[ HistoryChinese header i;
	if (header)
		print "^", (b) "Siang K'i: Chinese Chess", "^^";

	print "~Siang K'i adds a number of interesting features to the game,
	including fortresses, a moat, and cannons. As usual, a legendary
	antiquity is claimed for the game; however, its earliest mention is
	found in the Book of Marvels, attributed to Nui Seng-ju, who died in AD
	847. The game is popular in China, and especially in Hong Kong.^^";

	font off;
	print "T-H-E-M-G-M-E-H-T   G General^";
	print "| | | |@@92|/| | | |   M Mandarin^";
	print "+-+-+-+-+-+-+-+-+   E Elephant^";
	print "| | | |/|@@92| | | |   H Horseman^";
	print "+-C-+-+-+-+-+-C-+   T Chariot^";
	print "| | | | | | | | |   C Cannon^";
	print "P-+-P-+-P-+-P-+-P   P Pawn^";
	print "| | | | | | | | |^";
	print "+-+-+-+-+-+-+-+-+^";
	print "^";
	print "+-+-+-+-+-+-+-+-+^";
	print "| | | | | | | | |^";
	print "p-+-p-+-p-+-p-+-p^";
	print "| | | | | | | | |^";
	print "+-c-+-+-+-+-+-c-+^";
	print "| | | |@@92|/| | | |^";
	print "+-+-+-+-+-+-+-+-+^";
	print "| | | |/|@@92| | | |^";
	print "t-h-e-m-g-m-e-h-t^";
	font on;

	print "^^~The game board is split into two territories, each measuring
	5 by 9 grid lines, separated by a 'moat'. The pieces are not played
	within the squares, but at the intersections of the grid lines. Each
	player has a 'fortress' composed of 4 squares marked with diagonal
	slashes at each end of the board. The playing pieces are discs with
	their ranks written on their upper faces in ideograms. One side is
	marked in red, the other in green or black. Some of the characters for
	pieces having the same powers differ from one side to the other. The
	moves of the pieces are:^
	^
	~General: one point orthogonally; may not leave the fortress.^
	~Mandarin: one point diagonally; may not leave the fortress.^
	~Elephant: two points diagonally; may not leap intervening pieces; may not cross the moat.^
	~Horseman: one point orthogonally followed by one point diagonally; may not leap intervening pieces.^
	~Chariot: like a modern rook.^
	~Cannon: like the chariot, but only captures if it jumps an intervening piece (called the 'screen') from either side; it may only jump when making a capture and may only make one jump in a turn.^
	~Pawn: one point forward on its own side of the board; on the enemy's side it may move forwards or sideways. There is no promotion; a pawn on the last rank may only move sideways.^
	^
	~The object is to checkmate the general, and all of the usual rules of
	western chess apply. There are some variations worth mentioning
	regarding checks. When generals face each other along an unobstructed
	file, one of the generals is in check. Since a general may not move
	into check, this only occurs when the two generals are on the same
	file, and a player moves the sole intervening piece. The player moving
	the piece that exposes the generals on the file gives the check. As the
	horseman cannot jump an intervening piece, a check given by the
	horseman can be blocked by interposing a piece on the angle of the
	horseman's move. Finally, a cannon attacks the general in the same way
	as it attacks any other piece - by 'shooting' over a 'screen'. If the
	screen is removed, or if another piece is interposed, the check is
	relieved. If the check cannot be relieved, the general is lost and the
	game is over.";
	
	if (~~header)
		"~";
];

[ HistoryJapanese header  x y;
	if (header)
		print "^", (b) "Sho-gi: Japanese Chess", "^^";

	print "~Sho-gi has been played in Japan for centuries, and is almost as
	ancient as siang k'i. It is immensely popular in Japan, having more
	than ten million players. In medieval Japan there were seven ranks, the
	seventh being the highest. The highest rank was not always awarded, and
	was often vacant. In those times there were a number of families who
	were particularly associated with the game, and whose membership
	traditionally included many of the highest ranked players.^
	^
	~Currently the leading hundred players are classed as professionals. An
	annual match, called the Meijin-sen, is held between the top player and
	the leading contender, the winner bearing the title of 'Meijin' for the
	ensuing year.^^";

	font off;
	for (y=0: y<9: y++)
	{
		for (x=0: x<9: x++)
		{
			if ((y*9+x) & 1)
				style reverse;
			else
				style roman;

			switch (y*9+x)
			{
				0: print " L  ";
				1: print " H  ";
				2: print " SG ";
				3: print " GG ";
				4: print " JK ";
				5: print " GG ";
				6: print " SG ";
				7: print " H  ";
				8: print " L  ";
				10: print " FC ";
				16: print " A  ";
				18 to 26: print " S  ";
				54 to 62: print " s  ";
				64: print " a  ";
				70: print " fc ";
				72: print " l  ";
				73: print " h  ";
				74: print " sg ";
				75: print " gg ";
				76: print " jk ";
				77: print " gg ";
				78: print " sg ";
				79: print " h  ";
				80: print " l  ";
				default: print " .  ";
			}
		}
		style roman;
		switch (y)
		{
			0: print "  JK  Jewelled King^";
			1: print "  GG  Gold General^";
			2: print "  SG  Silver General^";
			3: print "  H   Honourable Horse^";
			4: print "  L   Lance^";
			5: print "  A   Angle-Going^";
			6: print "  FC  Flying Chariot^";
			7: print "  S   Soldier^";
			8: print "^";
   		}
	}
	font on;

	print "^~Sho-gi brings to chess an interesting level of complexity. The
	pieces are wedge-shaped tablets resembling small obelisks, that lie
	flat on the board. As in siang k'i, the names of the pieces are
	inscribed on the pieces. Each piece, save the Jeweled Kings and the
	Gold Generals, has a specific value to which it can be promoted during
	the game, the symbol for which is inscribed on the reverse side of the
	piece (the first move is determined by flipping a soldier; the opponent
			calls 'soldier' or 'general'; the winner of a game
			begins the next). Promotion occurs when a player's
	piece enters enemy territory, defined as the three ranks closest to the
	opponent's side of the board. Promotion is at the player's option for
	each turn the piece remains in enemy territory.  The moves of the
	pieces, and their promotion values are given as follows:^
	^
	~Jewelled King: one square in any direction. Is not promoted.^
	~Gold General: one square orthogonally, or diagonally forward. Is not promoted.^
	~Silver General: one square diagonally, or straight forward. Promoted to Gold General.^
	~Honourable Horse: two squares straight forward, then one square right or left; may leap intervening pieces. Promoted to Gold General.^
	~Lance: any number of open squares, straight forward only. Promoted to Gold General.^
	~Angle-Going: like a modern bishop. Promoted to Dragon Horse.^
	~Flying Chariot: like a modern rook. Promoted to Dragon King.^
	~Soldier: one square forwards. Promoted to Gold General.^
	^
	~The Dragon Horse and Dragon King are like the Angle-Going or Flying
	Chariot but can also move one square in any direction.^
	^
	~The pieces are not colored, and are distinguished only by the
	direction in which they point. This enables the use of a unique rule -
	captured pieces may be returned to the board on the side of the player
	who captured the piece, simply by turning the piece to point toward the
	opponent and dropping it on a square. This may be done on any turn the
	player desires, so that the drop can be made to maximum effect.^
	^
	~The drop of a piece is subject to the following rules:^
	^
	~1. Pieces that have been promoted revert to their original powers when
	dropped onto the board, even if dropped into enemy territory. In the
	latter case, they may be promoted again once they have made a move.^
	^
	~2. A soldier cannot be dropped on a file occupied by one of the
	player's unpromoted soldiers.^
	^
	~3. A soldier or lance cannot be entered on the last rank, or the
	honourable horse on the last two rows; otherwise, they could never move
	and so never promote.^
	^
	~4. A piece may be dropped so as to give check, but not to give checkmate.^
	^
	~The game ends with checkmate. If a king enters enemy territory, the game is drawn.";

	if (~~header)
		print "~";
];

[ HistoryModern header;
	if (header)
		print "^", (b) "Modern Chess", "^^";

	print "~Chess reached its present form in the 15th and 16th centuries,
	when the queen was endowed with her sweeping powers, and when castling
	was introduced to the game.^
	^
	Beginning in the 19th century, positional theory came to the fore.
	Steinitz demonstrated the value of a methodical approach to development
	and the use of small advantages (such as two bishops against a bishop
			and knight) that is taken for granted today. In the
	20th century, Nimzovitch developed an integrated system for playing
	chess, that has become a standard for the game. My System, first
	published in 1930, is still regarded by many as the essential text for
	the serious student of chess.";

	if (~~header)
		print "~";
];

[ HistoryInternet header;
	if (header)
		print "^", (b) "Chess on the Internet", "^^";

	print "~The internet has created a new venue for chess players.
	Previously, to play a game with players at any distance involved
	mailing moves back and forth, entailing a wait of days or weeks for a
	reply.  Moreover, the winner was usually the player with the best chess
	library and, more recently, with the best chess computer program. Use
	of e-mail has speeded things up considerably, although book research
	and number crunching are still realities that have to be faced.^
	^
	~Live games can now be played with chess players anywhere in the world.
	Currently the best way of doing this is via Telnet. Through Telnet, a
	number of players all log into a single remote chess server. Using
	their computers as remote terminals, the moves are transmitted to the
	server, and from the server to the other player.^
	^
	~The servers provide rough schematics of the chess boards using ASCII
	text characters, but most players prefer to use specialized 'client
	software' that interprets the data stream from the remote computer and
	displays the position on a graphic interface. The software also allows
	the chess player to make moves using a mouse, rather than having to
	enter the moves from the keyboard. This client software can be
	downloaded free of charge from any number of FTP sites or web pages.
	You can play directly from many servers' web pages by using a Java
	applet, though in my experience applets tend to be slower and less
	versatile than the available client software.^
	^
	~A time-keeping program is usually integrated into the client software,
	so that timed games can be played. This allows time control methods
	that have not been available to over-the-board players with standard
	chess clocks. One popular time control is '2 12', meaning each player
	has 2 minutes to make all of his or her moves, but every move adds 12
	seconds to the player's clock. This allows faster games than the
	standard '40 moves in two hours' or '30 moves in 30 minutes' time
	controls, but also allows a game much more relaxed than the 5 minute
	blitz game. Note however that just about any time control, including 1
	minute lightning games, can be played.";

	if (~~header)
		"~";
];

