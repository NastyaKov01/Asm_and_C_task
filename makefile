CC=gcc
NASM=nasm
CFLAGS+=-W -Wall -g -O2 -m32
ASMFLAGS+=-g -f elf32
.PHONY: all clean

all: func

func: main.o func.o
		$(CC) $(CFLAGS) -o $@ $^
		
main.o: main.c
		$(CC) $(CFLAGS) -c $<
		
func.o: func.asm
		$(NASM) $(ASMFLAGS) $< -o $@
		
clean:
		rm -rf *.o
