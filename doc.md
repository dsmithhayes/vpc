# VPC

*A Virtual Processor written in C*

**Table of Contents**

1.  **Preface**
    1.  Abstract
    2.  Considerations
    3.  Comments
2.  **Overview**
    1.  Compiling
    2.  Usage
    3.  Reading Files
    4.  Writing Files
    5.  Dumping Memory
    6.  Dumping Registers
    7.  Execution
    8.  Tracing
3.  **Operations & Testing**
    1.  Immediate Instructions
        1.  `MOV_IMM`
        2.  `CMP_IMM`
        3.  `ADD_IMM`
        4.  `SUB_IMM`
    2.  Data Instructions
        1.  `AND_DAT`
        2.  `EOR_DAT`
        3.  `SUB_DAT`
        4.  `SXB_DAT`
        5.  `ADD_DAT`
        6.  `ADC_DAT`
        7.  `LSR_DAT`
        8.  `LSL_DAT`
        9.  `TST_DAT`
        10. `TEQ_DAT`
        11. `CMP_DAT`
        12. `ROR_DAT`
        13. `ORR_DAT`
        14. `MOV_DAT`
        15. `BIC_DAT`
        16. `MVN_DAT`
    3.  Load/Store Instructions
    4.  Push/Pull Instructions
    5.  Conditional Branch
    6.  Unconditional Branch
    7.  Stopping
4.  **Code Review**
    1.  Header Files
    2.  Source Files
5.  **Program Flow**


## 1.0 Preface

It is assumed that the reader of this document is competent in the C programming
language enough to understand it's datatypes, the differences in compilers
and the nuances of the language. There will not be a lot of discussion about
simple concepts like bit-masking or type casting. This document will provide
helpful information about using the program, how testing was done and how the
program works from the code's perspective.

### 1.1 Abstract

VPC is a central processing unit emulation program. It acts as an interactive
shell where one can run, trace, load (from the hard disk of the host operating
system), edit and save binary files that will operate within VPC. These binary
files represent the instructions and data that would constitute for a computer
program. VPC is written in C and conforms with C99 standards.

### 1.2 Considerations

VPC had most of its development and testing done on a 64bit Linux (v3.13)
distribution using the GNU C Compiler (*GCC*). When the project had started the
specification noted that there must be a 16bit version of the program compiled
with the Borland C/C++ 5.2 Compiler (*BCC*) for DOS. It was also suggested to
use one file to represent the entire processor. Throughout the development of
these original specs a lot of issues were encountered in terms of data type
association and casting. Consider the table below, where the size of a `long`
is not the same between the 64bit GCC and the others, just as the size of an
`int` is not the same between BCC and the others. 

<table>
    <tr>
        <th>Compiler</th>
        <th>Size of <code>int</code></th>
        <th>Size of <code>long</code></th>
    </tr>
    <tr>
        <td>GCC 4.8.2 (<em>64bit</em>)</td>
        <td>4</td>
        <td>8</td>
    </tr>
    <tr>
        <td>Microsoft VS C++2013 (<em>32bit</em>)</td>
        <td>4</td>
        <td>4</td>
    </tr>
    <tr>
        <td>BCC 5.2 (<em>16bit</em>)</td>
        <td>2</td>
        <td>4</td>
    </tr>
</table>

Data types become a crucial aspect of VPC, as there is a lot of casting between
types to determine specific information about the binary data being moved
within the program. Because of these mismatch in sizes the project moved to
the C99 standard library, which includes data types that have a fixed bit-width
inside the stdint.h header file. This transistion however has left the BCC
inoperable because of it's lack of C99 standard library definitions. Instead,
the Open Watcom (*OWC*) 16bit DOS compiler will be used for testing on 16bit
systems.

### 1.3 Comments

The Microsoft Visual Studio 2013 compiler will be referenced as *VSC*. There
was almost no actual development done on a Windows system, but all of the
testing was compliant.

