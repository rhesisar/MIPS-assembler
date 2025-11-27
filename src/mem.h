#ifndef _MEM_H_
#define _MEM_H_

#include <stdio.h>

#include "const.h"

#define MEM_SIZE 4096
#define HEX_LEN 8

void exec(int addr);
void memtoinst(int i, Inst *inst);
void storeinsts(FILE *hexfp);
void store32(int n, int addr);

extern int mem[MEM_SIZE];

#endif