CC=clang
CFLAGS=-g -Wall

all: enctool

enctool: main.c shift.c help.c err_n_exit.c check_digit.c xor.c
	$(CC) $(CFLAGS) -o enctool main.c shift.c help.c err_n_exit.c check_digit.c xor.c

clean:
	rm -rf enctool a.out