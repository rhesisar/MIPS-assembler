#include <errno.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void
*emalloc(size_t size)
{
	void *p = NULL;

	if ((p = malloc(size)) == NULL){
		perror("malloc");
        exit(1);
    }
	return p;
}

FILE
*efopen(const char *pathname, const char *mode)
{
    FILE *fp;

    if ((fp = fopen(pathname, mode)) == NULL){
        perror("fopen");
        exit(1);
    }
    return fp;
}

void
error(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	exit(1);
}

int
inttonbits(int n, int nbits)
{
	return n & ((int)pow(2.0, (double)nbits) - 1);
}
int
nbitstoint(int n, int nbits)
{
	if (n >> (nbits - 1) == 1)
        return n - (int)pow(2.0, (double)nbits);
    return n;
}

int
outofbounds(int n, int nbits, int twoscomp)
{
	int max;

	if (twoscomp){
		max = (int)pow(2.0, (double)(nbits - 1)) - 1;
		if (n < -max - 1 || n > max)
			return 1;
	}
	else if (n < 0 || n > (int)pow(2.0, (double)(nbits)) - 1)
		return 1;
	return 0;
}