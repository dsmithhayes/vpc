CC=gcc
CFLAGS=-Ilib/

SRCDIR=src
OBJDIR=obj

OBJS=$(OBJDIR)/%.o

all: vpc

vpc: $(OBJS)
	$(CC) -c 

$(OBJS): $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $< -c $@