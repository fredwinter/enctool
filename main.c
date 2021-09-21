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
				break;
			case 'd':
				decode_flag = 1;
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
					fprintf(stderr, "Option '-%c' requires a cipher as an argument.\n", optopt);
				}
				else if (isprint(optopt))
				{
					fprintf(stderr, "Unknown option '-%c'.\n", optopt);
				}
				print_help(pname);
				return EXIT_FAILURE;
			default:
				print_help(pname);
				return EXIT_FAILURE;
		}
	}
}