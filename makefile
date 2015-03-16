CC=gcc
CFLAGS=-Wall
INC=-Ilib/

TARGET=vpc.exe

SOURCES=$(wildcard src/*.c)
OBJECTS=$(addprefix obj/,$(notdir $(SOURCES:.c=.o)))

all: vpc

vpc: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

obj/%.o: src/%.c
	$(CC) $(CLFAGS) $(INC) -c -o $@ $<

clean:
	rm $(OBJECTS)
