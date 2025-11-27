#include <stdio.h>

#include "const.h"

int
writehex(Inst *inst, FILE *hexfp)
{
    int i, hex;

    hex = 0;

    if (inst->opn == ROTR)
        hex += 1 << 21;
    hex += instfmts[inst->opn].opval << shifts[ instfmts[inst->opn].type ][OPCODE];

    for (i = 0; i < MAX_NUM_ARGS; ++i){
        hex += inst->args[i] << shifts[ instfmts[inst->opn].type ] [ instfmts[inst->opn].args[i] ];
    }

    fprintf(hexfp, "%08x\n", hex);
    return 0;
}

