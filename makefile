CC=gcc

INCDIR := -Ilib/
SRCDIR := src/
OBJDIR := obj/

all: vpc

vpc:
    

clean:
    rm ($OBJDIR)*.o
