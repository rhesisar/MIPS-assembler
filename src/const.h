#ifndef _CONST_H_
#define _CONST_H_

#define MAX_NUM_ARGS 3
#define MAX_OP_SIZE 4

#define VOID -1

typedef struct instfmt {
	int type;
    char *op;
    int opval;
    int args[MAX_NUM_ARGS];
	void (*exec)(int args[]);
} Instfmt;
typedef struct rawinst {
	char op[MAX_OP_SIZE + 1];
	char *args[MAX_NUM_ARGS];
} Rawinst;
typedef struct inst {
	int opn;
	int args[MAX_NUM_ARGS];
} Inst;

typedef struct reg {
	char *mnem;
	int val;
} Reg;

enum types {
	RTYPE,
	ITYPE,
	JTYPE,
	NUM_INST_TYPES
};
enum elmts {
	FUNC,
	IMM,
    OPCODE,
    RD,
    RS,
    RT,
    SA,
    TARGET,
	NUM_ELMTS
};
enum ops {
	ADD,
	ADDI,
	AND,
	BEQ,
	BGTZ,
	BLEZ,
	BNE,
	DIV,
	J,
	JAL,
	JR,
	LUI,
	LW,
	MFHI,
	MFLO,
	MULT,
	NOP,
	OR,
	ROTR,
	SLL,
	SLT,
	SRL,
	SUB,
	SW,
	XOR,
	NUMBER_OPS
};

extern const int elmtnbits[NUM_ELMTS];
extern const Instfmt instfmts[NUMBER_OPS];
extern const int shifts[NUM_INST_TYPES][NUM_ELMTS];

#endif