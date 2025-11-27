#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem.h"
#include "const.h"
#include "exec.h"
#include "util.h"
#include "regs.h"

int mem[MEM_SIZE];

void
exec(int addr)
{
    Inst inst;

	memtoinst(addr, &inst);
    printf("PC = %d, Executing op = %d \"%s\", args = {%d, %d, %d}\n", regs[PC].val/4, inst.opn, instfmts[inst.opn].op, inst.args[0], inst.args[1], inst.args[2]);
	instfmts[inst.opn].exec(inst.args);
}
void
storeinsts(FILE *hexfp)
{
    int i;
    int hex;
    char s[9];

    for (i = 0; fgets(s, HEX_LEN + 1, hexfp); i += 4){
        fgetc(hexfp); /* Read newline character */
        hex = strtol(s, NULL, 16);
        store32(i, hex);
    }
}

void
store32(int addr, int n)
{
    mem[addr] = (n >> 24);
    mem[addr + 1] = (n >> 16) & 255;
    mem[addr + 2] = (n >> 8) & 255;
    mem[addr + 3] = n & 255;
}

void
memtoinst(int i, Inst *inst)
{
    int opval;
    int hex;

    hex = (mem[i] << 24) + (mem[i + 1] << 16) + (mem[i + 2] << 8) + mem[i + 3];
    opval = (hex >> 26) & 63;
    if (opval == 0){
        opval = hex & 63;
        for (inst->opn = 0; inst->opn < NUMBER_OPS; ++(inst->opn)){
            if (instfmts[inst->opn].opval == opval && instfmts[inst->opn].type == RTYPE){
                if (!strcmp(instfmts[inst->opn].op, "ROTR") && ((hex >> 21) & 1) == 0)
                    continue;
                if (!strcmp(instfmts[inst->opn].op, "NOP"))
                    continue;
                break;
            }
        }
    }
    else{
        for (inst->opn = 0; inst->opn < NUMBER_OPS; ++(inst->opn)){
            if (instfmts[inst->opn].opval == opval && instfmts[inst->opn].type != RTYPE)
                break;
        }
    }
    
    for (i = 0; i < MAX_NUM_ARGS; ++i){
        if (instfmts[inst->opn].args[i] != VOID){
            inst->args[i] = (hex >> shifts[ instfmts[inst->opn].type ][ instfmts[inst->opn].args[i] ]) & ((int)pow(2.0, (double)elmtnbits[instfmts[inst->opn].args[i]]) - 1);
            switch (instfmts[inst->opn].args[i]){
            case SA: /* FALLTHROUGH */
            case IMM:
                inst->args[i] = nbitstoint(inst->args[i], elmtnbits[instfmts[inst->opn].args[i]]);
                break;
            }
        }
    }
    return;
}
/*
void
loadinst(
    
)
*/