# VPC

*A Virtual Processor written in C*

**Table of Contents**

1.  Preface

    1.  Abstract
    2.  Considerations
    3.  Comments
2.  Overview

    1.  Compiling
    2.  Usage
    3.  Reading Files
    4.  Writing Files
    5.  Dumping Memory
    6.  Dumping Registers
    7.  Execution
    8.  Tracing
3.  Testing

    1.  Immediate Instructions
    2.  Data Instructions
    3.  Load/Store Instructions
    4.  Push/Pull Instructions
    5.  Conditional Branch
    6.  Unconditional Branch
4.  Code Review

    1.  Header Files
    2.  Source Files

## 0.0 Preface

### 0.1 Abstract

VPC is a central processing unit emulation program. It acts as an interactive
shell where one can run, trace, load (from the hard disk of the host operating
system), edit and save binary files that will operate within VPC. These binary
files represent the instructions and data that would constitute for a computer
program. VPC is written in C and conforms with C99 standards.

### 0.2 Considerations

VPC had most of its development and testing done on a 64bit Linux (v3.13)
distribution using the GNU C Compiler (*GCC*). When the project had started the
specification noted that there must be a 16bit version of the program compiled
with the Borland C/C++ 5.2 Compiler (*BCC*) for DOS. It was also suggested to
use one file to represent the entire processor. Throughout the development of
these original specs a lot of issues were encountered in terms of data type
association and casting. Consider *Table 0.1*, where the size of a `long` is
not the same between the 64bit GCC and the others, just as the size of an
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

*Table 0.1 - Demonstrating the sizes of data types within C*

Data types become a crucial aspect of VPC, as there is a lot of casting between
types to determine specific information about the binary data being moved
within the program. Because of these mismatch in sizes the project moved to
the C99 standard library, which includes data types that have a fixed bit-width
inside the stdint.h header file. This transistion however has left the BCC
inoperable because of it's lack of C99 standard library definitions. Instead,
the Open Watcom (*OWC*) 16bit DOS compiler will be used for testing on 16bit
systems.

### 0.3 Comments

The Microsoft Visual Studio 2013 compiler will be referenced as *VSC*. There
was almost no actual development done on a Windows system, but all of the
testing was compliant.

VPC makes use of the `fprintf()`, `fgets()` and `fscanf()` functions that
VSC really hates and has declared deprecated (for their system). This function
is however extremely safe to use on POSIX compliant operating systems (such as
Linux, or BSD). This is a not a real problem, but an interesting note.

## 1.0 Overview

VPC emulates a processor. Processors are usually equipped with registers to
help the speed and calculation of data. 
