#include "main.h"
#include "shift.h"
#include "help.h"

// TODO:
// tentar um autocomplete.

int main(int argc, char **argv)
{
	char *pname = argv[0];
	unsigned int encode_flag = 0;
	unsigned int decode_flag = 0;
	char *cipher = NULL;
	unsigned int key;
	unsigned int hex_flag = 0;
	char *message = NULL;
	int c;

	// set the argparser not to print any errors.
	opterr = 0;
		
	// check if the number of arguments is zero and
	// print out the help.
	if (argc == 1)
	{
		print_help(pname);
		return EXIT_FAILURE;
	}

	// parse the CLI arguments.
	while ((c = getopt(argc, argv, "hedc:kx")) != -1)
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
				cipher = optarg;
				break;
			case 'x':
				hex_flag = 1;
				break;
			case 'h':
				print_help(pname);
				return EXIT_SUCCESS;
			case '?':
				if (optopt == 'c')
				{
					fprintf(stderr, "%s: option '-%c' requires a cipher number as an argument.\n", pname, optopt);
					fprintf(stderr, "Try '%s -h' for more information.\n", pname);
				}
				else if (isprint(optopt))
				{
					fprintf(stderr, "%s: invalid option '-%c'.\n", pname, optopt);
					fprintf(stderr, "Try '%s -h' for more information.\n", pname);
				}
				return EXIT_FAILURE;
			default:
				print_help(pname);
				return EXIT_FAILURE;
		}
	}

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
	printf("Message: %s\n", message);
}