VPC makes use of the `fprintf()`, `fgets()` and `fscanf()` functions that
VSC really hates and has declared deprecated (for their system). This function
is however extremely safe to use on POSIX compliant operating systems (such as
Linux, or BSD). This is a not a real problem, but an interesting note.

## 2.0 Overview

VPC emulates a processor. Processors are usually equipped with registers to
help the speed and calculation of data. These registers are all 32bits in
in length. As described in *Section 1.2*, a datatype in C that has 32bits would
be a `long` for 32bit operating systems. So instead all of the registers are
defined as `uint32_t` to satisfy this requirement. VPC has 16 general purpose
registers, referred to from here on out as the *register file*. There is a
Memory Address Register (*MAR*) that tells the processory where in memory the
data is located. Along with the MAR there is a Memory Buffer Register (*MBR*)
which is used to buffer data from memory into the register file. There are two
Instruction Registers (*IR*) that are 16bits each and reside in the same
32bit register. The top half of the IR is considered the first instruction
(*IR0*) and the bottom half is the second instruction (*IR1*). This means that
the processory uses 16bit instructions.

Note that the last three registers in the register file are used as special
case registers that contain the Stack Pointer (*SP*), Link Register (*LR*) and
Program Counter (*PC*). There is also an Arithmetic Logic Unit (*ALU*) which
is used as a buffer for actual processory calculations and operations. Its
usage will be further explained in *Section 4.2*.

VPC also comes with a 16kB (`0x4000` bytes) addressable memory. This is the
memory that will be accessed by the MBR and addressed by the MAR.

There are three control flags that will be toggled throughout the operation
of the CPU. This register is referred to as the Control Code Register (*CCR*).
This register considers the Sign, Zero and Carry flags that may be set or
cleared during the operation of an instruction. 

### 2.1 Compiling

Compiling (and running) VPC is as easy as running the following series of
commands in the root of the project's directory.

    make
    make run        # in the VPC shell here
    make clean

The Visual Studio project file will just compile & run in a Debug mode. The
Open Watcom project file will also do the same for the 16bit DOS version.

### 2.2 Usage

When VPC is first run, it is best to execute `?`, `H` or `h` to access the
folowing menu

    All number input should be in UPPER CASE HEX
    Using lowercase could yield to unfavourable results

    d   dump memory
    g   go - run the program
    l   load a file into memory
    m   memory modify
    q   quit
    r   display registers
    t   trace - execute one instruction
    w   write file
    z   reset all registers to 0
    ?, h    display this menu

The top warning is for when options such as `d` or `m` require the user to
specify addresses in memory, or binary values that will be stored in the memory.
This based on used `fscanf()` with the `%X` pattern to match. Depending on
your standard library, it may not capture lower-case hexadecimal values
properly.

### 2.3 Reading Files

When executing VPC from the `make run` command make the relative directory the
project root. In the root is a testing file called `test.bin`. Using the
`l` option, type the name of the file. This action will load the `test.bin`
file directory into memory.

    option> l
    
    file name> test.bin
    File loaded. 0x0010 (16) bytes read.

### 2.4 Writing Files

Writing a file will prompt the user with how much of the memory should be
written to the disk. The following example will save the `test.bin` file as
twice its size.

    option> w
    
    filename> test.bin
    bytes to write (hex)> 20
    Wrote 0x20 (32) bytes to the file successfully.

### 2.5 Dumping Memory

When writing the 32byte file to the disk, the file is filled up with 32 bytes
worth of `0`s. To prove this, dumping the memory contents from the first
address (`0x0`) to the `0x20` address will display what the contents of the
`test.bin` is.

    option> d
    
    offset> 0
    length> 20
    
       0    4A A5 61 15 71 15 50 15 5A A5 E0  0  0  0  0  0 
             J  .  a  .  q  .  P  .  Z  .  .  .  .  .  .  . 
      10     0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 
             .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  . 

### 2.6 Dumping the Registers

