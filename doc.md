# vpc - documentation

The following is a description of the functions created and their
algorithms. 

## load_file()

* `void *memory`
* `unsigned int max`

Loading file works by passing a full or relative path to the program
to which is then loaded into the virtual memory. The following list is
the algorithm used to load the file.

1. Ask the user for a file name
2. If it is a valid file name, open the file into a buffer
3. Read the size of the file
4. copy the file into the virtual memory

This function utlizes the system's implementation of the standard
library functions `fopen()`, `fread()`, `fseek()`, `ftell()`
 `rewind()`, and  `fgets()`. The appropriate `errno` is returned
to the main program.

## write_file()

* `void *memory`

Writing a file is taking contents of memory and placing them into a
file in the current working directory based on a size given by the
user. The following is how this process is accomplished.

1. Ask the user for a file name
2. If the file doesn't exist, create it, overwrite otherwise
3. Ask for the size of the file to be written
4. If the given size is unreasonable, make it the whole memory
5. Write the memory to the file.

## modify_memory()

* `void *memory`
* `unsigned int offset`

An important part of the program is the ability to edit the values
that sit in the memory. This is achieved in a brutally tedius way;
each memory location asks for a value from the keyboard, when the
user enters `.` the writing stops.

1. ask the user for a memory location to start entering
2. capture the user input
3. place the character into memory
4. repeat until `.` entered or memory exceeded

## dump_memory()

* `void *memory`
* `unsigned int offset`
* `unsigned int length`

Dumping the memory to the screen is necessary to allow the user to
visually see what's being manipulated in the memory.

The follow figure is a demonstation of what the output should look like.

    offset> 18
    length> 40
    
    18  2E 63  A 20 20 20 20 61 75 74 68 6F 72 3A 20 44 
         .  c  .              a  u  t  h  o  r  :     D 
    28  61 76 65 20 53 6D 69 74 68 2D 48 61 79 65 73  A 
         a  v  e     S  m  i  t  h  -  H  a  y  e  s  . 
    38  20 20 20 20 64 61 74 65 
                     d  a  t  e

1. Ask the user where to start in memory
2. Iterate through the memory 
3. Print the graph above.

**Printing the graph**

Printing the graph was a fun task. The following is the steps and
sizes of iterations used to display the contents of the memory. The
 `offset` variable is where you start in the memory and you keep
printing until you've printed `length` contents of the memory. The
table has to be 16 (`0x10`) values long with two rows showing the
hex value of the memory address, and the ASCII value if there is one.
The beginning of each row is offsetted by which memory address is the
first value.

1. Print the memory address of the first value
2. Print the contents of the first address
3. Print the next 15 (`0xF`) values as hex
4. Print the same values as ASCII
5. If the value is not a character, print a `.`
6. Repeat process at `offset + 16 (0x10)`
7. If memory adress is equal to `offset + length` end

