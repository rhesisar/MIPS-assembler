#include <stddef.h>

#include "const.h"
#include "exec.h"

const int elmtnbits[NUM_ELMTS] = {
    [RS] = 5,
    [RT] = 5,
    [RD] = 5,
    [SA] = 5,
    [IMM] = 16,
    [TARGET] = 26
};
const Instfmt instfmts[NUMBER_OPS] = {
    { RTYPE,    "ADD",  0x20,   { RD,           RS,     RT   }, exec_add    },
    { ITYPE,    "ADDI", 0x08,   { RT,           RS,     IMM  }, exec_addi   },
    { RTYPE,    "AND",  0x24,   { RD,           RS,     RT   }, exec_and    },
    { ITYPE,    "BEQ",  0x04,   { RS,           RT,     IMM  }, exec_beq    },
    { ITYPE,    "BGTZ", 0x07,   { RS,           IMM,    VOID }, exec_bgtz   },
    { ITYPE,    "BLEZ", 0x06,   { RS,           IMM,    VOID }, exec_blez   },
    { ITYPE,    "BNE",  0x05,   { RS,           RT,     IMM  }, exec_bne    },
    { RTYPE,    "DIV",  0x1A,   { RS,           RT,     VOID }, exec_div    },
    { JTYPE,    "J",    0x02,   { TARGET,       VOID,   VOID }, exec_j      },
    { JTYPE,    "JAL",  0x03,   { TARGET,       VOID,   VOID }, exec_jal    },
    { RTYPE,    "JR",   0x08,   { RS,           VOID,   VOID }, exec_jr     },
    { ITYPE,    "LUI",  0x0F,   { RT,           IMM,    VOID }, exec_lui    },
    { ITYPE,    "LW",   0x23,   { RT,           IMM,    RS   }, exec_lw     },
    { RTYPE,    "MFHI", 0x10,   { RD,           VOID,   VOID }, exec_mfhi   },
    { RTYPE,    "MFLO", 0x12,   { RD,           VOID,   VOID }, exec_mflo   },
    { RTYPE,    "MULT", 0x18,   { RS,           RT,     VOID }, exec_mult   },
    { RTYPE,    "NOP",  0x00,   { VOID,         VOID,   VOID }, NULL        },
    { RTYPE,    "OR",   0x25,   { RD,           RS,     RT   }, exec_or     },
    { RTYPE,    "ROTR", 0x02,   { RD,           RT,     SA   }, exec_rotr   },
    { RTYPE,    "SLL",  0x00,   { RD,           RT,     SA   }, exec_sll    },
    { RTYPE,    "SLT",  0x2A,   { RD,           RS,     RT   }, exec_slt    },
    { RTYPE,    "SRL",  0x02,   { RD,           RT,     SA   }, exec_srl    },
    { RTYPE,    "SUB",  0x22,   { RD,           RS,     RT   }, exec_sub    },
    { ITYPE,    "SW",   0x2B,   { RT,           IMM,    RS   }, exec_sw     },
    { RTYPE,    "XOR",  0x26,   { RD,           RS,     RT   }, exec_xor    }
};
const int shifts[NUM_INST_TYPES][NUM_ELMTS] = {
	[RTYPE] = { [RS] = 21,		[RT] = 16,	[RD] = 11, [SA] = 6, [OPCODE] = 0 },
	[ITYPE] = { [OPCODE] = 26,	[RS] = 21,	[RT] = 16, [IMM] = 0 },
	[JTYPE] = { [OPCODE] = 26,	[TARGET] = 0 }
};