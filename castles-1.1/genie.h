! objects.h
! All objects in the main room.

Object Genie "genie"
	with
		name
			'genie' 'djinn',
		description
		[;
			print "You've never seen a genie before, but there's no doubt
			that this is one. Turban, strange moustache, pointed
			ears, ornate robes, smoke where his legs should be ---
			yes, everything's there. Somehow, however, you'd
			expected a genie to be somewhat more, well, impressive.
			Perhaps it's the way he keeps nervously cleaning his
			wire-rimmed glasses, or the row of pencils sticking out
			of what would be his shirt pocket, if he had a shirt;
			but whatever he is, this is not the kind of genie that
			strides across the landscape smiting your enemies. This
			is the kind of genie that sits behind a desk and writes
			them memos.^
			^
			Inside the genie you can see a brain.";
			if (self.cross)
				print "^He looks cross.^";
			rtrue;
		],
		life
		[ i;
			Ask:
				switch (second)
				{
					'orb', 'ball':
						"He just shudders.";

					'chessboard':
						"~Nice, isn't it? I got it off
						an angel I used to know. It's
						got real neutronium veneer on
						the back.~";

					'table', 'steel':
						"~I got that from an IBM
						engineer. He wanted to ask my
						advice about building some sort
						of chess-playing machine. The
						Big Blue, or something like
						that. Quite laughable,
						really.~";

					'armchair', 'chair':
						"~I've no idea where ", (b) "that",
						" came from.~";

					'tent', 'curtains', 'tapestries':
						"~What ", (address) second, "?~";

					'jack', 'maet':
						"The genie seems to be having trouble suppressing a smirk.";

					'david', 'given', 'author':
						"~He's just this guy, you know?~";

					'graham', 'nelson':
						"~Shh! Do not summon Him. He may... read poetry.~";

					'volker', 'barthelmann':
						"The genie rummages around and
						pulls out a piece of paper. ~I
						have a message for him. It
						says: 'Thanks, dude.' I hope
						you understood it; I didn't.~";

					'moustache', 'tache', 'turban',
					'robes', 'smoke', 'pointed', 'ears':
						"~Part of the official dress
						code, I'm afraid.~";

					'genie', 'him', 'himself', 'itself':
						"~I am a genie. I am one of
						those that stand between the
						day and the night, the light
						and the dark, between man and
						god. We watch over the world
						and ensure it turns smoothly on
						its axis. We are
						intermediaries, expediters,
						interpreters and interpolators.^
						^
						~In my spare time I also play
						chess. I have been extremely
						generous and reduced my natural
						skill level to grade ",
						cinvoke(_MSCP_GetIntelligence),
						" in order to provide you with
						a suitably simplified game, but
							I can reduce it further
							if necessary.";

					'daemon':
						"He primly polishes his
						glasses. ~I prefer to be called
						a genie.~";

					'demon':
						"~I hope you mean ", (b)
						"daemon", ". ", (b) "Demons", "
						exist only in Christian
						mythology.";

					'christian', 'mythology':
						"He looks at you in
						exasperation. ~Look, do you
						want to play or not?~";

					'glasses':
						"He looks defensive. ~What
						about them?~";

					'pencils':
						"He looks confused. ~They're
						just pencils.~";

					'ply':
						"~A count of the number of half
						moves. For example, if white
						moves, that's one ply. Then
						black moves; that's two ply.
						And so on.~";

					'king':
						"~The key to the game. If you
						can take your opponent's king
						--- called being in check ---
						and your opponent can't stop
						you --- known as check-mate ---
						you've won the game. The king
						can move one square in any
						direction per move; but the two
						kings cannot occupy adjacent
						squares.~";

					'queen':
						"~The most powerful piece in
						the game. The queen can move
						any distance in any direction
						each move.~";

					'bishop':
						"~These pieces can move
						diagonally any distance per
						move.~";

					'rook', 'castle':
						"~These pieces can move
						orthogonally any distance per
						move. There's also a special
						move these can make, called
						castling, but I won't talk
						about that now.~";

					'knight':
						print "~The strangest of all
						the pieces.  Knights move one
						space orthogonally and one
						space diagonally, always moving
						away from the starting point.
						What's more, they jump over all
						the intermediate pieces.^^";
						DrawKnightDiagram();
						"^~In the above diagram, the
						knight has just jumped from X
						to its current
						position.~";

					'pawn':
						"~One of the simplest and yet
						most intricate of the pieces.
						Pawns can normally only move
						one square forwards and cannot
						take pieces. However, there are
						exceptions. Firstly, if a pawn
						reaches the far end of the
						board, it turns into any other
						piece (your choice, but a queen
								is usual).
						Secondly, a pawn may move
						diagonally forwards in order to
						take an opposing piece.
						Thirdly, a pawn's very first
						move can be two spaces, not
						just one.^
						^
						~However: if a pawn moves two
						spaces in this way, it may be
						immediately be taken by an
						opposing piece as if it had
						only moved one square. This
						only applies to the next move.
						This is called taking ", (b)
						"en passant", ", from the
						French 'in passing'. This is
						possibly the most obscure move
						in the entire game.~";

					'diagram', 'drawing':
						"He eyes you archly. ~You want
						to know how I can speak
						diagrams? I ", (b) "am", " a
						genie, you know.~";

					'diagonal', 'diagonally':
						"~I'm sure you know what '", (address) second,
						"' means.~";

					'orthogonal', 'orthogonally':
						"~Either up/down or left/right.~";

					'intelligence', 'brain', 'forehead':
						"~I think about moves by determining all the
						possible moves I could make,
						and picking the most favourable. I can
						also take into account the
						possible moves ", (b) "you",
						" might make afterwards, and the
						possible response I could make
						to that, and so on. My intelligence
						level determines how many ply I
						look ahead. It's currently set
						to ",
						cinvoke(_MSCP_GetIntelligence),
						".^
						^
						~The more I look ahead, the
						longer I have to spend thinking
						about the moves. At high
						levels, we may be here some
						time. At low levels, I'll move
						pretty much instantly, but even
						you will be able to beat
						me...~";

					'opening', 'book':
						"~At the very beginning of the
						game, I don't really think
						about my moves. I've got a
						prepared set of possible moves
						that I use. Whenever you make a
						move, I look it up in the book
						to find if there's a set
						opening that will help me; if
						so, I make the move from that
						opening. I only start playing
						properly when the book can no
						longer help me.~";

					'move', 'moves', 'moving':
						"~Moves are generally
						represented by standard
						algebraic notation. This can
						take a number of forms. The
						simplest is to just put the
						start and end of a move. For
						example, ", (b) "move a1a2", "
						moves the piece from A1 to A2.
						If it's not ambiguous, you can
						replace the start with the
						symbol representing the piece
						to be moved. For example, ",
						(b) "move Qd5", " means to move
						the queen to D5.^
						^
						~If you're moving a pawn to the
						far side of the board, you will
						need to tell the game what you
						want it promoted to. For
						example, ", (b) "move Pa8=Q", "
						means to move the pawn to A8
						and promote it to a queen.^
						^
						~Castling can be done by ", (b)
						"move O-O", " or ", (b) "move
						O-O-O", ", depending which side
						you want to castle on.^
						^
						~There are a few other
						algebraic forms but these three
						will be sufficient to play a
						complete game.^
						^
						~As a shortcut, it's also
						possible to do ", (b) "move a2
						to a3", " and ", (b) "move pawn
						to a3", ". These are directly
						equivalent to the first two
						algebraic forms.~";

					'check', 'checkmate':
						"~The purpose of the game is to
						manouver yourself into a
						position where you can take
						your opponent's king. If you
						are in a position where you can
						do this, your oppenent is
							referred to as being ",
								(b) "in check",
						". If your opponent cannot
						prevent the king from being
							taken, then you have
							won; this is called ",
							(b) "checkmate", ".^
						^
						~It is not legal to move into a
						position where you will be in
						check. In addition, the only
						legal moves you can make while
						being in check are ones that
						will take you immediately out
						of it.~";

					'chess':
						"~I can tell you about the
						history or the rules, if you
						like.~";

					'rules':
						print "~The game is a highly
						abstracted form of warfare
						between two opposing armies. It
						is played by two players on a
						eight by eight board. Each
						player gets sixteen pieces;
						eight pawns, two rooks (or
								castles, as
								they are also
								known), two
							bishops, two knights, a
							queen and a king. The
							purpose of the game is
							to try and capture the
							opposing player's
							king.~^
						^
						~The two players are called
						'black' and 'white', so named
						from the colour of the pieces.
						White always moves first.^
						^
						~Each player takes it in turns
						to move a single piece. A move
						can legitimately end on one of
						your opponents pieces, in which
						case that piece is removed
						permanently from the board;
						this is called 'capturing' or
							'taking'. Each type of
							piece moves
							differently; ask me
							about each one and I'll
							give you more details.^
						^
						A special move called
						'castling' is also available in
						some circumstances.^^";
						style bold;
						print "[To start a game, do
						'play' or 'setup' if you want
							to use a custom board
							layout.]";
						style roman;
						rtrue;

					'history':
						print "^~Are you sure? There's
						a lot of it.~^YES or NO >>> ";
						if (~~YesOrNo())
							"^~All right, then.~";

						print "^The genie settles back
						in his non-existant chair for a
						good long lecture.^
						^
						~Modern international chess as
						it is played today is a
						relatively recent invention.
						The sweeping moves of the queen
						and the long reach of the
						bishops were not elements of
						the original game. Nor were
						such maneuvers as castling or
						capturing en passant. On the
						other hand, the moves of the
						remaining pieces are nearly
						identical to those of their
						ancient analogues.^
						^
						~Moreover, there are other
						forms of chess still being
						played today which, while not
						so widespread geographically as
						western chess, are yet played
						by significant numbers of
						people. Indeed, the variety of
						chess played in China, Hong
						Kong, and Taiwan can claim as
						many, if not more, players as
						its western counterpart.
						Japan's chess, significantly
						different from both the western
						and Chinese versions, also
						claims players who number in
						the millions.^";
						HistoryShaturanga(1);
						print "^";
						HistoryShatranj(1);
						print "^";
						HistoryIndiaAndTheWest(1);
						print "^";
						HistoryEastOfIndia(1);
						print "^";
						HistoryChinese(1);
						print "^";
						HistoryJapanese(1);
						print "^^~Unfortunately, I
						can't play any of these
							variants.~^";
						HistoryModern(1);
						print "^";
						HistoryInternet(1);
						"~";

					'shaturanga':
						HistoryShaturanga(0);
						rtrue;

					'shatranj':
						HistoryShatranj(0);
						rtrue;
						
					'dilaram', 'solution':
						DilaramsSolution();
						rtrue;
						
					'west':
						HistoryIndiaAndTheWest(0);
						rtrue;

					'east':
						HistoryEastOfIndia(0);
						rtrue;

					'chinese', 'china', 'siang', 'ki':
						HistoryChinese(0);
						rtrue;

					'japanese', 'japan', 'sho', 'gi', 'sho-gi', 'shogi':
						HistoryJapanese(0);
						rtrue;

					'modern', 'international':
						HistoryModern(0);
						rtrue;

					'net', 'internet', 'computer':
						HistoryInternet(0);
						rtrue;

					'castling':
						"~Castling is a rather odd move
						involving the king and a
						castle; hence the name. It can
						be done only once in a game,
					and only then if certain conditions are
						met.^
						^
						~What happens is: in a single
						move, the king moves two spaces
						towards one of your castles,
						and the castle jumps into the space
						crossed over by the king. This
						can be done with either castle.
						Neither the king or the castle
						may have been moved prior to
						this, all the spaces crossed
						over must be vacant, and none
						may be under attack by your
						opponent.^
						^
						~Ask me about moving if you want
						to know how to castle.~";

					'score', 'scores', 'scoring':
						print "~When you take a piece,
						your score is increased.^
						^";
						font off;
						print (ul) "Score  Piece^",
						           "  1    Pawn^",
							   "  3    Knight^",
							   "  3    Bishop^",
							   "  5    Rook^",
							   "  9    Queen^";
						font on;
						"^~The king, of course, can't be taken.^
						^
						~Traditionally chess doesn't
						have much truck with scoring
						individual pieces. However, I
						like it, and the scores reflect
						the value I put on the pieces
						when considering moves, so it's
						useful to keep track of.~";
				}
				"~I'm sorry, I don't follow you.~";

			Tell:
				"~What about it?~";

			Answer:
				switch (noun)
				{
					'hello', 'hi', 'hey', 'howdy':
						"~Hello to you, too.~";
				}
				"The genie stares at you evenly.";

			Order:
				switch (action)
				{
					##PlayGame:
						PlayGameSub();
						rtrue;
				}
				"~What?~";
				
			Kiss:
				"Ew.";

			Attack:
				"~Don't even think about it.~";
		],
		cross
			0,
	has
		animate transparent;

