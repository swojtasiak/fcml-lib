[![CircleCI](https://circleci.com/gh/swojtasiak/fcml-lib/tree/master.svg?style=svg)](https://circleci.com/gh/swojtasiak/fcml-lib/tree/master)

# FCML
This is a general purpose machine code manipulation library for IA-32 and Intel 64 architectures.
The library supports UNIX-like systems as well as Windows and is highly portable. The FCML library
is free for commercial and non-commercial use as long as the terms of the LGPL license are met.

Currently it supports such features as:

  - A one-line disassembler
  - A one-line assembler
  - An experimental multi-pass load-and-go assembler (Multi line!)
  - Support for the Intel and AT&T syntax
  - An instruction renderer
  - An instruction parser
  - Instructions represented as generic models
  - UNIX/GNU/Linux and Windows (mingw, mingw64, cygwin, VS2008, VS2010, VS2013, VS2015) support
  - Portable - written entirely in C (no external dependencies)
  - C++ wrapper available
  - Supported instruction sets: MMX, 3D-Now!, SSE, SSE2, SSE3, SSSE3, 
	SSE4.1, SSE4.2, SSE4A, AVX, AVX2, AES, TBM, BMI1, BMI2, 
	HLE, ADX, CLMUL, RDRAND, RDSEED, FMA, FMA4, LWP, SVM, XOP, VMX, SMX

The following sections show a few examples in C++ language. Do not treat them as a reference manual or anything like that. They are here just to give you a general overview how the C++ API looks like. If you are interested in a bit more sophisticated use cases do not hesitate to look into the official manual on the http://www.fcml-lib.com.

## Assembling
The following code shows how easy it is to assemble anything in a true dynamic way! Notice that it assembles generic instruction model built using an instruction builder (IB) class.

```cpp
IntelDialect dialect;
AssemblerContext ctx( EntryPoint::OM_32_BIT, 0x401000 );
Assembler assembler(dialect);
Instruction instruction = IB(M_MOV).reg(EAX).offd( 0x40302010 );
AssemblerResult result;
assembler.assemble( ctx, instruction, result );
CodeIterator it = result.getCodeIterator();
while( it.hasNext() ) {
	fcml_uint8_t codeByte = it.next();
	...
}
```
## Parsing
Ok, so we know how to assemble generic instruction model, but what about textual instructions? Nothing easier than that! We can use a parser to achieve expected result:
```cpp
IntelDialect dialect;
ParserContext ctx(0x401000);
Parser parser(dialect);
ParserResult result;
parser.parse( ctx, _FT("mov eax, dword [0x0401000]"), result );
const Instruction &instruction = result.getInstruction();
...
```
## Disassembling
In order to disassemble anything we have to set up a dialect, disassembler context which holds instruction pointer and processor operating mode and then pass a piece of machine code directly to the disassembler instance. Error handling has been avoided intentionally to make code simpler.
```cpp
fcml_uint8_t code[] = {0x80, 0x54, 0x01, 0x02, 0x03};
IntelDialect dialect;
Disassembler disassembler( dialect );
DisassemblerContext ctx( code , sizeof( code ) );
ctx.setIP(0x401000);
ctx.setOperatingMode(EntryPoint::OM_32_BIT);
DisassemblerResult result;
disassembler.disassemble( ctx, result );
const Instruction &instruction = result.getInstruction();
```
### Rendering
Having the instruction model, we can render it using one of the dialects:
```cpp
Renderer renderer( dialect );
RenderConfig config;
fcml_cstring instructionMnemonic;
renderer.render( config, result, instructionMnemonic );
cout << instructionMnemonic << endl;
```
This code should print the following instruction: 
>adc byte ptr [ecx+eax+2],3

## Resources
* For more information do not hesitate to head over the official project site: http://www.fcml-lib.com
* You can download official binaries and source code archive directly from sourceforge: https://sourceforge.net/projects/fcml/files

LICENSE
---

LGPL 2.1 (https://www.gnu.org/licenses/lgpl-2.1.txt)

hsdis is dual licensed under LGPL 2.1 or Apache License 2.0

https://www.apache.org/licenses/LICENSE-2.0.txt

