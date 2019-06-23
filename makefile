CFLAGS = -g -Wall -Wno-unused-result -O3
LDLIBS = -l hiredis -l readline

all: clean controlador exemplo1 

controlador: controlador.c

exemplo1: lista.h tabuleiro.h tabuleiro.c  aux.c lista.c grafo.c exemplo1.c

clean:
	rm -f controlador exemplo1 exemplo2
