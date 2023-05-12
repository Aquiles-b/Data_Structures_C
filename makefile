parametrosCompilacao=-Wall -g #-Wshadow
nomePrograma=trab_20221230

all: $(nomePrograma)

$(nomePrograma): main.o avl.o fila.o
	gcc -o $(nomePrograma) main.o avl.o fila.o $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

avl.o: avl.h avl.c 
	gcc -c avl.c $(parametrosCompilacao)

fila.o: fila.h fila.c
	gcc -c fila.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)
