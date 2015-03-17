CC=gcc
CFLAGS=-Wall
INC=-Ilib/

TARGET=vpc

OBJDIR=obj

SOURCES=$(wildcard src/*.c)
OBJECTS=$(addprefix obj/,$(notdir $(SOURCES:.c=.o)))

all: vpc

vpc: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

obj/%.o: src/%.c
	$(CC) $(CLFAGS) $(INC) -c -o $@ $<

init:
	mkdir -p $(OBJDIR)

clean:
	rm $(OBJECTS)
