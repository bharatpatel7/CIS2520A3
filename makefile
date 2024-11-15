# Compiler and flags
CC = gcc
CFLAGS = -Wall -std=c99 -pedantic

# Default target to build both executables
all: a3q1 a3q2

# Rule to build a3q1 from q1.c and q1_functions.c
a3q1: a3q1_main.c a3q1_functions.c a3q1_header.h
	$(CC) $(CFLAGS) -o a3q1 a3q1_main.c a3q1_functions.c

# Rule to build a3q2 from q2.c and q2_functions.c, linking with the math library (-lm)
a3q2: a3q2_main.c a3q2_functions.c a3q2_header.h
	$(CC) $(CFLAGS) -o a3q2 a3q2_main.c a3q2_functions.c -lm

# Clean rule to remove generated executables
clean:
	rm -f a3q1 a3q2