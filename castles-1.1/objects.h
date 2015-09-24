! objects.h
! All objects in the main room.

! --- Main room --------------------------------------------------------------

Object Dreaming "Dreaming"
	with
		name
			'dreaming',
		description
			"The room is small and richly carpeted. Or maybe it's a
			tent. There's a hint of curtains or tapestries in the
			darkness beyond the little pool of light in the
			centre.",
		after
		[;
			! Ensure that anything dropped anywhere in the room
			! ends up on the floor, even if the player is sitting
			! down.
			Drop:
				move noun to self;
		],
	has
		light;

Object -> "scenery"
	with
		name
			'curtains' 'tapestries' 'drapes' 'darkness' 'carpet',
		description
			"Some dark material; you can't make out the pattern.",
	has
		scenery;

Object -> Table "glass table"
	with
		name 
			'glass' 'table',
		initial
			"In the center of the room is a simple steel-and-glass
			table with a chessboard on it.",
		description
			"A tubular steel frame supporting a two-centimetre
			thick slab of glass. Very simple and oddly attractive,
			but somehow it doesn't fit the rest of the decor.",
		before
		[;
			Take:
				"Don't be silly.";
		],
	has
		supporter;

Object -> -> Orb "glass orb"
	with
		name
			'cloudy' 'glass' 'orb' 'ball',
		description
			"Silvery glass, a handspan across. Clouds move oddly
			inside it.",
		before
		[;
			PutOn:
				"It might roll away and get broken.";

			Drop, Attack:
				remove self;
				move genie to Dreaming;
				"You hold the orb out and let go. It falls
				maybe ten centimetres before a hand flashes out
				and catches it. ~No! No! Don't do that!~^
				^
				The owner of the arm --- a genie --- stows the
				orb away inside his voluminous robes and seats
				himself in the empty air across the table from
				you.^
				^
				~Thank heavens I caught it in time,~ he says
				irritably.  ~You don't want to know what would
				happen if you had actually broken it. Now, what
				do you want?~";
		],
		after
		[;
			PutOn:
				"[You shouldn't be able to put the orb on
				anything. Error!]";

			Take:
				"You pick the orb up gingerly. It's very
				light and feels extremely fragile.";
		];

Object -> Armchair "armchair"
	with
		name
			'armchair' 'chair' 'overstuffed',
		initial
			"An elderly armchair stands to one side of the table.",
		description
			"A slightly scruffy, worn leather armchair. Horsehair
			pokes out from the occasional tear in the leather, but
			despite that, it's the most relaxing thing you've
			ever sat in.",
		react_before
		[;

			Exit:
				"But you feel so comfortable.";

			Wake:
				"You really can't muster up the effort.";
		],
		before
		[;
			Take:
				"Don't be silly.";
		],
	has
		container open static transparent;

