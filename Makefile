wave: wave.o
	gcc -lm -o wave wave.o

wave.o: wave.c
	gcc -c -o wave.o wave.c

play: wave
	./play.sh

.PHONY: play
