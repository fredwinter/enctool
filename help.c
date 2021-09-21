#include "help.h"

void print_help(char *pname)
{
	printf("Encryptool is a simple tool for basic encryption.\n");
	printf("It can be downloaded at https://github.com/scnprt/encryptool\n\n");

	printf("Usage: %s <options> <message>\n\n", pname);

	printf("Options:\n");
	printf("\t-h\t\t\tPrint this help message.\n");
	printf("\t-e\t\t\tEncrypt the message. Required to encrypt the message.\n");
	printf("\t-d\t\t\tDecrypt the message. Required to decrypt the message.\n");
	printf("\t-c <number>\t\tSelect the cipher's number. Required.\n");
	printf("\t-k <number>\t\tSome ciphers require a key, that must be a positive number.\n");
	printf("\t-x\t\t\tPrint the encrypted message as hexadecimal.\n");

	printf("\n");

	printf("Available Ciphers:\n");
	printf("\t1\t\t\tShift. Requires a key.\n");
	printf("\t2\t\t\tCaesar.\n");
	printf("\t3\t\t\tROT-13.\n");
}