VPC starts with absolutely no value in any register. Dumping the registers is
useful to see what values are in the processor during any given operation.
Consider an immediate instruction which places an 8bit value into any specified
register.

    option> r
    
    R00: 0x00000000 R01: 0x00000000 R02: 0x00000000 R03: 0x00000000 
    R04: 0x00000000 R05: 0x00000000 R06: 0x00000000 R07: 0x00000000 
    R08: 0x00000000 R09: 0x00000000 R10: 0x00000000 R11: 0x00000000 
    R12: 0x00000000  SP: 0x00000000  LR: 0x00000000  PC: 0x00000000
    
    CCR: 000 (sign, zero, carry)
    MBR: 0x00000000
    MAR: 0x00000000
    IR0: 0x0000
    IR1: 0x0000
    
    Stop Flag: 0
    Active IR: 0

### 2.7 Execution

Execution runs every instruction possible until it reaches the ever so important
stop instruction. This must always be considered when assembling a program so
that the execution loop can properly be stopped. There is no visual indication
of executions.

### 2.8 Tracing

Tracing is extremely important to the debugging of the assembled program. When
tracing through `test.bin`, the registers display the immediate instruction's
value and operation. Tracing will perform each individual instruction and dump
the registers (the same as `r` would) to the screen.

    option> t
    
    Press any button to trace, '.' to exit.
    0x00000000> 
    R00: 0x00000000 R01: 0x00000000 R02: 0x00000000 R03: 0x00000000 
    R04: 0x00000000 R05: 0x000000AA R06: 0x00000000 R07: 0x00000000 
    R08: 0x00000000 R09: 0x00000000 R10: 0x00000000 R11: 0x00000000 
    R12: 0x00000000  SP: 0x00000000  LR: 0x00000000  PC: 0x00000004
    
    CCR: 000 (sign, zero, carry)
    MBR: 0x4AA56115
    MAR: 0x00000004
    IR0: 0x4AA5
    IR1: 0x6115
    
    Stop Flag: 0
    Active IR: 1
    
    0x00000002> 
    R00: 0x00000000 R01: 0x00000000 R02: 0x00000000 R03: 0x00000000 
    R04: 0x00000000 R05: 0x000000BB R06: 0x00000000 R07: 0x00000000 
    R08: 0x00000000 R09: 0x00000000 R10: 0x00000000 R11: 0x00000000 
    R12: 0x00000000  SP: 0x00000000  LR: 0x00000000  PC: 0x00000004
    
    CCR: 100 (sign, zero, carry)
    MBR: 0x4AA56115
    MAR: 0x00000004
    IR0: 0x4AA5
    IR1: 0x6115
    
    Stop Flag: 0
    Active IR: 0
    
    0x00000004>

## 3.0 Operations & Testing

Throughout this section of the documentation the instructions are described
and each operation of that instruction type is tested. Please refer to Section
4.1, header file `operations.h` for a table explaining how the 16bits are
used for each instruction. This section demonstrates the exact binary
instructions that are included within the program.

### 3.1 Immediate Instructions

An immediate instruction places a value represented by eight bits into the
register file defines in the last four bits of the instruction (`RD`). There are
four opcodes that are used to determine immediate instructions. All of these
constants are defined with a `_IMM` suffix.

<table>
    <tr>
        <th>Operation</th>
        <th>Mask</th>
        <th>Description</th>
    </tr>
    <tr>
        <td><code>MOV</code></td>
        <td><code>0x4000</code></td>
        <td>Moves the immediate value into the register specified by Rd</td>
    </tr>
    <tr>
        <td><code>CMP</code></td>
        <td><code>0x5000</code></td>
        <td>Compares the immediate value with the value in Rd.</td>
    </tr>
    <tr>
        <td><code>ADD</code>
        <td><code>0x6000</code></td>
        <td>Adds the immediate value into the Rd.</td>
    </tr>
    <tr>
        <td><code>SUB</code></td>
        <td><code>0x7000</code></td>
        <td>Substracts the immediate value from Rd.</td>
    </tr>
</table>

#### 3.1.1 MOV

