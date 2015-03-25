# vpc

 *Author:* Dave Smith-Hayes

 *Date:* 24 March, 2015

## Abstract

 `vpc` is a small virtual processor written in C to target multiple
platforms. The processor is attached to 16kB (`0x4000`) of memory,
uses 16bit instructions and has a handful of 32bit registers. The
instructions used and the program flow control simulate an ARM
Cortex-3 processor.

The following literature is usage documentation, along with instruction
documentation and explanation of how several components of the software
interact with each other.

### Instruction Operation

The processor has a very simple cycle of operation. Firstly, it fetches
the data from the memory, interprets the instruction, fetches further
data from meory, performs an operation and finally stores the result
of the operation in memory.

1. Fetch an instruction from memory
2. Decode an instruction
3. Put data in registers
4. Perform data operation between registers
5. Store result in memory

Despite there being 32bit registers, the one *Instruction Register*
is actually viewed as a combination 16bit instruction register. The
first 2bytes of the value in the Instruction Register is the value
for `ir0` and the last 2bytes is `ir1`.

### Registers

When there are more that one register in an array format, this is
called a register file. The last three indexes of the register file
for `vpc` have special consideration. They are aliased with the
named *Stack Pointer*, *Link Register* and *Program Counter* and
perform their own special operations. The rest of the register file
is used for generic high speed data computation.

There is a *Memory Buffer Register*, *Memory Address Register* and
 *Arithmatic Logic Unit* which control the loading and storing of
data to the memory.

## Compilation

If the desired system is Windows, there is a binary in the `bin/`
directory called `vpc.exe` . There also includes a Visual Studio C++
2010 Express project file which should be able to run in all later
versions of Visual Studio. Along with that there is a Windows
 `makefile.win` that is used with the Orwell Dev-C++ project file
(which in turn uses GCC and the glibc) that is included with the
project. The program will run from these IDEs.

### Using make

    $ make

This will create a `vpc` binary in the `bin/` directory. This directory
will also be where all of the other binary files for instructions will
go as well. More on this topic in the usage.

## Usage

Topics in this section will be how to use the actual `vpc` program.
This presumes that the program was a successful compile, and is now
running as a binary on your system. *Which ever system that is.*

## Code Documentation

### Headers

#### vpc.h

This is the main header file that was used in the extremely early
stages of the development of this program. Defined here are extremely
important routines that interact with the human input. Routines like
loading and writing files from and to the physical disk.

All of the header files for `vpc` are found within the `lib/` directory.

 `vpc.h` includes one system header: `<stdin.h>` for `uintN_t`
declarations

The use of `uintN_t` type definitions is to assure fixed bit-width
datatypes. This assures that contents of the registers are actually
32bits and the content of memory exacty 8bits (one byte) at each
address.

 *Definitions*

    #define TOTAL_MEMORY 0x4000

There is a total of 16 kilobytes of memory in `vpc`. This is represented
as `16 * (2^10)` (16384) bytes, or `0x4000` in hexadecimal.

    #define HEX 0x10

This definition is used for a function that is in the standard
library (`strtoul()`) which allows the user to specify which base to
capture from the string. In this case, it is `HEX`.

 *Function Prototypes*

    void writef(void* memory);

Writes the contents of the memory to a file. The file name is supplied
by the user.

    int loadf(void* memory, uint16_t max);

Loads a file to the memory. If the file size is larger than `max` bytes
then it is truncated.

    void dumpmem(void* memory, uint16_t offset, uint16_t length);

Dumps the contents of memory to the screen, based on the offset in
memory and the contents of memory.

    void modmem(void* memory, uint16_t offset);

Allows the user to edit contents of the memory, address per address.
The user supplies an offset to begin editing the memory (in hexadecimal)
and stops when the user supplies a period. 

#### registers.h

A crucial library for this processor, most things defined and
prototyped here are used for the registers in the CPU.

 `registers.h` includes one system header: `<stdin.h>` used for the
 `uintN_t` datatypes

 *Definitions*

    #define REG_FILE_S 0x10

The register file is defines as a 16-32bit register file.

    #define SP 0xD
    #define LR 0xE
    #define PC 0xF

The *Stack Pointer* is defined as the 13th index of the register file.
The *Link Register* is the 14th index of the register file. Finally,
the *Program Counter* is the 15th index of the register file.

    #define SIGN  4
    #define ZERO  2
    #define CARRY 1
    #define STOP  1
    #define INST  1

These are flags that have their own registers. `SIGN`, `ZERO` and
 `CARRY` are all apart of one 32bit register (much too big) called the
 *Code Control Register*. Each number represents a 3bit logical
representation. Remember 4 in binary is `100`, 2 is `010` and 1 is
 `001`.

    ccr = SIGN | CARRY // 100 | 001 = 101

This shows how to apply both the `SIGN` and `CARRY` flag to a variable
that would represent the Code Control Register.

    #define REG_SIZE   4
    #define REG_BIT_S  0x20
    #define INSTR_SIZE 2
    #define INS_BIT_S  0x10

These are byte and bit definitions. `vpc` defines 4byte (32bit)
registers and 2byte (16bit) instruction sizes.

 *typedef*

    typedef struct Registers {
        uint32_t file[REG_FILE_S];
        
        uint32_t ccr;
        uint32_t mbr;
        uint32_t mar;
        uint32_t ir;
        uint32_t alu;
        
        uint8_t ir_flg;
        uint8_t stp_flg;
    } registers;

This struct defines all of the registers, along with two flags. The
register `alu` is the arithmatic logic unit, where all arithmetic is
performed. `ir_flg` is the instruction flag, which flip-flops according
to which instruction register is to be used. Remember the `ir` register
defined here is split into `ir0` and `ir1`. The `stp_flg` indicates
when the program should halt.

 *Prototypes*

    void zero(registers* reg);

Given the registers, sets all of the values within it to zero.

    void dumpreg(registers reg);

Displays all of the registers to the standard output.

    uint16_t ir0(uint32_t in);
    uint16_t ir1(uint32_t in);

Returns values that represent the 16bit pseudo-registers `ir0` and
 `ir1`

    void trace(void* memory, registers* reg);

Prompts the user to single step through the program counter while
loading the registers and performing operations accordingly.

    void fetch(void* memory, registers* reg);

This routine represents the fetch step in the CPU instruction cycle of
 `vpc`.

    void go(void* memory, registers* reg);

Run the program loaded in memory.

#### operations.h

The instruction set for this processor is defined here, mostly in
masks.

 *Prototypes*

    uint8_t is_inst(uint16_t mask, uint16_t inst);

Given the instruction mask defined in this header and the (pseudo)
Instruction Register (`ir0` or `ir1`), returns non-zero if they
match.

#### interface.h

The user interface is an important part of `vpc`.

 `interface.h` include one system library: `<stdint.h>` for `uintN_t`
data types.

 *Definitions*

    #define INPUT_BUFFER 0xFF
    #define HEX_INPUT    4

The `INPUT_BUFFER` is actually used in the `loadf()` and `writef()`
routines for the `fgets()` function, defining how much to buffer for
the filenames in bytes. `HEX_INPUT` is just like `INPUT_BUFFER` but
strictly for hexadecimal numbers. This is used in the `modmem()`
routine.

    #define ROW_LENGTH 0x10

When dumping the memory to the screen (`dumpmem()`), show 16 bytes per
line.

 *Prototypes*

    void help();

Displays the help text that shows which characters represent which
command.

### Source Files

