#include "ErrorChecking.h"
#include "variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int error_checking_arg(int argc, char *argv[]) { // Checks if the basis vectors inputted in the terminal is correct 
    int no_of_elements = 0, no_of_vectors = 0; 

    for (int i = 1; i < argc; i++) {
        no_of_elements += 1;
        if (strchr(argv[i], ']') != NULL) {
            no_of_vectors += 1;
        }

        int num = atoi(argv[i]);
        if (num == 0 && *argv[i] != '0' && strchr(argv[i], '[') == NULL) {
            printf("ERROR: a vector was not formatted correctly\n");
            return 0;
        }
    }

    if (no_of_elements % no_of_vectors != 0) {
        printf("ERROR: Inconsistent dimensions of basis given\n");
        return 0;
    }

    if (no_of_elements/no_of_vectors != no_of_vectors) {
        printf("ERROR: Basis Vectors given do not form a square matrix\n");
        return 0;
    }
    return no_of_vectors;
}
