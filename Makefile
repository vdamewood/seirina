all: cmaj

cmaj: cmaj.o waves.o
	$(CC) -lm -o cmaj waves.o cmaj.o

waves.o: waves.c
	$(CC) -c -o waves.o waves.c

cmaj.o: cmaj.c
	$(CC) -c -o cmaj.o cmaj.c

.PHONY: play
