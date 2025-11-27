#ifndef _REGS_H_
#define _REGS_H_

#include "const.h"

enum GPR {
	ZERO,
    AT,
	V0,
	V1,
	A0,
	A1,
	A2,
	A3,
	T0,
	T1,
	T2,
	T3,
	T4,
	T5,
	T6,
	T7,
	S0,
	S1,
	S2,
	S3,
	S4,
	S5,
	S6,
	S7,
	T8,
	T9,
	K0,
	K1,
	GP,
	SP,
	FP,
	RA,
    NUM_GPR
};
enum SPR {
	PC = NUM_GPR,
	HI,
	LO,
	NUM_REGS
};

extern Reg regs[];

#endif