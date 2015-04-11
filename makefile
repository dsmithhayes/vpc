CC=gcc
CFLAGS=-Wall
INC=-Iinc/

TARGET=bin/vpc

OBJDIR=obj
SRCDIR=src
BINDIR=bin

SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(addprefix obj/,$(notdir $(SOURCES:.c=.o)))

all: directories vpc

vpc: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

obj/%.o: src/%.c
	$(CC) $(CLFAGS) $(INC) -c -o $@ $<

directories:
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)

run:
	./$(TARGET)

clean:
	rm -r $(OBJECTS) $(TARGET) $(OBJDIR) $(BINDIR)
