vpc
===

A virtual 16bit processor and hex memory editor.
=======
This is a virtual cpu with 16kB memory. So far all it can do is read
and write files. I mean that's pretty cool but its not all that
impressive yet.

Compiling
---------

Testing this on many compilers. The follow is how to compile
and run `vpc`.

    $ gcc -o vpc vpc.c
    $ ./vpc

This has also been tested against the Borland 16bit C Compiler.

    :\> bcc vpc.c
    :\> vpc.exe
