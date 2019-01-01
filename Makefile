CFLAGS=-Wall
sound: sound.o
	cc -Wall -o sound sound.o
clean:
	rm *.o sound
