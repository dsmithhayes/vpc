CC=gcc
CFLAGS=-Wall
INC=-Ilib/

TARGET=vpc

SOURCES=$(wildcard src/*.c)
OBJECTS=$(addprefix obj/,$(notdir $(SOURCES:.c=.o)))

all: vpc

vpc: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS)

obj/%.o: src/%.c
	$(CC) $(CLFAGS) $(INC) -c -o $@ $<

clean:
	rm $(OBJECTS)
