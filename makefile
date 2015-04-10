CC=bcc
CFLAGS=-C -V
INC=-Ilib/

TARGET=bin/vpc.exe

OBJDIR=obj

SOURCES=$(wildcard src/*.c)
OBJECTS=$(addprefix obj/,$(notdir $(SOURCES:.c=.o)))

all: vpc

vpc: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

obj/%.o: src/%.c
	$(CC) $(CLFAGS) $(INC) -c -o $@ $<

clean:
	rm $(OBJECTS) $(TARGET)
