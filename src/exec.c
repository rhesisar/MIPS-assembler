#include "regs.h"
#include "mem.h"
#include "util.h"


void
exec_add(int *args)
{
    regs[args[0]].val = regs[args[1]].val + regs[args[2]].val;
}
void
exec_addi(int *args)
{
    regs[args[0]].val = regs[args[1]].val + args[2];
}
void
exec_and(int *args)
{
    regs[args[0]].val = regs[args[1]].val & regs[args[2]].val;
}
void
exec_beq(int *args)
{
    if (regs[args[0]].val == regs[args[1]].val){
        exec(regs[PC].val + 4);
        regs[PC].val += args[2] * 4;
    }
}
void
exec_bgtz(int *args)
{
    if (regs[args[0]].val > 0){
        exec(regs[PC].val + 4);
        regs[PC].val += args[1] * 4;
    }
}
void
exec_blez(int *args)
{
    if (regs[args[0]].val <= 0){
        exec(regs[PC].val + 4);
        regs[PC].val += args[1] * 4;
    }
}
void
exec_bne(int *args)
{
    if (regs[args[0]].val != regs[args[1]].val){
        exec(regs[PC].val + 4);
        regs[PC].val += args[2] * 4;
    }
}
void
exec_div(int *args)
{
    regs[LO].val = regs[args[0]].val / regs[args[1]].val;
    regs[HI].val = regs[args[0]].val % regs[args[1]].val;
}
void
exec_j(int *args)
{
    exec(regs[PC].val + 4);
    regs[PC].val = (args[0] - 1) * 4;
}
void
exec_jal(int *args)
{
    exec(regs[PC].val + 4);
    regs[RA].val = regs[PC].val + 8;
    regs[PC].val = (args[0] - 1) * 4;
}
void
exec_jr(int *args)
{
    exec(regs[PC].val + 4);
    if (regs[args[0]].val % 4)
        error("Address Error exception occured\n");
    regs[PC].val = regs[args[0]].val - 4;
}
void
exec_lui(int *args)
{
    regs[args[0]].val = args[1] << 16;
}
void
exec_lw(int *args)
{
    if ((regs[args[2]].val + args[1]) % 4)
        error("Address Error exception occured\n");
    regs[args[0]].val = (mem[regs[args[2]].val + args[1]] << 24)
                      | (mem[regs[args[2]].val + args[1] + 1] << 16)
                      | (mem[regs[args[2]].val + args[1] + 2] << 8)
                      | mem[regs[args[2]].val + args[1] + 3];
}
void
exec_mfhi(int *args)
{
    regs[args[0]].val = regs[HI].val;
}
void
exec_mflo(int *args)
{
    regs[args[0]].val = regs[LO].val;
}
void
exec_mult(int *args)
{
    long res = regs[args[0]].val * regs[args[1]].val;
    regs[LO].val = (int)(res & 0xFFFFFFFF);
    regs[HI].val = (int)((res >> 32) & 0xFFFFFFFF);
}
void
exec_or(int *args)
{
    regs[args[0]].val = regs[args[1]].val | regs[args[2]].val;
}
void
exec_rotr(int *args)
{
    regs[args[0]].val = (regs[args[1]].val >> args[2]) | (regs[args[1]].val << (32 - args[2]));
}
void
exec_sll(int *args)
{
    regs[args[0]].val = regs[args[1]].val << args[2];
}
void
exec_slt(int *args)
{
    regs[args[0]].val = regs[args[1]].val < regs[args[2]].val;
}
void
exec_srl(int *args)
{
    regs[args[0]].val = regs[args[1]].val >> args[2];
}
void
exec_sub(int *args)
{
    regs[args[0]].val = regs[args[1]].val - regs[args[2]].val;
}
void
exec_sw(int *args)
{
    if ((regs[args[2]].val + args[1]) % 4)
        error("Address Error exception occured\n");
    store32(regs[args[2]].val + args[1], regs[args[0]].val);
}
void
exec_xor(int *args)
{
    regs[args[0]].val = regs[args[1]].val ^ regs[args[2]].val;
}