The following 16bit instruction, `0x4100`, will move the value of `0x10` into
the first indexed register in the file (`0x0`). Because this moves a value into
the register there is no need to check for the carry flag to be set. This
instruction will however set the sign and zero flags respectively. 

#### 3.1.2 CMP

Comparing a value will subtract the imemdiate value from the register but not
store the result. Because there is arithmetic involved with the operation
(even without storing the result) all of the CCR flags are set accordingly.
The 16bit instruction used is `0x5110` to compared `0x11` in the register
file with the `0` index (`0x10` from our last instruction). This will set the
carry flag accordingly.

#### 3.1.3 ADD

Now the instruction to add `0x20` into the same register would look like `6200`
and adds the value correctly.

#### 3.1.4 SUB

To substract the total value from the register (now `0x30`) use the 16bit
instruction `0x7300`. This will set the zero flag.

### 3.2 Data Instructions

Data instructions take the value in the register defined by Rn and perform
the necessary operation to the value in Rd. There are 16 data operations
that can be used. All of the constants are defined with a `_DAT` suffix.

<table>
    <tr>
        <th>Operation</th>
        <th>Mask</th>
        <th>Description</th>
    </tr>
    <tr>
        <td><code>AND</code></td>
        <td><code>0x0000</code></td>
        <td>Bitwise AND the value from Rn into Rd.</td>
    </tr>
    <tr>
        <td><code>EOR</code></td>
        <td><code>0x0100</code></td>
        <td>Bitwise exclusive OR the value from Rn into Rd.</td>
    </tr>
    <tr>
        <td><code>SUB</code></td>
        <td><code>0x0200</code></td>
        <td>Substract the value Rn from Rd and store in Rd.</td>
    </tr>
    <tr>
        <td><code>SXB</code></td>
        <td><code>0x0300</code></td>
        <td>Rd becomes a signed version of Rn.</td>
    </tr>
    <tr>
        <td><code>ADD</code></td>
        <td><code>0x0400</code></td>
        <td>Adds the value of Rn into Rd.</td>
    </tr>
    <tr>
        <td><code>ADC</code></td>
        <td><code>0x0500</code></td>
        <td>Adds the value of Rn into Rd with consideration of the carry
        flag.</td>
    </tr>
    <tr>
        <td><code>LSR</code></td>
        <td><code>0x0600</code></td>
        <td>Performs a logical shift right on Rd by Rn bits.</td>
    </tr>
    <tr>
        <td><code>LSL</code></td>
        <td><code>0x0700</code></td>
        <td>Performs a logical shit left on Rd by Rn bits.</td>
    </tr>
    <tr>
        <td><code>TST</code></td>
        <td><code>0x0800</code></td>
        <td>Performs bitwise AND between Rn and Rd, does not store result.</td>
    </tr>
    <tr>
        <td><code>TEQ</code></td>
        <td><code>0x0900</code></td>
        <td>Performs bitwise exclusive OR between Rn and Rd, does not store
        the result.</td>
    </tr>
    <tr>
        <td><code>CMP</code></td>
        <td><code>0x0A00</code></td>
        <td>Compares the values in Rd and Rn, does not store the result.</td>
    </tr>
    <tr>
        <td><code>ROR</code></td>
        <td><code>0x0B00</code></td>
        <td>Rotates the values in Rd by Rn bits.</td>
    </tr>
    <tr>
        <td><code>ORR</code></td>
        <td><code>0x0C00</code></td>
        <td>Performs a bitwise OR between Rn and Rd.</td>
    </tr>
    <tr>
        <td><code>MOV</code></td>
        <td><code>0x0D00</code></td>
        <td>Moves the value in Rn into Rd.</td>
    </tr>
    <tr>
        <td><code>BIC</code></td>
        <td><code>0x0E00</code></td>
        <td>Clears all of the bits defined by Rn in Rd</td>
    </tr>
    <tr>
        <td><code>MVN</code></td>
        <td><code>0x0F00</code></td>
        <td>Places the 1's compliment of Rn in Rd.</td>
    </tr>
