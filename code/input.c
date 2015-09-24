#include <stdlib.h>
#include <stdio.h>
 
char *get_line(FILE* fp)
{
	int len = 0, got = 0, c;
	char buf[128];

	while ((c = fgetc(fp)) != EOF) {
		if (got + 1 >= len) {
			len *= 2;
			if (len < 4) len = 4;
/*			buf = realloc(buf, len); */
		}
		if (c == '.') break;
		buf[got++] = c;

	}
	if (c == EOF && !got) return 0;
 
	buf[got] = '\0';
	return buf;
}
 
int main()
{
	char *s;
	int j;
	while ((s = get_line(stdin))) {

		printf("%s",s);
		j=atoi(s);
		printf(" j times 3 is %d ", j*3);
		if(j==99)
			break;

		printf("next\n");

/*		free(s); */
	}
	return 0;
}
