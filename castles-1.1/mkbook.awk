BEGIN {
	print "array __data_start -->"
	max = 0
}

/^[^#]/ {
	print "\"" $0 "\""
	if (length($0) > max)
		max = length($0)
}

END {
	print "\"\""
	print "0;"
	print "array __data_buffer -> " max+3 ";"
}

