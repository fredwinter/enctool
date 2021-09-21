CC=gcc

all: build install

build: main.c shift.c help.c
	$(CC) -o encryptool main.c shift.c help.c

install:
	mv ./encryptool /usr/bin/encryptool

clean:
	rm encryptool

dep:
	$(CC) main.c shift.c help.c