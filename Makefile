CC=gcc

default:
	$(CC) -O3 -Wall -o imeigen imeigen.c

clean:
	rm -f imeigen
