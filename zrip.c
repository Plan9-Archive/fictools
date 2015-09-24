/*
 * (c) Mikael Ågren 2010. This source can be modified or 
 * redistributed any way or form you like as long as this
 * header stays intact and if you want to you buy me a 
 * coffee or a beer - whatever's your poison.
 *
 * This program has not been tested. Use at your own risk.
 */

/* Queue the QaD */
#define ZRIP_VERSION "0"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int error(char * msg, int code) {
	puts(msg);
	exit(code);
	return;
}

int main(int argc, char *argv[]) {
	if(argc != 3) {
		printf("usage: %s input output\n\n", argv[0]);
		printf("ZRip Tries to extract Z machine code from zblorb files. * Use at your own risk *\n");
		printf("ZRip version %s\n\n", ZRIP_VERSION);
		
		error("Too few parameters\n", -1);
	}
	FILE *in;
	FILE *out;
	if((in = fopen(argv[1], "r")) == NULL) {
		error("Couldn't open input file\n", -1);
	}
	/* Find beginning of zcode */
	char mystate=0;
	int mychar;
	while(mystate < 4) {
		mychar = fgetc(in);
		if(mychar == EOF) {
			if(feof(in) != 0)
				error("Couldn't find ZCOD block\n", -1);
			error("An input file error occured\n", -1);
		}
		switch(mystate) {
			case 0:
				if(mychar == 'Z')
					mystate++;
				break;
			case 1:
				if(mychar == 'C')
					mystate++;
				else
					mystate = 0;
				break;
			case 2:
				if(mychar == 'O')
					mystate++;
				else
					mystate = 0;
				break;
			case 3:
				if(mychar == 'D')
					mystate++;
				else
					mystate = 0;
				break;
		}
	}
	puts("Found ZCOD block.\n");
	(void)fgetc(in);
	(void)fgetc(in);
	(void)fgetc(in);
	(void)fgetc(in);

	/* Get the interesting parts of the zcode header */
	char *header;
	header = malloc(28);
	fread(header, 1, 28, in);
	int version = header[0];
	unsigned long filelength = 0xffff & ((((unsigned long)header[26]) << 8) | ((unsigned long)header[27] & 0xff));
	printf("File length: %lu\n", filelength);
	if((version >= 1) & (version <= 3))
		filelength *= 2;
	else if (version >= 6)
		filelength *= 8;
	else
		filelength *= 4;
	printf("Version:     %d\n", version);
	printf("File length: %lu\n", filelength);
	unsigned long dynamicsize = 0xffff & ((((unsigned long)header[14]) << 8) | ((unsigned long)header[15] & 0xff));
	printf("Dynamic memory size: %lu\n", dynamicsize);
	
	/* Extract zcode */
	char outfileending[4];
	sprintf(outfileending, ".z%d", version & 0xf);
	char outfilename[60];
	strncpy(outfilename, argv[2], 60-4);
	strncat(outfilename, outfileending, 3);
	if((out = fopen(outfilename, "w")) == NULL) {
		error("Couldn't open output file\n", -1);
	}
	if(fwrite(header, 1, 28, out) != 28)
		error("Couldn't write to file\n", -1);
	unsigned long i;
	for(i=28; i < filelength; i++) {
		if((mychar = fgetc(in)) == EOF) {
			if(feof(in) != 0)
				error("Input file seems to be too short\n", -1);
			else
				error("Couldn't read from file\n", -1);
		}
		if(fputc(mychar, out) == EOF)
			error("Couldn't write to file\n", -1);
	}	
	fclose(in);
	fclose(out);
	
	return 0;
}