</table>

For testing purposes, it is to assume that all al of the Rn values are in the
1 index of the register file, and all of the Rd values are in the 0 index.

#### 3.2.1 AND

To perform an AND and store the value in Rd, use `0x0010`.

#### 3.2.2 EOR

`0x0110` would perform a bitwise exclusive `OR` between Rn and Rd, and store
the value in Rd.

#### 3.2.3 SUB

To substract the value of Rn from Rd use `0x0210`

#### 3.2.4 SXB

`0x0310` will sign (toggle the most significant bit) Rn and place it in Rd.

#### 3.2.5 ADD

`0x0410`

#### 3.2.6 ADC

`0x0510`

#### 3.2.7 LSR

`0x0610`

#### 3.2.8 LSL

`0x0710`

#### 3.2.9 TST

`0x0810`

#### 3.2.10 TEQ

`0x0910`

#### 3.2.11 CMP

`0x0A10`

#### 3.2.12 ROR

`0x0B10`

#### 3.2.13 ORR

`0x0C10`

#### 3.2.14 MOV

`0x0D10`

#### 3.2.15 BIC

`0x0E10`

#### 3.2.16 MVN

`0x0F10`

### 3.3 Load/Store Instructions

Loading and storing is done by finding the value in memory that is pointed to
by Rn and placing that value in Rd. There are two control bits that determine
the size of a load or store. This can be a full register size (32bits) or a
single byte. Assuming we have a value in the register file at index 1 and want
to store a value in the register file index 0, consider the examples below. All
of these masks and macros are prefixed with `LS_`.

<table>
    <tr>
        <th>16bit Instruction</th>
        <th>Explanation</th>
    </tr>
    <tr>
        <td><code>0x2010</code></td>
        <td>Stores the whole register into memory.</td>
    </tr>
    <tr>
        <td><code>0x2810</code></td>
        <td>Loads a whole register from memory.</td>
    </tr>
    <tr>
        <td><code>0x2410</code></td>
        <td>Stores a single byte from the register into memory. This is the
        least significant byte (lower part of the register).</td>
    </tr>
    <tr>
        <td><code>0x2C10</code></td>
        <td>Loads a single byte from memory into the lower half of the
        register</td>
    </tr>
</table>

### 3.4 Push/Pull Instructions

The push and pull instructions are used to store the values of the registers
onto into memory as a stack. The lower byte of the instruction actually
determines which registers are to be stored in memory. There are three control
bits that determine what will happen with this instruction. The table below
will demonstrate how it works.

The lower byte of the instruction is set so that the most significant bit is
the highest register in the list; for each bit set, the corresponding register
from the file is pushed into memory, or the contents of memory are pulled
into it.

The opcode bit pattern (lower half of the most significant byte) holds the three
control bits that determine the load/store bit (L), which registers are to be
pushed or pulled (H) and finally whether to perform any extra pushes or pulls
(R). Their bit pattern looks like `LH0R`.

All of these instruction constants and macros are prefixed with `PP_`.

<table>
    <tr>
        <th>16bit Instruction</th>
        <th>Explanation</th>
    </tr>
    <tr>
        <td><code>0xA0AA</code></td>
        <td>Push every other register from the lower half of the register
        file.</td>
    </tr>
    <tr>
        <td><code>0xA1AA</code></td>
        <td>Push every other register from the lower half of the register file
        as well as the Link Register.</td>
    </tr>
    <tr>
        <td><code>0xA4AA</code></td>
        <td>Push ever other register from the upper half of the register
        file.</td>
    </tr>
    <tr>
        <td><code>0xA5AA</code></td>
        <td>Push every other register from the upper half of the register file
        as well as the Link Register.</td>
    </tr>
    <tr>
        <td><code>0xA8AA</code></td>
        <td>Pull data from the memory and place it in every other register in
        the lower half of the register file.</td>
    </tr>
    <tr>
        <td><code>0xA9AA</code></td>
        <td>Pull data from the memory and place it in every other register in
        the lower half of the register file, as well as the Program
        Counter.</td>
    </tr>
    <tr>
        <td><code>0xACAA</code></td>
        <td>Pull data from the memory and place it in every other register in
        the upper half of the register file.</td>
    </tr>
    <tr>
        <td><code>0xADAA</code></td>
        <td>Pull data from the memory and place it in every other register in
        the upper half of the register file, as well as the Program
        Counter.</td>
    </tr>
