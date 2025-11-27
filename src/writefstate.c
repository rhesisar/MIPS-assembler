#include <stdio.h>

#include "regs.h"

void
writefstate(FILE *fstatefp)
{
    int i;

    for (i = 0; i < NUM_GPR; ++i){
        fprintf(fstatefp, "$%02d: %d\n", i, regs[i].val);
    }
    fprintf(fstatefp, "LO: %d\nHI: %d\n", regs[LO].val, regs[HI].val);
    return;
}