# Main program
PROG := main

# Source code
SRC := ${wildcard src/*.c}

# Object code 
OBJ := ${SRC:.c=.o}

# flags of each type
CC = gcc 
INCLUDES = -I/usr/include/X11
LIBRARIES = -lX11

# Linker Flags (From object to program)
LDFLAGS := ${LIBRARIES}

# For compilation
CFLAGS := -Wall -Wextra -O2 ${INCLUDES}

# Compiles the program
all : ${PROG}

# Link the object: $@ => Each object
# This intermediatry step is used to link the libraries
${PROG} : ${OBJ}
	${CC} ${OBJ} -o $@ ${LDFLAGS}

# Compilation of source code to object files
# $< => only one program 
%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	@rm -rf ${OBJ} ${PROG}

.PHONY: all clean