</table>

### 3.5 Conditional Branch

Conditional branches are used when specific events in the CCR occur. There
are a number of conditions to which the table below will specify their 16bit
instruction and a small explanation.

The lower byte of the conditional branch instruction is a signed relative
address. Consider the program counter is at `4` during a conditional branch
execution, and the next set of instructions are at an offset of `+0x40`. This
will make the lower byte of each example used below as `0x40`.

There are a total of nine conditions, including a condition to ignore all of
the other conditions. All of the constants and macros for these instructions
are prefixed with `COND_`.

<table>
    <tr>
        <th>16bit Instruction</th>
        <th>Explanation</th>
    </tr>
    <tr>
        <td><code>0x8040</code></td>
        <td>Branches if the zero flag is set.</td>
    </tr>
    <tr>
        <td><code>0x8140</code></td>
        <td>Branches if the zero flag is clear.</td>
    </tr>
    <tr>
        <td><code>0x8240</code></td>
        <td>Branches if the carry flag is set.</td>
    </tr>
    <tr>
        <td><code>0x8340</code></td>
        <td>Branches if the carry flag is clear.</td>
    </tr>
    <tr>
        <td><code>0x8440</code></td>
        <td>Branches if the sign flag is set.</td>
    </tr>
    <tr>
        <td><code>0x8540</code></td>
        <td>Branches if the sign flag is clear.</td>
    </tr>
    <tr>
        <td><code>0x8840</code></td>
        <td>Branches if carry flag is set and zero flag is clear.</td>
    </tr>
    <tr>
        <td><code>0x8940</code></td>
        <td>Branches if the carry flag is clear and the zero flag is set.</td>
    </tr>
    <tr>
        <td><code>0x8E40</code></td>
        <td>Just branch no matter what.</td>
    </tr>
</tr>

### 3.6 Unconditional Branch

The unconditional branch only has two options to it. There is a 12bit absolute
address stored within the instruction, along with one control bit that
determines if the current address in memory is stored in the Link Register to
be used as a return address. All of the constants and macros associated with
this instruction are prefixed with `UN_`

Assume the absolute location in memory is address `0x1F0`.

<table>
    <tr>
        <th>16bit Instruction</th>
        <th>Explanation</th>
    </tr>
    <tr>
        <td><code>0xC1F0</code></td>
        <td>Branches to `0x1F0` without storing a return address.</td>
    </tr>
    <tr>
        <td><code>0xD1F0</code></td>
        <td>Branches to `0x1F0` with a stored return address.</td>
    </tr>
</table>

### 3.7 Stopping

The end-all, be-all of the stop instruction is `0xE000`. The stop flag will
stop execution, but will not stop the tracing.

## 4.0 Code Review

The following is an explanation of a given file in the project along with its
purpose and any comments necessary to the operation of VPC. It is encouraged
to actually realy the source code file as well as they are extremely well
documented.

### 4.1 Header Files

VPC ships with four defined header files for the four seperate components of
the actual program. `vpc.h` is the general operations of the program to the
disk, including loading and writing files. `interface.h` defines all of the
functions that would act as an interface to the user. `registers.h` defines
constants and macros that pertain to the registers, along with a structure
called `registers` that contains all of the registers. `operations.h` is
a massive file that defines routines, macros and constants for **all** of the
operations that the processor can do.

The header files are all located within the `inc/` directory and are
included by the compiler during compilation.

#### vpc.h

