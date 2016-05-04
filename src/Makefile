all: cmaj mary

clean:
	rm -Rf *.o

distclean: clean
	rm -Rf cmaj mary

cmaj: cmaj.o output.o waves.o
	$(CC) -lm -o cmaj waves.o output.o cmaj.o

mary: mary.o output.o waves.o
	$(CC) -lm -o mary waves.o mary.o output.o

mary.o: mary.c waves.h
	$(CC) -c -o mary.o mary.c

output.o: output.c output.h
	$(CC) -c -o output.o output.c

waves.o: waves.c waves.h
	$(CC) -c -o waves.o waves.c

cmaj.o: cmaj.c
	$(CC) -c -o cmaj.o cmaj.c

.PHONY: all clean distclean
