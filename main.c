#include "main.h"
#include "shift.h"
#include "help.h"

// TODO:
// tentar um autocomplete.

int main(int argc, char **argv)
{
	char *pname = argv[0];
	uint8_t encode_flag = 0;
	uint8_t decode_flag = 0;
	uint8_t cipher;
	uint8_t key = 0;
	uint8_t hex_flag = 0;
	char *message = NULL;
	int c;

	// set the argparser not to print any errors.
	opterr = 0;
		
	//check if the number of arguments is zero and print out the help.
	if (argc == 1)
	{
		print_help(pname);
		return EXIT_FAILURE;
	}

	// parse the CLI arguments.
	while ((c = getopt(argc, argv, ":hedxc:k:")) != -1)
	{
		switch(c)
		{
			case 'e':
				encode_flag = 1;
				if (decode_flag == 1)
				{
					fprintf(stderr, "%s: cannot use option -e with option -d.\n", pname);
					fprintf(stderr, "Try '%s -h' for more information.\n", pname);
					return EXIT_FAILURE;
				}
				break;
			case 'd':
				decode_flag = 1;
				if (encode_flag == 1)
				{
					fprintf(stderr, "%s: cannot use option -e with option -d.\n", pname);
					fprintf(stderr, "Try '%s -h' for more information.\n", pname);
					return EXIT_FAILURE;
				}
				break;
			case 'c':
				if (!atoi(optarg))
				{
					fprintf(stderr, "%s: cipher number not valid.\n", pname);
					fprintf(stderr, "Try '%s -h' for more information.\n", pname);
					return EXIT_FAILURE;
				}
				cipher = atoi(optarg);
				break;
			case 'k':
				if (atoi(optarg) <= 0)
				{
					fprintf(stderr, "%s: key value must be a potivive int.\n", pname);
					fprintf(stderr, "Try '%s -h' for more information.\n", pname);
					return EXIT_FAILURE;
				}
				key = atoi(optarg);
				break;
			case 'x':
				hex_flag = 1;
				break;
			case 'h':
				print_help(pname);
				return EXIT_SUCCESS;
			case ':':
				fprintf(stderr, "%s: option '-%c' requires an argument.\n", pname, optopt);
				fprintf(stderr, "Try '%s -h' for more information.\n", pname);
				return EXIT_FAILURE;
			case '?':
				fprintf(stderr, "%s: invalid option '-%c'.\n", pname, optopt);
				fprintf(stderr, "Try '%s -h' for more information.\n", pname);
				return EXIT_FAILURE;
			default:
				print_help(pname);
				return EXIT_FAILURE;
		}
	}

	// check if both -e and -d are set.
	if (encode_flag == 0 && decode_flag == 0)
	{
		fprintf(stderr, "%s: one of -e of -d is required.\n", pname);
		fprintf(stderr, "Try '%s -h' for more information.\n", pname);
		return EXIT_FAILURE;
	}

	// set the message variable to the non-option argument.
	message = argv[optind];
	if (message == NULL)
	{
		fprintf(stderr, "%s: a message is required.\n", pname);
		fprintf(stderr, "Try '%s -h' for more information.\n", pname);
		return EXIT_FAILURE;
	}

	char *res = NULL;

	// call the cipher function.
	switch (cipher)
	{
		case 1: // Shift.
			if (key == 0)
			{
				fprintf(stderr, "%s: shift cipher requires a key.\n", pname);
				fprintf(stderr, "Try '%s -h' for more information.\n", pname);
				return EXIT_FAILURE;
			}
			if (encode_flag == 1)
			{
				res = enc_shift(message, key % 26); // cap the key value limit to 26 (alphabet letters)
			}
			else if (decode_flag == 1)
			{
				res = dec_shift(message, key % 26); // cap the key value limit to 26 (alphabet letters)
			}
			break;
		case 2: // Caesar.
			if (encode_flag == 1)
			{
				res = enc_shift(message, 3);
			}
			else if (decode_flag == 1)
			{
				res = dec_shift(message, 3);
			}
			break;
		case 3: // ROT-13.
			if (encode_flag == 1)
			{
				res = enc_shift(message, 13);
			}
			else if (decode_flag == 1)
			{
				res = dec_shift(message, 13);
			}
			break;
		default:
			fprintf(stderr, "%s: cipher number not valid.\n", pname);
			fprintf(stderr, "Try '%s -h' for more information.\n", pname);
			return EXIT_FAILURE;
	}

	// print out the result.
	if (res != NULL)
	{
		printf("Message: %s\n", message);
		printf("Result: %s\n", res);
		if (hex_flag == 1)
		{
			printf("Result in hexadecimal: 0x%x\n", res);
		}
	}
	else
	{
		fprintf(stderr, "%s: could not encrypt or decrypt the message.\n", pname);
		fprintf(stderr, "Try '%s -h' for more information.\n", pname);
		return EXIT_FAILURE;
	}
}