`vpc.h` has two constants defined, one for the total memory and the other
for a word-representation for hexadecimal that will be used in the `strtoul()`
function to capture hexadecimal values up to `0xF`.

    #define TOTAL_MEMORY    0x4000
    #define HEX             0x10

The function prototypes in `vpc.h` define routines that allow VPC to interact
with the memory. The following is a listing of these prototypes.

    void writef(void * memory);
    int  loadf(void * memory, uint16_t max);
    void dumpmem(void * memory, uint16_t offset, uint16_t length);
    void modmem(void * memory, uint16_t offset);

The use of these functions are described in the `main.c` file. 

#### interface.h

The `interface.h` file is rather small, defines three constants and one
function prototype. They help define interface values for input from the user.

    #define INPUT_BUFFER    0xFF
    #define HEX_INPUT       4
    #define ROW_LENGTH      0x10

    void help();

The `help()` function displays the options available to the user.

#### registers.h

Seeing as registers are a very important part of the program, the `registers.h`
header defines a lot of constants and macros that are important to the
flow of the program.

A crucial part of the register file is the aliases used to describe the special
functioning registers, `SP`, `LR` and `PC` which are all assigned to the
index of the array that is the register file.

Because the CCR is a single register, there needs to be three bits for the
flags. The `SIGN_FLAG` is assigned to the third bit, `ZERO_FLAG` is the
second bit and the `CARRY_FLAG` is the least significant bit of the register.
There are macros defiend to determine if any of these flags are set.

The most important part of the `registers.h` file is the actual `registers`
structure that contains all of the registers. It is defined as follows.

    typedef struct Registers {
        uint32_t file[REG_FILE_S];
        
        uint32_t ccr;
        uint32_t mbr;
        uint32_t mar;
        uint32_t ir;
        uint32_t alu;
    
        uint8_t ir_flag;
        uint8_t stop_flag;
    } registers;

The `REG_FILE_S` constant is defined at `0x10` because there's 16 registers
in the file.

Function prototypes within `registers.h` define the functions that actually
move and manipulate the data from the memory to the register. These are all
called from the main program loop save for the `fetch()` function which
is called from all over the program. Each of these functions reside within
their own `.c` file.

    void zero(registers * reg);
    void dumpreg(registers reg);
    void trace(void * memory, registers * reg);
    void fetch(void * memory, registers * reg);
    void go(void * memory, registers * reg);

Note that all of the memory is passed as a `void` throughout the program. This
is to assure that technical modifications to the memory can be made with very
little change to the program's logic.

#### operations.h

All of the operations are defined according to the specification. The first
thing to note about the instructions is that they are 16 bits in length and
a number of them share similar properties. Consider the constant `RD_MASK`
which defines the four bit number that represents which register is the
destination for the operation. This is referred to as `Rd` throughout equations
and `rd` within functions in the source code. There is a macro to determine
this value called `RD`. Another common value found in instructions is the
`Rn` value which can determin the source of data stored in a register. There is
a corresponding `RN_MASK` that defines which bits of the instruction are `Rn`.
The value can be seen in functions with the name of `rn` with the corresponding
macro to determine the value with `RN`. There is a very obvious pattern here.

There are six definite types of operations. They are immediate instructions
(`IMM_MASK`), data instructions (`DAT_MASK`), load/store instructions
(`LS_MASK`), push/pull instructions (`PP_MASK`), conditional branches
(`COND_MASK`) and unconditional branched (`UN_MASK`). Of course one special
instruction is the stop instruction which is defined as `STOP_MASK`.

Note the prefixes in the constants that are defined. There are macros to test
the instruction against the mask defined. Each instruction mask is defined as
the bit pattern in the first four bits of the instruction. The following is
a table representation of the different instructions.

