BEGIN {
	addr = 0
	print "[ _make_book_from_table xp book;"
}

{
	i = 0;
	while ($(i+2) != "")
	{
		j = $(i+2)*256 + $(i+3)
		print "! " $(i+2) " " $(i+3)
		printf "@storew book " (i/2) " "
		if (j < 0)
			printf "0"
		print j ";"
		i += 2;
	}
	print "@add book " (i) " -> book;"
}

END {
	print "];"
}

