CC=gcc
CFLAGS="-g --Wall"

all: build install

build: main.c shift.c help.c
	$(CC) $(CFLAGS) -o encryptool main.c shift.c help.c

debug:
	$(CC) $(CFLAGS) main.c shift.c help.c

install:
	mv ./encryptool /usr/bin/encryptool

clean:
	rm encryptool a.out