<table>
    <tr>
        <th>0xF</th>
        <th>0xE</th>
        <th>0xD</th>
        <th>0xC</th>
        <th>0xB</th>
        <th>0xA</th>
        <th>0x9</th>
        <th>0x8</th>
        <th>0x7</th>
        <th>0x6</th>
        <th>0x5</th>
        <th>0x4</th>
        <th>0x3</th>
        <th>0x2</th>
        <th>0x1</th>
        <th>0x0</th>
        <th>Operation</th>
    </tr>
    <tr>
        <td>0</td>
        <td>1</td>
        <td colspan="2">Opcode</td>
        <td colspan="8">Immediate Value</td>
        <td colspan="4">Rd</td>
        <td>Immediate Operation</td>
    </tr>
    <tr>
        <td>0</td>
        <td>0</td>
        <td>0</td>
        <td>0</td>
        <td colspan="4">Opcode</td>
        <td colspan="4">Rn</td>
        <td colspan="4">Rd</td>
        <td>Data Operations</td>
    </tr>
    <tr>
        <td>0</td>
        <td>0</td>
        <td>1</td>
        <td>0</td>
        <td>L</td>
        <td>B</td>
        <td>0</td>
        <td>0</td>
        <td colspan="4">Rn</td>
        <td colspan="4">Rd</td>
        <td>Load/Store Instructions</td>
    </tr>
    <tr>
        <td>1</td>
        <td>0</td>
        <td>1</td>
        <td>0</td>
        <td>L</td>
        <td>H</td>
        <td>0</td>
        <td>R</td>
        <td colspan="8">Register List</td>
        <td>Push/Pull</td>
    </tr>
    <tr>
        <td>1</td>
        <td>0</td>
        <td>0</td>
        <td>0</td>
        <td colspan="4">Condition Code</td>
        <td colspan="8">Relative Address</td>
        <td>Conditional Branch</td>
    </tr>
    <tr>
        <td>1</td>
        <td>1</td>
        <td>0</td>
        <td>K</td>
        <td colspan="12">Memory Address Offset</td>
        <td>Unconditional Branch</td>
    </tr>
    <tr>
        <td>1</td>
        <td>1</td>
        <td>1</td>
        <td>0</td>
        <td>0</td>
        <td>0</td>
        <td>0</td>
        <td>0</td>
        <td>0</td>
        <td>0</td>
        <td>0</td>
        <td>0</td>
        <td>0</td>
        <td>0</td>
        <td>0</td>
        <td>0</td>
        <td>Stop</td>
    </tr>
</table>

Note that the data operations use `0000` as its instruction code. This would
default all invalid operations as a data operations by doing a bitwise `AND`
with all zeros. The `DAT_MASK` constant is set to all ones so that when a
valid data operation is inverted it matches the mask properly. This will
render all invalid operations useless.

There are macros and cosntants defined all throughout `operations.h` that
will help extract the data necessary to perform each operation. It is
recommended that the documentation in `operations.h` be read to fully
understand what each value of these constants are, and what each function per
operation's prototype means.

### 4.2 Source Files

Please refer to the actual source files for they have adequate documentation
as to what they are doing.

## 5.0 Program Flow and Operation

Once a binary program is written, it can be executed in one of two ways. The
first to be discussed is tracing the program, which steps through each
individual instruction while displaying all of the registers affected and in
use. The second is to execute the whole program while in the background. Both
consider similar actions.

1.  Fetch four bytes from memory, store these values in the IR
2.  Check which instruction sub-register is to be used, either IR0 or IR1.
3.  Decode appropriate instruction, perform the associated operation.
4.  Repeat forever until the stop instruction is hit, or the end of memory is
    reached.

### 5.1 Trace

As mentioned above, when tracing through a program the user explicitly executes
each individual instruction. The user can exit the tracing by pressing the `.`
character. Each trace will do a full register dump. The prompt of the tracing
indicates which part of the PC they are on. Note that each instruction is
executed before the registers are dumped. This will display the *current* IR
flag, such as the prompt shows the *current* location in memory.

### 5.2 Go

Letting the program execute on its own will display text letting the user know
the program is running. Each period displayed on the screen indicates how many
instructions were actually executed, save for the stop instruction.
