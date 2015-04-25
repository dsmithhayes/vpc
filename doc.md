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

3.  **Testing**

    1.  Immediate Instructions
    2.  Data Instructions
    3.  Load/Store Instructions
    4.  Push/Pull Instructions
    5.  Conditional Branch
    6.  Unconditional Branch

4.  **Code Review**

    1.  Header Files
    2.  Source Files

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

## 3.0 Testing

## 4.0 Code Review











