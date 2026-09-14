# PROGRAMA
    PROG = energia

# arquivos a compilar
	HDR = $(wildcard codigos/*.h)			# headers
	SRC = $(wildcard codigos/*.c)			# fontes C
	OBJ = $(SRC:.c=.o)				# objetos .o
	CC = gcc
	CFLAGS = -Wall -g -std=c99
.PHONY: all clean purge

codigos/%.o: codigos/%.c $(HDR)
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(PROG)

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ 
	
clean:
	@rm -f *~ *.o codigos/*.o

purge:  clean
	@rm -f $(PROG) 
