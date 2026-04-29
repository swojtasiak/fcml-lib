[![Build and Test](https://github.com/swojtasiak/fcml-lib/actions/workflows/build.yml/badge.svg)](https://github.com/swojtasiak/fcml-lib/actions/workflows/build.yml)

# FCML

A general purpose machine code manipulation library for IA-32 and Intel 64 architectures.
Written entirely in C, no external dependencies, supports UNIX-like systems and Windows.
Free for commercial and non-commercial use under the LGPL 2.1 license.

If you are building a disassembler, a binary analysis tool, a JIT compiler, a debugger,
or anything else that needs to encode or decode x86 instructions programmatically,
FCML gives you a clean, portable API to do it in C or C++.

## Features

- One-line assembler and disassembler
- Multi-pass load-and-go assembler (experimental)
- Intel and AT&T (GAS) syntax
- Instruction renderer and parser
- Generic instruction model (GIM) shared by assembler and disassembler
- C++ wrapper
- Windows support: MinGW, MinGW-w64, Cygwin, VS2017, VS2019
- Instruction sets: MMX, 3DNow!, SSE–SSE4A, AVX, AVX2, AVX-512, AES, TBM,
  BMI1, BMI2, HLE, ADX, CLMUL, FMA, FMA4, LWP, SVM, XOP, VMX, SMX, XEON PHI

## Installation

### GNU/Linux

Debian/Ubuntu packages:

```sh
sudo apt-get install fcml
sudo apt-get install libfcml-dev
```

From source:

```sh
autoreconf -i
./configure
make && make install
make check
```

Use `./configure --help` to see all options. See the `INSTALL` file in the
distribution archive for full details.

### Windows

Pre-built binaries are available on the [releases page](https://github.com/swojtasiak/fcml-lib/releases).

Visual Studio solutions for x86/x64 static and dynamic builds are in
`win32/vs2017` and `win32/vs2019`. MinGW builds follow the same autotools
process as Linux; for x86\_64 pass `--host=x86_64-w64-mingw32` to `configure`.

## Quick Start

FCML is built around a **Generic Instruction Model (GIM)** — a portable,
dialect-independent representation of an x86 instruction. Both the assembler
and disassembler speak GIM, making it easy to inspect, transform, and
round-trip between machine code and text.

### C

The C API uses lightweight structs and function calls to manage dialects,
assemblers, and disassemblers. Each component is initialized explicitly and
must be freed after use.

**Assembler** — populate a GIM and encode it to machine code:

```c
#include <stdio.h>
#include <fcml/fcml_assembler.h>
#include <fcml/fcml_intel_dialect.h>
#include <fcml/fcml_common_utils.h>

fcml_st_dialect *dialect;
fcml_fn_dialect_init_intel(FCML_INTEL_DIALECT_CF_DEFAULT, &dialect);

fcml_st_assembler *assembler;
fcml_fn_assembler_init(dialect, &assembler);

/* Describe "adc ax, 0x8042" as a GIM */
fcml_st_instruction instruction = {0};
instruction.mnemonic = "adc";
instruction.operands[0] = FCML_REG(fcml_reg_AX);
instruction.operands[1] = FCML_IMM16(0x8042);
instruction.operands_count = 2;

fcml_st_assembler_context context = {0};
context.assembler = assembler;
context.entry_point.op_mode = FCML_OM_32_BIT;
context.entry_point.ip = 0x401000;

fcml_st_assembler_result asm_result;
fcml_fn_assembler_result_prepare(&asm_result);

fcml_fn_assemble(&context, &instruction, &asm_result);

/* Print the chosen encoding byte-by-byte */
fcml_st_assembled_instruction *ins = asm_result.chosen_instruction;
for (int i = 0; i < ins->code_length; i++) {
    printf("%02x ", ins->code[i]);
}

fcml_fn_assembler_result_free(&asm_result);
fcml_fn_assembler_free(assembler);
fcml_fn_dialect_free(dialect);
```

Output:

```
66 15 42 80
```

**Disassembler** — decode raw machine code to a GIM and render it as text:

```c
#include <stdio.h>
#include <fcml/fcml_disassembler.h>
#include <fcml/fcml_intel_dialect.h>
#include <fcml/fcml_renderer.h>

fcml_uint8_t code[] = {0x80, 0x54, 0x01, 0x02, 0x03};

fcml_st_dialect *dialect;
fcml_fn_dialect_init_intel(FCML_INTEL_DIALECT_CF_DEFAULT, &dialect);

fcml_st_disassembler *disassembler;
fcml_fn_disassembler_init(dialect, &disassembler);

fcml_st_disassembler_context context = {0};
context.disassembler = disassembler;
context.entry_point.op_mode = FCML_OM_32_BIT;
context.entry_point.ip = 0x401000;
context.code = code;
context.code_length = sizeof(code);

fcml_st_disassembler_result result;
fcml_fn_disassembler_result_prepare(&result);

fcml_fn_disassemble(&context, &result);

/* Render the decoded instruction to human-readable text */
fcml_char buffer[FCML_REND_MAX_BUFF_LEN];
fcml_st_render_config render_config = {0};
fcml_fn_render(dialect, &render_config, buffer, sizeof(buffer), &result);

printf("%s\n", buffer);

fcml_fn_disassembler_result_free(&result);
fcml_fn_disassembler_free(disassembler);
fcml_fn_dialect_free(dialect);
```

Output:

```
adc byte ptr [ecx+eax+2],3
```

### C++

The C++ wrapper provides RAII-managed classes, a fluent instruction builder,
and exception-based error handling. All types live in the `fcml` namespace;
the examples below use `using namespace fcml;` for brevity.

Register and mnemonic constants are intentionally not exported from the shared
library, in order to avoid C++ ABI symbol dependencies. Instead, include the
corresponding `.cpp` files directly in your translation unit — they are
designed to be compiled this way:

```cpp
#include <fcml/fcml_registers.cpp>        // EAX, EBX, ...
#include <fcml/fcml_intel_mnemonics.cpp>  // fcml::intel::M_MOV, ...
#include <fcml/fcml_gas_mnemonics.cpp>    // fcml::gas::M_MOV, ...
```

Mnemonic constants are grouped by dialect into `fcml::intel` and `fcml::gas`,
reflecting the two supported syntaxes. Add the appropriate `using` directive
alongside `using namespace fcml;` depending on which dialect your code uses.

**Assembler** — build instructions with the fluent `IB` builder and encode them:

```cpp
#include <cstdio>
#include <fcml/fcml_assembler.hpp>
#include <fcml/fcml_intel_dialect.hpp>
#include <fcml/fcml_intel_mnemonics.hpp>
#include <fcml/fcml_intel_mnemonics.cpp>
#include <fcml/fcml_registers.hpp>
#include <fcml/fcml_registers.cpp>

using namespace fcml;
using namespace fcml::intel;

IntelDialect dialect;
Assembler assembler(dialect);
AssemblerContext ctx(EntryPoint::OM_32_BIT, 0x401000);

/* "mov eax, dword ptr [0x40302010]" built with the instruction builder */
Instruction instruction = IB(M_MOV).reg(EAX).offd(0x40302010);

AssemblerResult result;
assembler.assemble(ctx, instruction, result);

/* Print the bytes of the chosen encoding */
const AssembledInstruction *ins = result.getChosenInstruction();
for (fcml_usize i = 0; i < ins->getCodeLength(); i++) {
    printf("%02x ", ins->getCode()[i]);
}
```

Output:

```
a1 10 20 30 40
```

**Parser** — parse a text instruction directly into a GIM:

```cpp
#include <fcml/fcml_parser.hpp>
#include <fcml/fcml_intel_dialect.hpp>
#include <fcml/fcml_registers.cpp>

using namespace fcml;

IntelDialect dialect;
Parser parser(dialect);
ParserContext ctx(0x401000);
ParserResult result;

parser.parse(ctx, _FT("mov eax, dword ptr [0x0401000]"), result);

const Instruction &instruction = result.getInstruction();
```

**Disassembler + Renderer** — decode machine code and render it to a string:

```cpp
#include <iostream>
#include <fcml/fcml_disassembler.hpp>
#include <fcml/fcml_intel_dialect.hpp>
#include <fcml/fcml_renderer.hpp>
#include <fcml/fcml_registers.cpp>

using namespace fcml;

fcml_uint8_t code[] = {0x80, 0x54, 0x01, 0x02, 0x03};

IntelDialect dialect;
Disassembler disassembler(dialect);

DisassemblerContext ctx(code, sizeof(code));
ctx.setIP(0x401000);
ctx.setOperatingMode(EntryPoint::OM_32_BIT);

DisassemblerResult result;
disassembler.disassemble(ctx, result);

/* The decoded GIM is available for programmatic inspection */
const Instruction &instruction = result.getInstruction();

/* Render it to a human-readable string */
Renderer renderer(dialect);
RenderConfig config;
fcml_cstring text;
renderer.render(config, result, text);

std::cout << text << std::endl;
```

Output:

```
adc byte ptr [ecx+eax+2],3
```

## Resources

- **Project site:** https://www.fcml-lib.com
- **Manual:** http://www.fcml-lib.com/manual.html — comprehensive reference covering
  the Generic Instruction Model, assembler and disassembler configuration, the parser,
  renderer, error handling, and the full C and C++ APIs
- **Releases:** https://github.com/swojtasiak/fcml-lib/releases

## License

LGPL 2.1 — https://www.gnu.org/licenses/lgpl-2.1.txt

hsdis is dual licensed under LGPL 2.1 or Apache License 2.0 —
https://www.apache.org/licenses/LICENSE-2.0.txt
