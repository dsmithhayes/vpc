vpc
===

**vpc** is a 16kB virtual processor. It has 32bit registers and uses
16bit instructions.

## Compile

To compile on Linux just make sure you have GCC and Make and then just:

    $ make

There will be a binary in your base directory called `vpc`, run it.

## What It Does

* Interactive menu that doesn't suck
* Loads files into the 16kB memory, truncating it if necessary
* Writes files to the disc from memory per given size
* Modifies memory with hexadecimal input
* Dumps the contents of memory to screen per given offset and length
* Dump registers to the screen

## What It Needs to Do

* Load memory into registers
* Step through each chunk of memory
* Analyze instrustion
* Perform operations
* Compile from makefile
* Compile from dev-cpp project
