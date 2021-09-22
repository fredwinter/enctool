#include "main.h"
#include "shift.h"
#include "help.h"

//considerar transformar os erros em função.

int main(int argc, char **argv)
{
	char *pname = argv[0];
	unsigned int encode_flag = 0;
	unsigned int decode_flag = 0;
	unsigned int hex_flag = 0;
	unsigned int cipher = 0;
	char *message = NULL;
	key k;

	// set the argparser not to print any errors.
	opterr = 0;
		
	//check if the number of arguments is zero and print out the help.
	if (argc == 1)
	{
		print_help(pname);
		return EXIT_FAILURE;
	}

	// parse the CLI arguments.
	int c;
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
				if (!input_is_digit(optarg))
				{
					fprintf(stderr, "%s: the cipher's code is not valid.\n", pname);
					fprintf(stderr, "Try '%s -h' for more information.\n", pname);
					return EXIT_FAILURE;
				}
				cipher = atoi(optarg);
				break;
			case 'k':
				k.is_digit = input_is_digit(optarg);
				if (k.is_digit)
				{
					k.num = atoi(optarg);
				}
				else
				{
					k.str = optarg;
				}
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

	// check if either -e or -d are set.
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

	// call the encrypt/decrypt function for the chosen cipher.
	switch (cipher)
	{
		// 1. Shift.
		case 1:
			// check if the key is a digit.
			if (!k.is_digit || k.is_digit && k.num == 0)
			{
				fprintf(stderr, "%s: shift cipher requires a positive integer as key.\n", pname);
				fprintf(stderr, "Try '%s -h' for more information.\n", pname);
				return EXIT_FAILURE;
				
			}
			else
			{
				// cap the key value limit to 26 (alphabet letters)
				res = encode_flag == 1 ? enc_shift(message, k.num % 26) : dec_shift(message, k.num % 26);
			}
			break;
		// 2. Caesar.
		case 2:
			res = encode_flag == 1 ? enc_shift(message, 3) : dec_shift(message, 3);
			break;
		// 3. ROT-13.
		case 3:
			res = encode_flag == 1 ? enc_shift(message, 13) : dec_shift(message, 13);
			break;
		// XOR.
		// case 4:
		// 	res = encode_flag == 1 ? enc_shift(message, k.str) : dec_shift(message, k.str);
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
		free(res);
	}
	else
	{
		fprintf(stderr, "%s: could not encrypt or decrypt the message.\n", pname);
		fprintf(stderr, "Try '%s -h' for more information.\n", pname);
		return EXIT_FAILURE;
	}
}

bool input_is_digit(char *arg)
{
	bool is_digit = true;
	int len = strlen(arg);
	for (int i = 0; i < len; i++)
	{
		if (!isdigit(arg[i]))
		{
			is_digit = false;
		}
	}
	return is_digit;
}