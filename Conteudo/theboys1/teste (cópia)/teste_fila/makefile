# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lm

# Objetos
objects = testaFila.o fila.o

# Alvo principal
testaFila: $(objects)
	$(CC) -o testaFila $(objects) $(LDFLAGS)

# Compilação dos .c
fila.o: fila.c fila.h
	$(CC) -c $(CFLAGS) fila.c

testaFila.o: testaFila.c fila.h
	$(CC) -c $(CFLAGS) testaFila.c

# Limpeza
clean:
	rm -f $(objects) testaFila
