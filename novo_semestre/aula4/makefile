CC = gcc

CFLAGS = -g  -Wall -Werror -Wextra -pedantic
LDFLAGS = -lm

main: hospital.o main.o
	$(CC) main.o hospital.o -o hospital  $(LDFLAGS)

main.o : main.c 
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f main.o hospital.o

