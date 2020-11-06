[![CircleCI](https://circleci.com/gh/swojtasiak/fcml-lib/tree/master.svg?style=svg)](https://circleci.com/gh/swojtasiak/fcml-lib/tree/master)

# FCML
This is a general purpose machine code manipulation library for IA-32 and Intel 64 architectures.
The library supports UNIX-like systems as well as Windows and is highly portable. The FCML library
is free for commercial and non-commercial use as long as the terms of the LGPL license are met.

## Features

Currently it supports such features as:

  - A one-line disassembler
  - A one-line assembler
  - An experimental multi-pass load-and-go assembler (Multi line!)
  - Support for the Intel and AT&T syntax
  - An instruction renderer
  - An instruction parser
  - Instructions represented as generic models
  - UNIX/GNU/Linux and Windows (mingw, mingw64, cygwin, VS2017, VS2019) support
  - Portable - written entirely in C (no external dependencies)
  - C++ wrapper available
  - Supported instruction sets: MMX, 3D-Now!, SSE, SSE2, SSE3, SSSE3, 
	SSE4.1, SSE4.2, SSE4A, AVX, AVX2, AES, TBM, BMI1, BMI2, 
	HLE, ADX, CLMUL, RDRAND, RDSEED, FMA, FMA4, LWP, SVM, XOP, VMX, SMX, AVX-512, XEON PHI

The following sections show a few examples in C and C++ language. Do not treat them as a reference manual or anything like that. They are here just to give you a general overview how the API looks like. If you are interested in a bit more sophisticated use cases do not hesitate to look into the official manual on the http://www.fcml-lib.com/manual.html.

## Installation

The following chapters explain how to download and install FCML under GNU/Linux and Windows systems.

### Downloading

All release packages code can be found here: https://github.com/swojtasiak/fcml-lib/releases 

### GNU/Linux

If you use Debian based GNU/Linux distribution like Ubuntu or Debian itself you can install the library
from packages:

```shell script
sudo apt-get install fcml
```

In order to install development files get the following package:

```shell script
sudo apt-get install libfcml-dev
```

In case of other GNU/Linux distributions you may have to install it manually. FCML uses autotools, so its installing process is standardized and follows all autotools rules. Consequently everything you have to do is to execute the following commands:

```shell script
autoreconf -i
./configure
make && make install
```

Then, in order to check if everything works you should also execute unit tests using the following command:

```shell script
make check
```

It should return a test execution report, like this one:

```
Test [Internal unit tests]: 
Run Summary:      Type         Ran     Passed     Failed 
                suites          13         13          0 
                 tests         184        184          0 
               asserts        1772       1772          0 
PASS: fcml_internal_check 
============= 
1 test passed 
============= 
…
Test [Public API tests]: 
Run Summary:      Type         Ran     Passed     Failed 
                suites          28         28          0 
                 tests         610        610          0 
               asserts        8096       8096          0 
PASS: fcml_public_check 
============= 
1 test passed 
============= 
```

The result may vary a bit depending on autotools version and used test driver.

FCML does not have any external dependencies and consequently the build process is quite straightforward and is very unlikely to fail. Anyway, if needed you can customize the build process by adding additional options to the configure script. For instance, in order to build only the static library, you can disable the shared one by adding `--disable-shared` option as follows:

```shell script
./configure --disable-shared
```

Use `--help` parameter in order to display all available configuration options. Do not hesitate to read INSTALL file in the distribution archive, which describes installation process in every details.

If you have Doxygen installed the API documentation will be also generated.

### Windows

Building Windows binaries is a bit more complicated and it is why there are dedicated archives with pre-built libraries. 

#### MinGW

In case of MinGW the build process is quite straightforward as long as we do not want to build a library with undecorated symbol names. In such a case the configure script should be used the same way as in case of UNIX-like systems. For instance:

```shell script
./configure
make && make install
```

Remember that such libraries are not compatible with Visual Studio, because Visual Studio uses [different symbol decorations](http://www.transmissionzero.co.uk/computing/advanced-mingw-dll-topics/). Of course you can generate undecorated symbols using the MinGW tools chain, but it is a bit more advanced task and it is out of scope of this manual (see dlltool and module definition files).

If you would like to build binaries for x86_64 architecture you have to install [mingw-w64](http://mingw-w64.sourceforge.net/) and then set the appropriate host running the configure script:

```shell script
$ ./configure --host=x86_64-w64-mingw32
***************************************************
fcml version 1.2.2 
Host CPU.........: x86_64 
Host OS:.........: mingw32 
Prefix:..........: /usr/local 
Debug Build......: no 
Shared Library...: yes 
Compiler.........: x86_64-w64-mingw32-gcc -std=gnu99 -g -O2 
Linker...........: C:/mingw64/x86_64-w64-mingw32/bin/ld.exe 
Doxygen..........: NONE 
***************************************************
```

In the report "Host CPU" should point to the appropriate CPU architecture.

If you have Doxygen installed the API documentation will also be generated. As you could see in the example above Doxygen was not found.

#### Visual Studio

There are solutions prepared for Visual Studio available in win32/vs2017 and win32/vs2019 directories. Everything
you need to do is to load such a solution using your Visual Studio and click build. All paths are relative to the 
distribution directory so everything should be built without any problems. You can also choose between a few 
configurations in order to build static or dynamic libraries. All the solutions support x86 and x64 builds.

Remember that header files available in ${DIST_DIR}/include have to be added as include directory to the destination 
project in order to use the built libraries.

Visual Studio Express is fully supported, so if you do not have access to the full version, you can build the
library using the express version. 

## Quick Start

The following sections show some really basic use cases of C and C++ API. Comprehensive documentation is available here: [manual](http://www.fcml-lib.com/manual.html). 

### C language

A quick guide how to use the library in C language.

#### Assembler
The FCML assembler allows us to assemble instructions encoded in a [generic instruction model](http://www.fcml-lib.com/manual.html#generic_instruction_model) 
(called GIM in the next sections) prepared by the user or returned as a result of the instruction parsing process. 
Therefore the first thing is the GIM. For the purpose of this chapter we will prepare it on our own, but you can also 
convert a textual instruction to a GIM instance using FCML parsers (see: Parser for more details about parsing).

So for instance the GIM for a simple instruction: "adc ax, 0x8042" can be encoded as follows:
```c	
#include <fcml_common.h>
 
fcml_st_instruction instruction = {0};
instruction.mnemonic = "adc";
instruction.operands[0] = FCML_REG( fcml_reg_AX );
instruction.operands[1] = FCML_IMM16( 0x8042 );
instruction.operands_count = 2;
```

The structure fcml_st_instruction is defined in the [fcml_common.h](http://www.fcml-lib.com/api/fcml__common_8h.html) header file. It is the main structure of the GIM model.
Utility macros FCML_REG and FCML_IMM16 are defined in the [fcml_common_utils.h](http://www.fcml-lib.com/api/fcml__common__utils_8h.html) header file and can be used just to make 
source code shorter. See the page API where all utility macros and functions are described.

The second line allocates space for the instruction model. In the third line we specify an instruction by its mnemonic
(remember that mnemonic is dialect dependant). Line four defines a register operand with one AX general purpose 
register. Line five sets the second operand to 16-bit unsigned immediate value and in the last line, the 
number of used operands is specified.

Now when the GIM is ready it is time to prepare the assembler which will be able to assemble the model. In order to 
initialize the assembler an initialized dialect instance is needed. Thanks to the dialects the library is able to
use different instruction syntaxes like the Intel or AT&T. So let's prepare an instance of the Intel dialect:

```c	
#include <fcml_intel_dialect.h>
 
fcml_st_dialect *dialect;
fcml_ceh_error error = fcml_fn_dialect_init_intel(FCML_INTEL_DIALECT_CF_DEFAULT, &dialect);
if (error) {
    printf("Cannot initialize the Intel dialect, error: %d\n", error);
    exit(EXIT_FAILURE);
}
```

As you can see there are dedicated functions to create different dialects. Every function can also take additional
 parameters used to configure the initialized dialect instance. In theory it should be possible to implement every 
 existing dialect for FCML but currently only the Intel and AT&T (called GAS) dialects are supported. For the sake
  of the example the Intel dialect (the preferred one) is used.

The dialect is ready, so let's initialize the assembler using the [fcml_fn_assembler_init](http://www.fcml-lib.com/api/fcml__assembler_8h.html#ae8182220144272c8f233b7782da76a3c) function:

```c	
fcml_st_assembler *assembler;
error = fcml_fn_assembler_init(dialect, &assembler);
```

To make the code a bit clearer error handling has been avoided in this specific case, but it should be implemented in 
the same way as in the case of dialect initialization. All possible error codes are defined in the 
[fcml_errors.h](http://www.fcml-lib.com/api/group__ERRORS__GROUP.html#ga88406cc59b708d9f4de9286d254dd10a) header file.

Once both the dialect and the assembler are initialized, there is the last thing to be done before assembling is
 possible. It is an assembler result structure. This structure is reusable, therefore it has to be prepared in 
 the right way in order to allow assembler to reuse it correctly. To do so, a manually allocated structure 
 has to be passed to the [fcml_sn_assembler_result_prepare](http://www.fcml-lib.com/api/fcml__assembler_8h.html#a3a827d482043c2fc1c6766e71f047484) function:

```c	
fcml_st_assembler_result asm_result;
fcml_fn_assembler_result_prepare(&asm_result);
```

Notice that we have not used the partial initialization to clear the memory held by the allocated structure this time.
 We could omit it because it is the mentioned function that clears the structure for us.

That is all, assembler is prepared to do its job, so let's try to assemble the model from the example above.

The main structure that has to be properly prepared for the assembler to work is [fcml_st_assembler_context](http://www.fcml-lib.com/api/fcml__assembler_8h.html#ac72d9fd39163fe6cabf8c2e87e64bae7).
It consists of the previously initialized assembler instance which should be used to assemble machine code, 
some configuration flags we can use to configure assembling process and an [entry point](http://www.fcml-lib.com/manual.html#un-entry-point) which will be used to
inform the assembler about the code segment the instruction is destined for. The assembler context itself 
can be initialized on the stack but it is very important to clear memory it uses before passing it to the assembler.
We should do it just to set all configuration options and other parameters to their default values. For example 
the following source code shows the proper way to initialize the assembler context:

```c	
fcml_st_assembler_context context = {0};
```

Having the context set up, we should provide an assembler instance first:

```c	
context.assembler = assembler;
```

Now it is time to set the configuration flags. For beginners the most useful option is called [enable_error_messages](http://www.fcml-lib.com/api/structfcml__st__assembler__conf.html#a9848f423218cd1c2ad600575e8c723da). 
It is used to enable support for textual error messages, which can be very useful when an error occurs, so let's set it to true:

```c
context.configuration.enable_error_messages = FCML_TRUE;
```

As you noticed without any doubt we have used a strange constant `FCML_TRUE` in place of "true" for the boolean variable.
This constant is defined inside the [fcml_types.h](http://www.fcml-lib.com/api/fcml__types_8h.html) header file and should be used whenever true (`FCML_TRUE`) or false 
(`FCML_FALSE`) should be directly set for given variable, but of course every not zero value can be used in case of true.

There is one more configuration option which can be interesting now, it is [increment_ip](http://www.fcml-lib.com/api/structfcml__st__assembler__conf.html#a954159936ace6f452ae9f6727ea2bfb5) but we will describe it later.

The last thing to do is to set up the entry point correctly:

```c	
context.entry_point.addr_form = FCML_MO_32_BIT;
context.entry_point.ip = 0x401000;
```

As you can see, processor operating mode has been set to 32 bits and EIP register to 0x401000 which is the default 
address for many assemblers/compilers. We have not set the operand size attribute or address size attribute so they
both are set to their default values, which are 32 bits for both of them in case of the chosen processor operating mode.

The full source code for initializing the assembler context:

```c	
fcml_st_assembler_context context = {0};
context.assembler = assembler;
context.configuration.enable_error_messages = FCML_TRUE;
context.entry_point.addr_form = FCML_OM_32_BIT;
context.entry_point.ip = 0x401000;
```

Now we are ready to assemble the GIM we prepared earlier, so let's do that.

In order to assemble an instruction model, we have to use fcml_fn_assemble function defined by fcml_assembler.h 
header file. This is the definition of the function:

```c	
LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_assemble( 
    fcml_st_assembler_context *context, 
    const fcml_st_instruction *instruction, 
    fcml_st_assembler_result *result);
```

We have everything we need to fill its arguments. The following code shows how to invoke the function with
 structures we have already prepared:

```c	
error = fcml_fn_assemble(&context, &instruction, &asm_result);
if( error ) {
    ...
}
```

If everything succeeded, the error variable is set to [FCML_CEH_GEC_NO_ERROR](http://www.fcml-lib.com/api/group__ERRORS__GROUP.html#ga88406cc59b708d9f4de9286d254dd10a) and asm_result
 contains the assembled machine code.

Let's take a look at [fcml_st_assembler_result](http://www.fcml-lib.com/api/structfcml__st__assembler__result.html) structure. The field errors contains textual error messages
if function failed. Assembled instructions are stored as a chain of [fcml_st_assembled_instruction](http://www.fcml-lib.com/api/structfcml__st__assembled__instruction.html) structures.
A chain was used, because there are instructions that can be assembled to more than one form. 
For example some of them can be assembled to even three different pieces of machine code. 
It is why the chain is just convenient here. Fortunately you do not have to analyse all available forms
in order to identify the best one considering your processor operating mode, size attributes, etc.
The most relevant piece of machine code is chosen by the assembler and is returned in chosen_instruction field.
The last field number_of_instructions contains number of instruction forms available in the chain. 
Although it can be calculated going through all instructions in the chain, it is needed rather
frequently so it is better to have it on hand.

The structure [fcml_st_assembled_instruction](http://www.fcml-lib.com/api/structfcml__st__assembled__instruction.html) holds information related to one assembled instruction and can contain 
optional warning messages if the instruction was assembled correctly, but FCML assembler had some objections 
to the generated machine code. The assembled machine code as a pointer to an array of bytes is available
through the field code and the array length is stored in code_length field.

As you may remember I pointed out that [fcml_st_assembler_result](http://www.fcml-lib.com/api/structfcml__st__assembler__result.html) structure is reusable and as so the same
structure can be used for every invocation of fcml_fn_assemble function. It is very convenient, because we
do not need to allocate and free this structure for every instruction being assembled. It is the assembler
which is responsible for freeing everything that assembler result contains like generated machine code 
or warning messages and reusing it.

When we are speaking about assembling multiple instructions one by one and reusing some assembler parameters, 
it is time to point out configuration flag increment_ip mentioned earlier. This flag can be used in order to 
force the assembler to increase the instruction pointer using the length of the chosen instruction (Length of
the machine code generated for it to be more specific.) after every successful invocation of the assembler. 
It is very convenient if we assemble instructions that follows each other in the code segment, because we do 
not need to calculate the instruction pointer for them every time.

When the whole machine code is ready and there is nothing more to assemble, we should free all resources
that are not needed any more. The first structure we have to free is [fcml_st_assembler_result](http://www.fcml-lib.com/api/structfcml__st__assembler__result.html), because 
even if it is allocated on the stack it might still contain the assembled machine code and potential
warning messages. You should call http://www.fcml-lib.com/api/fcml__assembler_8h.html#af7c11065d9016903daf8ae0a3b1d4d74 in order to free this information. 
Take into account that this function will not free the structure itself, so memory used by it has to be
freed anyway or the structure can be still reused by another invocation of the assembler (Remember
that you are owner of the structure and that you are responsible for freeing it at some point.)


```c	
fcml_fn_assembler_result_free(&asm_result);
```

We should also free the assembler itself and the dialect:

```c	
fcml_fn_assembler_free(assembler);
fcml_fn_dialect_free(dialect);
```

Remember that dialect has to be freed after the assembler.

The following source code assembles the generic instruction model from the example above:

```c
#include <stdio.h>
#include <stdlib.h>
 
#include <fcml/fcml_intel_dialect.h>
#include <fcml/fcml_assembler.h>
#include <fcml/fcml_common_utils.h>
 
int main(int argc, char **argv) {
 
    fcml_ceh_error error;
 
    /* Initializes the Intel dialect instance. */
    fcml_st_dialect *dialect;
    if ((error = fcml_fn_dialect_init_intel(FCML_INTEL_DIALECT_CF_DEFAULT, &dialect))) {
        fprintf(stderr, "Can not initialize Intel dialect: %d\n", error);
        exit(1);
    }
 
    fcml_st_assembler *assembler;
    if ((error = fcml_fn_assembler_init(dialect, &assembler))) {
        fprintf(stderr, "Can not initialize assembler: %d\n", error);
        fcml_fn_dialect_free(dialect);
        exit(1);
    }
 
    fcml_st_instruction instruction = {0};
    instruction.mnemonic = "adc";
    instruction.operands[0] = FCML_REG(fcml_reg_AX);
    instruction.operands[1] = FCML_IMM16(0x8042);
    instruction.operands_count = 2;
 
    /* Prepares the result. */
    fcml_st_assembler_result asm_result;
    fcml_fn_assembler_result_prepare(&asm_result);
 
    fcml_st_assembler_context context = {0};
    context.assembler = assembler;
    context.entry_point.ip = 0x401000;
    context.entry_point.op_mode = FCML_OM_32_BIT;
 
    /* Assembles the given instruction. */
    if ((error = fcml_fn_assemble( &context, &instruction, &asm_result))) {
        fprintf(stderr, "Can not assemble instruction: %d\n", error);
        fcml_fn_assembler_free(assembler);
        fcml_fn_dialect_free(dialect);
        exit(1);
    }
 
    /* Prints the instruction code. */
    if (asm_result.chosen_instruction) {
        fcml_st_assembled_instruction *ins_code = asm_result.chosen_instruction;
        int i;
        printf("Chosen instruction code: ");
        for (i = 0; i < ins_code->code_length; i++) {
            printf("%2x", ins_code->code[i]);
        }
        printf("\n");
    } else {
        fprintf(stderr, "Hmm, where is the assembled instruction?\n");
    }
 
    fcml_fn_assembler_result_free(&asm_result);
    fcml_fn_assembler_free(assembler);
    fcml_fn_dialect_free(dialect);
 
    return 0;
}
```

As you might have noticed, we have used a bit different location for the header files. In the examples above we
firstly supposed that header files are placed directly in the include directory, but in the case of the 
last example files are located in the dedicated "fcml" directory. It depends on the configuration. By default 
in case of GNU/Linux and MinGW include files are installed in the dedicated subdirectory, but it can be changed.
Just head over to the INSTALL file available in the distribution archive in order to investigate the subject
in great depth.

The example should print the following result:

Chosen instruction code: `66154280`

#### Disassembler

FCML disassembler takes a piece of machine code as an argument and "converts" it to a GIM instance 
(see: [Generic instruction model](http://www.fcml-lib.com/manual.html#generic_instruction_model)) which contains all information about the disassembled instruction. 
Such GIM can be used directly or for example can be rendered to the textual form of the instruction.

The first thing we have to do is to initialize a dialect which will be used by the disassembler to 
disassemble the provided machine code. Thanks to the dialects the library is able to use different
instruction syntaxes like Intel or AT&T (Remember that GIM is dialect dependant.). So let's prepare 
an instance of the Intel dialect:

```c	
#include <fcml_intel_dialect.h>
 
fcml_st_dialect *dialect;
fcml_ceh_error error = fcml_fn_dialect_init_intel(FCML_INTEL_DIALECT_CF_DEFAULT, &dialect);
if (error) {
    printf("Can not initialize dialect, error: %d\n", error);
    exit(EXIT_FAILURE);
}
```

As you can see, there are dedicated functions to create different dialects. Every function can also take additional
parameters used to configure the initialized dialect. In theory it should be possible to implement every existing 
dialect for FCML library, but currently only the Intel and AT&T (called GAS) dialects are supported. For the sake of
example the Intel dialect (the preferred one) is used. The Intel dialect was the first dialect which was supported
by FCML library and as such it is more mature. Anyway AT&T dialect is also fully supported and unit tested and 
can be safely considered as a stable one.

The dialect is ready, so let's initialize the disassembler instance using [fcml_fn_disassembler_init](http://www.fcml-lib.com/api/fcml__disassembler_8h.html#a795996631b091a97e7ae1d04a6015522) function.

```c	
fcml_st_disassembler *disassembler;
error = fcml_fn_disassembler_init(dialect, &disassembler);
```

To make code a bit clearer, error handling has been avoided in this case, but it should be implemented in the 
same way as in case of the dialect initialization. All possible error codes are defined in
the header file [fcml_errors.h](http://www.fcml-lib.com/api/group__ERRORS__GROUP.html#ga88406cc59b708d9f4de9286d254dd10a)

Having initialized the dialect and disassembler, there is the last thing to be done before disassembling is possible.
It is the disassembler result structure. This structure is reusable so it has to be prepared in the right way in
order to allow the disassembler to reuse it correctly. To do so, a manually allocated structure has 
to be passed to [fcml_fn_disassembler_result_prepare](http://www.fcml-lib.com/api/structfcml__st__disassembler__result.html) function:

```c	
fcml_st_disassembler_result result;
fcml_fn_disassembler_result_prepare(&result);
```

That is all, the disassembler is prepared to do its job, so let's try to disassemble a piece of example machine code.

The main structure which has to be properly prepared for the disassembler to work is [fcml_st_disassembler_context](http://www.fcml-lib.com/api/structfcml__st__disassembler__context.html). 
It consists of the previously initialized disassembler instance which should be used to disassemble the machine code, 
some configuration flags we can use to configure disassembling process, entry point which will be used to inform the 
disassembler about the code segment the instruction is located in and a piece of the instruction machine code. 
The disassembler context itself can be initialized on the stack, but it is very important to clear the memory it 
uses before passing it to the disassembler. We should do it just to set all configuration options and other parameters 
to its default values. For example the following source code shows the proper way to initialize the disassembler context:

```c	
fcml_st_disassembler_context context = {0};
```

Let's start by setting the configuration options. For now there is only one flag we are interested in. 
It is [enable_error_messages](http://www.fcml-lib.com/api/structfcml__st__disassembler__conf.html#a558b58f6dca6b073020970950e87707b) which is responsible for enabling textual error messages, which can be used
to identify potential errors and as such they should be very helpful for beginners. The second flag that might
be interesting here is [short_forms](http://www.fcml-lib.com/api/structfcml__st__disassembler__conf.html#a1f91b6e27453c19fe1896bb121f4ae87) and it has to be set to true in order to instruct the assembler to use a short
instruction forms whenever possible (For instance `cmpsw` instead of `cmps word ptr [si],word ptr [di]`.)
The [short_forms](http://www.fcml-lib.com/api/structfcml__st__disassembler__conf.html#a1f91b6e27453c19fe1896bb121f4ae87) flag impacts the generated GIM, so it should be used carefully.

```c	
context.configuration.enable_error_messages = FCML_TRUE;
context.configuration.short_forms = FCML_TRUE;
```

The disassembler is configured but we still have not provided any machine code yet. It can be done by setting 
two additional context fields [code](http://www.fcml-lib.com/api/structfcml__st__disassembler__context.html#a773efa2fa6b9600627b5b85f1570109d)
and [code_length](http://www.fcml-lib.com/api/structfcml__st__disassembler__context.html#aa517a01756088a93f0f5608632c511ac):

```c	
context.code = code;
context.code_length = sizeof(code);
```

The code should be a pointer to an array of bytes which contains instruction machine code and code_length of course 
holds the length of the array in bytes.

The machine code is configured now, but we known nothing about the code section, so it is time to set the instruction
pointer and processor addressing mode by setting the entry point structure correctly (If you do not known what the
instruction pointer, address size attribute or processor operating mode are, you definitely should at
least read this chapter: [Understanding entry point](http://www.fcml-lib.com/manual.html#un-entry-point))

The structure [fcml_st_entry_point](http://www.fcml-lib.com/api/structfcml__st__entry__point.html) holds basic information about the code section and the instruction pointer 
of the instruction. Thanks to it we can set value of the IP/EIP or RIP register that points to the instruction
machine code in the memory. It is very important to set it correctly, because this information is used to 
calculate relative offsets for example. The first required field is op_mode which describes the processor 
operating mode ([FCML_OM_16_BIT](http://www.fcml-lib.com/api/fcml__common_8h.html#aa842ef70ab3255bbffe239aa2bffdd1b), 
[FCML_OM_32_BIT](http://www.fcml-lib.com/api/fcml__common_8h.html#aa842ef70ab3255bbffe239aa2bffdd1b) or
[FCML_OM_64_BIT](http://www.fcml-lib.com/api/fcml__common_8h.html#aa842ef70ab3255bbffe239aa2bffdd1b)). We can also set default values for
the address size attribute and operand size attribute for our "virtual" code segment:

```go	
context.entry_point.op_mode = FCML_OM_32_BIT;
context.entry_point.address_size_attribute = FCML_DS_UNDEF;
context.entry_point.operand_size_attribute = FCML_DS_UNDEF;
context.entry_point.ip = 0x00401000;
```

The disassembler context is almost initialized, we have left the most important thing at the end. It is the disassembler
itself. It has to be also put into the context, because it will be used to do the whole job:

```go	
context.disassembler = disassembler;
```

The following piece of source code shows how the whole context initialization should looks like:

```c
fcml_st_disassembler_context context = {0};
context.disassembler = disassembler;
context.configuration.enable_error_messages = FCML_TRUE;
context.configuration.short_forms = FCML_TRUE;
context.code = code;
context.code_length = sizeof(code);
context.entry_point.op_mode = FCML_OM_32_BIT;
context.entry_point.address_size_attribute = FCML_DS_UNDEF;
context.entry_point.operand_size_attribute = FCML_DS_UNDEF;
context.entry_point.ip = 0x00401000;
```

Now we are ready to disassemble the first piece of machine code, so let's do it. In order to disassemble anything 
we have to call the function [fcml_fn_disassemble](http://www.fcml-lib.com/api/fcml__disassembler_8h.html#a26d4fb7b2eae675eeaaadbd950881c07) (Definition Below).

```c	
LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_disassemble(
    fcml_st_disassembler_context *context, 
    fcml_st_disassembler_result *result);
```

The function gets the disassembler context and disassembler result as arguments:

```c	
error = fcml_fn_disassemble(&context, &result);
if (!error) {
    …
}
```

If everything succeeded, the error code is `FCML_CEH_GEC_NO_ERROR` and the result contains the disassembled instruction
in the form of the generic instruction model. Let's take a look at [fcml_st_disassembler_result](http://www.fcml-lib.com/api/structfcml__st__disassembler__result.html) structure. 
Field [errors](http://www.fcml-lib.com/api/structfcml__st__disassembler__result.html#a8f402916076e73413bc1a31dbdb78141) contain error messages if the function failed (Or potential warnings in case of success).

There is also [fcml_st_instruction_details](http://www.fcml-lib.com/api/structfcml__st__instruction__details.html) structure which consists of additional information which is not 
relevant for the general instruction model but anyway can be useful through the process of the instruction analysis.

Now we have a general instruction model, but what if we would like to print a textual representation of the
instruction for the user? There is nothing easier than that. You only have to configure a instruction renderer 
and render the GIM to the provided buffer. So let's do it, but at first take a look at the function we
will use to render our instruction model:

```c	
LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_render(fcml_st_dialect *dialect,
    fcml_st_render_config *config, 
    fcml_char *buffer, 
    fcml_usize buffer_len,
    fcml_st_disassembler_result *result);
```

This function needs quite a few parameters, but take into account that there is only one argument that has to be 
carefully prepared. It is [fcml_st_render_config](http://www.fcml-lib.com/api/structfcml__st__render__config.html) structure which configures some aspects of the rendering process.
It is also not so complicated, because it contains only a few rendering flags (see: [Instruction renderer](http://www.fcml-lib.com/manual.html#instruction-renderer)) and 
padding configuration. So let's prepare the configuration:

```c	
fcml_st_render_config render_config = {0};
render_config.render_flags = FCML_REND_FLAG_HEX_IMM | 
                             FCML_REND_FLAG_HEX_DISPLACEMENT;
```

The next two parameters that follow the configuration: buffer and buffer_length point to the output buffer, 
where textual representation of the instruction will be rendered. You can allocate this buffer in the following way:

```c	
fcml_uint8_t buffer[FCML_INSTRUCTION_SIZE];
```

Remember that the buffer is also reusable and does not have to be cleaned between multiple calls to 
the rendering function.

We have prepared all needed parameters, so let's render the instruction from the disassembler result:

```c	
fcml_ceh_error error = fcml_fn_render(dialect, render_config, 
    buffer, sizeof(buffer), result);
```

As you can see we pass the whole disassembler result structure to the renderer. It is important to note that in 
order to render the instruction we need the whole result, a GIM is not enough here. It is why the whole result is 
passed as the parameter, because it contains [fcml_st_instruction_details](http://www.fcml-lib.com/api/structfcml__st__instruction__details.html) structure which is also used by the renderer.
Although it is possible to prepare such a disassembler result by hand and pass it the renderer, it would be very risky
(mostly because there is some information destined only for renderers like hints), so remember to use renderers
only with structures prepared by FCML disassembler. The last thing to remember is to use the same dialect 
that was used by the disassembler.

When resources are no longer needed they have to be freed. The following source code frees the disassembler
result, disassembler itself and the dialect:

```c	
fcml_fn_disassembler_result_free(&dis_result);
fcml_fn_disassembler_free(disassembler);
fcml_fn_dialect_free(dialect);
```

Remember that [fcml_fn_disassembler_result_free](http://www.fcml-lib.com/api/fcml__disassembler_8h.html#aacd6d5618c7e460cde65188c5c8ba241) function does not free the result structure itself. It is only 
responsible for freeing all structures allocated by the disassembler which are accessible through the disassembler 
result, like error messages for instance. It is why you can still reuse the structure, even if it was freed before.

See the [Instruction renderer](http://www.fcml-lib.com/manual.html#instruction-renderer) chapter for working example. 

### C++ language

The complete manual for C++ language can be found here: [C++ wrapper](http://www.fcml-lib.com/manual.html#cpp-wrapper)

#### Assembling
The following code shows how easy it is to assemble instructions in a truly dynamic way! Notice that it assembles [generic instruction model](http://www.fcml-lib.com/manual.html#generic_instruction_model) built using an instruction builder (IB) class.

```cpp
IntelDialect dialect;
AssemblerContext ctx( EntryPoint::OM_32_BIT, 0x401000 );
Assembler assembler(dialect);
Instruction instruction = IB(M_MOV).reg(EAX).offd( 0x40302010 );
AssemblerResult result;
assembler.assemble( ctx, instruction, result );
CodeIterator it = result.getCodeIterator();
while (it.hasNext()) {
	fcml_uint8_t codeByte = it.next();
	...
}
```
#### Parsing
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
#### Disassembling
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
#### Rendering
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
* You can download official binaries and source code archive directly from sourceforge: https://sourceforge.net/projects/fcml/files and GitHub releases: [releases](https://github.com/swojtasiak/fcml-lib/releases)

LICENSE
---

LGPL 2.1 (https://www.gnu.org/licenses/lgpl-2.1.txt)

hsdis is dual licensed under LGPL 2.1 or Apache License 2.0

https://www.apache.org/licenses/LICENSE-2.0.txt

