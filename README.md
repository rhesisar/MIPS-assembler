# MIPS Assembler

Small, self-contained MIPS32 assembler written in C.

Reads a subset of MIPS assembly and emits 32-bit machine code (hex), with a clean separation between lexing/parsing, instruction decoding, and encoding.

## Summary
Parses MIPS source: ignores comments/whitespace, tokenizes ops + args, supports $t0/$s1/$ra as well as numeric $0..$31.

Validates & decodes operands: registers, immediates (dec/hex), jump targets; clear error messages on malformed lines/out-of-range fields.

Encodes instructions into 32-bit words across R/I/J formats and writes a .hex file (one word per line).

Includes scaffolding for interactive and step-by-step modes (auto/CLI mode fully implemented).

### Supported mnemonics (24):
ADD, ADDI, AND, BEQ, BGTZ, BLEZ, BNE, DIV, J, JAL, JR, LUI, LW, MFHI, MFLO, MULT, OR, ROTR, SLL, SLT, SRL, SUB, SW, XOR

## Build
`make` -> produces `./emul-mips`

## Usage
Automatic (assembler) mode:

`./emul-mips <input.s> <output.hex> <final.state>`

Example:

`./emul-mips tests/test.s tests/test.hex tests/test.state`

`output.hex`: assembled machine code (one 8-digit hex word per line)
`final.state`: reserved for emulator state (not implemented, file is created)

## Helper targets:
`make test-cli` -> sanity-checks CLI (files created/handled)
`make tests` -> runs the provided assembly tests (pytest harness)
`make clean`

## Project layout
```
src/
  extract.c,h    # lexer: read lines, strip comments, split op/args
  decoderaw.c,h  # parser: normalize op, type-check args, numeric parsing
  instfmts.h     # per-op format: type + field map + opcode/funct
  write.c,h      # encoder: bit-field packing -> 32-bit word
  const.h, defines.h, formats.h, shifts.h, regs.h, struct.h  # data & enums
  modes.c,h      # interactive / step / automatic entry points
  util.c,h       # safe wrappers (emalloc/efopen), unified error()
main.c           # argument dispatch
tests/*.s        # sample programs with expected outputs
test.py          # pytest-based runner used by `make tests`
Makefile
```

## Notes

Error handling: explicit, fail-fast diagnostics (line/argument context) via error().

Portability: single gcc build, no external deps.

Design: table-driven encoding (instfmts, shifts) keeps the assembler compact and easy to extend (add a row to support a new mnemonic).
