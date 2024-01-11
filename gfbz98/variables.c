#include "variables.h"
#include "stdlib.h"
#include <stdio.h>
#include <string.h>

int size;

void global_array_size(int array_size) {
    size = array_size;
}

// https://stackoverflow.com/questions/9895216/how-to-remove-all-occurrences-of-a-given-character-from-string-in-c
void remove_all_chars(char* str, char c) {
    char *pr = str, *pw = str;
    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}

float ** lattice_basis(int argc, char *argv[])  {
    
    // Code from https://stackoverflow.com/questions/5201708/how-to-return-a-2d-array-from-a-function-in-c
    float* values = calloc(argc*argc, sizeof(float));
    float** matrix_basis = malloc(argc*sizeof(float*));

    int new_row = 0;
    int new_col = 0;

    for (int i=0; i < argc; ++i) {
        matrix_basis[i] = values + i*argc;
    }

    for (int i = 1; i < argc; i++) {
        if (strchr(argv[i], ']') != NULL) {
            remove_all_chars(argv[i], ']');
            matrix_basis[new_row][new_col] = atof(argv[i]);
            new_row += 1;
            new_col = 0;
            continue;
        }
        
        if (strchr(argv[i], '[') != NULL) {
            remove_all_chars(argv[i], '[');
        } 
        matrix_basis[new_row][new_col] = atof(argv[i]);
        new_col += 1;
    }

    return matrix_basis; 
}
