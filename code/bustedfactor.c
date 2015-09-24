#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
 
typedef struct {
    int *list;
    short count; 
} Factors;

void xferFactors( Factors *fctrs, int *flist, int flix ) 
{
    int ix, ij;
    int newSize = fctrs->count + flix;
    if (newSize > flix)  {
/*
        fctrs->list = realloc( fctrs->list, newSize * sizeof(int));
*/
	;
    }
    else {
        fctrs->list = malloc(2 * newSize * sizeof(int));
    }
    for (ij=0,ix=fctrs->count; ix<newSize; ij++,ix++) {
        fctrs->list[ix] = flist[ij];
    }
    fctrs->count = newSize;
}
 
Factors *factor( int num, Factors *fctrs)
{
    int flist[10], flix;
    int dvsr;
    flix = 0;
    fctrs->count = 0;
    free(fctrs->list);
    fctrs->list = NULL;
    for (dvsr=1; dvsr*dvsr < num; dvsr++) {
        if (num % dvsr != 0) continue;
        if ( flix == 300) {
            xferFactors( fctrs, flist, flix );
            flix = 0;
        }
        flist[flix++] = dvsr;
        flist[flix++] = num/dvsr;
    }
    if (dvsr*dvsr == num) 
        flist[flix++] = dvsr;
    if (flix > 0)
        xferFactors( fctrs, flist, flix );
 
    return fctrs;
}
 
int main(int argc, char*argv[])
{
    int nums2factor[] = { 2059, 45 };
    Factors ftors = { NULL, 0};
    char sep;
    int i,j;
	char *maltest;
	maltest=strdup("foo");
	printf("%s", maltest);
/*
	maltest = (char*)malloc(10 * sizeof(int));
*/
 /*
    for (i=0; i<2; i++) {
        factor( nums2factor[i], &ftors );
        printf("\nfactors of %d are:\n  ", nums2factor[i]);
        sep = ' ';
        for (j=0; j<ftors.count; j++) {
            printf("%c %d", sep, ftors.list[j]);
            sep = ',';
        }
        printf("\n");
    }
*/
    return 0;
}
