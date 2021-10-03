#include "main.h"

// melhorar o argparser
//colocar a escolha da função em arquivo separado
//colocar o parser em arquivo separado... passar o ponteiro das variáveis

int main(int argc, char **argv)
{

	const char *pname = argv[0];
	uint8_t encode_flag = 0;
	uint8_t decode_flag = 0;
	uint8_t cipher = 0;
	const char *message = NULL;
	key k;

	//set the argparser not to print any errors.
	opterr = 0;
		
	//check if the number of arguments is zero and print out the help
	if (argc == 1)
	{
		print_help(pname);
		return EXIT_FAILURE;
	}

	//parse the CLI arguments
	int c;
	while ((c = getopt(argc, argv, ":he:d:k:")) != -1)
	{
		switch(c)
		{
			//encode flag
			case 'e':
				encode_flag = 1;

				//if the encode flag is used with the decode flag, throw an error
				if (decode_flag == 1)
					err_n_exit("cannot use option -e with option -d", pname);

				//if the cipher's code is not a digit, throw an error
				if (!input_is_digit(optarg))
					err_n_exit("the cipher's code is not valid", pname);

				//set the cipher variable to the given code
				cipher = atoi(optarg);
				break;

			//decode flag
			case 'd':
				decode_flag = 1;

				//if the decode flag is used with the encode flag, throw an error
				if (encode_flag == 1)
					err_n_exit("cannot use option -e with option -d", pname);

				//if the cipher's code is not a digit, throw an error
				if (!input_is_digit(optarg))
					err_n_exit("the cipher's code is not valid", pname);

				//set the cipher variable to the given code
				cipher = atoi(optarg);
				break;

			//key
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
			
			//help
			case 'h':
				print_help(pname);
				return EXIT_SUCCESS;
			
			//errors
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

	//check if at least one of -e or -d are set
	if (encode_flag == 0 && decode_flag == 0)
		err_n_exit("one of -e of -d is required", pname);

	//set the message variable to the non-option argument passed by the user
	message = argv[optind];
	if (message == NULL)
		err_n_exit("a message is required", pname);

	char *res = NULL;

	//call the encrypt/decrypt function for the chosen cipher
	switch (cipher)
	{

		//shift
		case 1:
			//check if the key is a digit
			if (!k.is_digit || (k.is_digit && k.num == 0))
			{
				err_n_exit("shift cipher requires a positive integer as key", pname);
			}
			//cap the key value limit to 26 (alphabet letters)
			res = encode_flag == 1 ? enc_shift(message, k.num % 26) : dec_shift(message, k.num % 26);
			break;

		//caesar
		case 2:
			res = encode_flag == 1 ? enc_shift(message, 3) : dec_shift(message, 3);
			break;

		//rot-13
		case 3:
			res = encode_flag == 1 ? enc_shift(message, 13) : dec_shift(message, 13);
			break;

		//xor
		case 4:
			res = encode_flag == 1 ? enc_xor(message, k) : dec_xor(message, k);
			break;

		//vigerère
		case 5:
			break;

		//error
		default:
			err_n_exit("cipher number not valid", pname);
	}

	//print out the result
	if (res != NULL)
	{
		printf("%s\n", res);
		free(res);
	}
	else
	{
		err_n_exit("could not encrypt or decrypt the message", pname);
	}
}