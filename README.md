# MIPS Assembler and Simulator

Small MIPS32 assembler and emulator written in C (~1k non empty lines) for a university project.

It reads a subset of MIPS assembly, encodes each instruction into a 32 bit machine word, writes a hex file, then loads that hex into a simple byte addressed memory and simulates execution to produce a final CPU state.

## Features

- Supports a core integer subset of the MIPS32 ISA (25 instructions):

  `ADD, ADDI, AND, BEQ, BGTZ, BLEZ, BNE, DIV, J, JAL, JR, LUI, LW, MFHI, MFLO, MULT, NOP, OR, ROTR, SLL, SLT, SRL, SUB, SW, XOR`

- Register operands:
  - Accepts both numeric and mnemonic registers: `$0`..`$31` and `$zero`..`$ra`.
  - Backed by a small `Reg` table that stores each register mnemonic and its value.

- Immediate, offset, and target handling:
  - Parses decimal and hexadecimal immediates (`10`, `-5`, `0x12`, `-0x156`, etc.).
  - Supports base+offset addressing for loads and stores (for example `LW $1, 40($2)`).
  - Checks ranges for immediates and jump targets with two's complement bounds and reports clear errors.

- Table driven encoding:
  - Each instruction is described by an `Instfmt` entry:
    - instruction type (R / I / J),
    - mnemonic (`"ADD"`),
    - opcode or function code,
    - argument kinds (RS, RT, RD, SA, IMM, TARGET),
    - pointer to the corresponding `exec_*` function.
  - A `shifts` table and `elmtnbits` array describe how many bits and which bit positions each field occupies.
  - `writehex` uses these tables to pack arguments into a 32 bit word and writes one hex line per instruction.

- Simple CPU simulator:
  - 32 general purpose registers plus special registers `PC`, `HI`, and `LO`.
  - Byte addressed memory of size `MEM_SIZE` (4096 bytes).
  - `storeinsts` reads the hex output and fills the memory array.
  - `memtoinst` decodes a 32 bit word back into an `Inst` using the same format table.
  - `exec` dispatches to the appropriate `exec_*` function (for example `exec_add`, `exec_beq`, `exec_lw`) and updates registers and memory.
  - Misaligned memory accesses for word loads/stores are detected and reported.

- Final state export:
  - After execution finishes, the simulator writes a small final state file listing all general purpose registers and the contents of `HI` and `LO` in a simple text format.

- Command line interface:
  - Single binary: `emul-mips`.
  - Automatic mode is implemented and used by the test suite.
  - Interactive and step by step modes are present as stubs and can be extended later.

## Building

Requires a POSIX system with `gcc` and `make`.

```sh
make
```

This builds the `emul-mips` executable.

## Usage

The implemented automatic mode expects three arguments:

```sh
./emul-mips input.s output.hex final_state.txt
```

- `input.s`       MIPS assembly source file  
- `output.hex`    assembled program, one 32 bit word per line in hexadecimal  
- `final_state.txt`  final register and HI/LO state written by the simulator  

Example:

```sh
./emul-mips tests/arithmetic.s out.hex out.state
```

## Tests

The repository includes a small Python / pytest based test harness and sample programs:

```sh
make tests
```

- `tests/*.s` contain MIPS programs with two annotated sections:
  - `EXPECTED_ASSEMBLY` lists the expected 32 bit words for each instruction.
  - `EXPECTED_FINAL_STATE` lists the expected values for selected registers and `HI` / `LO`.
- `test.py` assembles and runs each test file with `emul-mips`, then:
  - compares the generated hex output with `EXPECTED_ASSEMBLY`,
  - compares the final CPU state with `EXPECTED_FINAL_STATE`.

There is also a simple CLI smoke test target:

```sh
make test-cli
```

which checks that the automatic mode creates the expected output files.

## Layout

- `src/`
  - `main.c`      entry point and mode selection (interactive, step, automatic)
  - `modes.c`     command line modes; automatic mode wires everything together
  - `extract.c`   lexical parsing of one assembly line into a `Rawinst`
  - `decoderaw.c` conversion from `Rawinst` to an `Inst` (mnemonic lookup, args decoding)
  - `const.c/h`   instruction format table, bit widths, and shift positions
  - `exec.c/h`    per instruction `exec_*` functions implementing the MIPS semantics
  - `mem.c/h`     memory array, hex loading, decoding, and execution loop
  - `regs.c/h`    register file and register mnemonics
  - `util.c/h`    helpers for error reporting, allocation, bounds checks, and bit conversions
  - `writehex.c/h`    encoder from `Inst` to 32 bit hex
  - `writefstate.c/h` writer for the final CPU state file

- `tests/`
  - Sample MIPS programs exercising arithmetic, memory access, branches, jumps, and a few delay slot scenarios.

- `test.py`
  - pytest based test runner used by `make tests`.

- `Makefile`
  - build, clean, and test targets.

## Known limitations

- No symbolic labels in assembly files. Branches and jumps use numeric offsets / targets.
- No pseudo instructions, macros, or assembler directives.
- Only a subset of the MIPS32 integer instruction set is implemented (no floating point, no syscalls).
- Memory is a fixed size byte array; there is no MMU or exception handling beyond basic checks.
- Interactive and step by step modes are present in the code but are not yet fully implemented.
