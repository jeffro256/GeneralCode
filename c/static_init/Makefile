.PHONY: all clean
all: static_init.out clean

static_init.out: main.o
	gcc main.o -o static_init.out

main.o: main.c
	gcc -c main.c

clean:
	rm main.o