Object -> "brain"
	with
		name
			'brain',
		description
		[;
			"The genie's brain is set to ",
			cinvoke(_MSCP_GetIntelligence), ".";
		],
		before
		[  i;
			SetTo:
				if (second < 1)
				{
					Genie.cross = 1;
					"The genie narrows his eyes and starts drumming his fingernails
					on the table. You notice he has claws. You change the subject
					hastily.";
				}
				if (second > 4)
					"~At level four it takes me long enough to think as it is.~";

				i = cinvoke(_MSCP_GetIntelligence);
				if (second == i)
					"~I'm already that intelligent.~";

				cinvoke(_MSCP_SetIntelligence, second);
				if (second < i)
					print "The genie concentrates intently. You see his turban
					gradually sink as his forehead shrinks. ";
				else
					print "The genie concentrates intently. You see his turban
					gradually rise as his forehead expands. ";
				
				switch (second)
				{
					1: "~Ug. Me Stupid.~";
					2: "~Maybe level 3 was a bit too hard for you.~";
					3: "~You'll never beat me like this.~";
					4: "~Oh, please. Don't make me laugh.~";
				}
				"[Internal brain error ", second, "!]";
		];

[ DrawKnightDiagram  i;
	font off;
	for (i=0: i<4: i++)
	{
		if (i & 1)
			style reverse;
		else
			style roman;
		print " . ";
	}
	print "^";
	for (i=0: i<4: i++)
	{
		if (i & 1)
			style roman;
		else
			style reverse;
		if (i==1)
			print " X ";
		else
			print " . ";
	}
	print "^";
	for (i=0: i<4: i++)
	{
		if (i & 1)
			style reverse;
		else
			style roman;
		print " . ";
	}
	print "^";
	for (i=0: i<4: i++)
	{
		if (i & 1)
			style roman;
		else
			style reverse;
		if (i==2)
			print " N ";
		else
			print " . ";
	}
	print "^";
	for (i=0: i<4: i++)
	{
		if (i & 1)
			style reverse;
		else
			style roman;
		print " . ";
	}
	print "^";
	style roman;
	font on;
];

