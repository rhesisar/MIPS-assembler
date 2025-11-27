#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>

#define MAX(a,b) (a>b?a:b)

void *emalloc(size_t size);
FILE *efopen(const char *pathname, const char *mode);
void error(const char *fmt, ...);
int inttonbits(int n, int nbits);
int nbitstoint(int n, int nbits);
int outofbounds(int n, int nbits, int twoscomp);

#endif