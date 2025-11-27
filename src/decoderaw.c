#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "regs.h"
#include "const.h"
#include "util.h"

static void getopn(Rawinst *rawinst, Inst *inst);
static void getargs(Rawinst *rawinst, Inst *inst);
static int regval(char *rawarg, int *regvalp);

/*
 * Returns 0 on success, 1 if op isn't recognized
 */
void
decoderaw(Rawinst *rawinst, Inst *inst)
{
    getopn(rawinst, inst);
	getargs(rawinst, inst);
	return;
}

/*
 * If op is recognized, returns EOF if end of line was found, 0 if not.
 * If op isn't recognized, returns 1.
*/ 
static void
getopn(Rawinst *rawinst, Inst *inst)
{
    int i;

    for (i = 0; rawinst->op[i] != '\0'; ++i){
        rawinst->op[i] = toupper(rawinst->op[i]);
    }
	for (inst->opn = 0; inst->opn < NUMBER_OPS; ++(inst->opn)){
		if (!strcmp(rawinst->op, instfmts[inst->opn].op))
			return;
	}
	error("Syntax error in assembly file: Operator %s not recognized\n", rawinst->op);
}
static void
getargs(Rawinst *rawinst, Inst *inst)
{
    int i;
    int r;
    char *p;

    for (i = 0; i < MAX_NUM_ARGS; ++i){
        switch (instfmts[inst->opn].args[i]) {
        case VOID:
            if (rawinst->args[i] != NULL)
                error("Syntax error in assembly file: Expected %d arguments for instruction %s, found at least %d\n", i, rawinst->op, i + 1);
            inst->args[i] = 0;
            break;
        case RD: /* FALLTHROUGH */
        case RS:
        case RT:
            if ((r = regval(rawinst->args[i], inst->args + i)) == 1)
                error("Syntax error in assembly file: Expected argument %d of instruction %s, found no argument\n", i + 1, rawinst->op);
            if (r == -1)
                error("Syntax error in assembly file: Expected register value for argument %d of instruction %s\n", i + 1, rawinst->op);
            break;
        case SA: /* FALLTHROUGH */
        case IMM:
        case TARGET:
            inst->args[i] = (int)strtol(rawinst->args[i], &p, 0);
            if (*p != '\0')
                error("Syntax error in assembly file: Invalid argument #%d value of instruction %s\n", i + 1, rawinst->op);
            if (instfmts[inst->opn].args[i] == TARGET){
                if (outofbounds(inst->args[i], elmtnbits[instfmts[inst->opn].args[i]], 0))
                    error("Out of bounds target value of instruction %s\n", rawinst->op);
            }
            else{
                if (outofbounds(inst->args[i], elmtnbits[instfmts[inst->opn].args[i]], 1))
                    error("Out of bounds immediate or offset value of instruction %s\n", rawinst->op);
                inst->args[i] = inttonbits(inst->args[i], elmtnbits[instfmts[inst->opn].args[i]]);
            }
            break;
        }
    }
    return;
}

static int
regval(char *rawarg, int *regvalp)
{
    int i;

    if (rawarg == NULL)
        return -1;
    if (rawarg[0] != '$')
        return 1;
    if (isdigit(rawarg[1])){
        *regvalp = (int)strtol(rawarg + 1, NULL, 10);
        if (*regvalp < 0 || *regvalp >= NUM_GPR)
            return 1;
    }
    else{
        for (i = 0; rawarg[i] != '\0'; ++i){
            rawarg[i] = tolower(rawarg[i]);
        }
        for (i = 0; i < NUM_GPR; ++i){
            if (!strcmp(rawarg + 1, regs[i].mnem))
                break;
        }
        if (i == NUM_GPR)
            return 1;
        *regvalp = i;
    }
    return 0;
}
