parametrosCompilacao=-Wall #-Wshadow
nomePrograma=hash_table

all: $(nomePrograma)

$(nomePrograma): main.o tabelaHash.o trataEntrada.o
	gcc -o $(nomePrograma) main.o tabelaHash.o trataEntrada.o $(parametrosCompilacao)

run: $(nomePrograma)
	./$(nomePrograma)

trataEntrada.o: trataEntrada.c trataEntrada.h
	gcc -c trataEntrada.c $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

tabelaHash.o: tabelaHash.h tabelaHash.c
	gcc -c tabelaHash.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)
