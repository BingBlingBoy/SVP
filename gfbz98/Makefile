CC=gcc
CFLAGS = -I.
DEPS = ErrorChecking.h GramSchmidt.h SE_Enumeration.h result_to_file.h variables.h LLL.h

all: ErrorChecking.o GramSchmidt.o SE_Enumeration.o result_to_file.o variables.o LLL.o
	$(CC) -o runme main.c ErrorChecking.o GramSchmidt.o SE_Enumeration.o result_to_file.o variables.o LLL.o -lm

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean: 
	rm -rf runme ErrorChecking.o GramSchmidt.o SE_Enumeration.o result_to_file.o variables.o LLL.o
# gcc -Wall main.c GramSchmidt.c SE_Enumeration.c variables.c ErrorChecking.c result_to_file.c  -lm  -o main
