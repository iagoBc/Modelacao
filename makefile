# PROGRAMA
    PROG = main

# arquivos a compilar
	HDR = $(wildcard *.h)			# headers
	SRC = $(wildcard *.c)			# fontes C
	OBJ = $(patsubst %.c,%.o,$(SRC))	# objetos .o
	CC = gcc
	CFLAGS = -Wall -g -std=c99
.PHONY: all clean purge

%.o: %.c %.h
	$(CC) -o $@ $<

all: $(PROG)

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ 
	
clean:
	@rm -f *~ *.o

purge:  clean
	@rm -f $(PROG) 
