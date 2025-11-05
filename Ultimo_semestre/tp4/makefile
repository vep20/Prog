<<<<<<< HEAD
# makefile generico para os TADs
# Carlos Maziero - DINF/UFPR

CC     = gcc
CFLAGS = -Wall -Wextra -g -std=c99
LIB    = lista
BIN    = tp4
OUT    = saida.txt

# gera o arquivo executável
$(BIN):   $(BIN).o $(LIB).o

# gera os arquivos-objeto
$(BIN).o: $(BIN).c $(LIB).h
$(LIB).o: $(LIB).c $(LIB).h

# teste de execução
teste: $(BIN)
	./$(BIN) > $(OUT)
	@echo "Diferenças entre saida esperada e gerada:"
	@diff $(BIN).txt $(OUT)

# verificação de memória
valgrind: $(BIN)
	valgrind --leak-check=full --track-origins=yes ./$(BIN)

# limpeza
clean:
	rm -f *.o *~ $(BIN) $(OUT)
=======
# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -Werror -Wextra -std=c90 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = tp4.o lista.o 

tp4: tp4.o lista.o
	$(CC) -o tp4 tp4.o lista.o $(LDFLAGS)

fila.o: fila.c
	$(CC) -c $(CFLAGS) lista.c

testa_fila.o: testa_fila.c
	$(CC) -c $(CFLAGS) tp4.c

clean:
	rm -f $(objects) tp4
>>>>>>> 79c6643f210888d3da082903eb3766d1d1dd7b99
