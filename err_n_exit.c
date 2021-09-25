#include "err_n_exit.h"

void err_n_exit(const char *err_message, const char *pname) {
    fprintf(stderr, "%s: %s.\n", pname, err_message);
    fprintf(stderr, "Try '%s -h' for more information.\n", pname);
    exit(EXIT_FAILURE);
}