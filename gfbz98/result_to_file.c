#include "result_to_file.h"
#include <stdio.h>

int res_to_file(float result) {
    char *filename = "result.txt";

    // open the file for writing
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening the file %s", filename);
        return 1;
    }
    // write to the text file
        
    fprintf(fp, "%f", result);
    // close the file
    fclose(fp);

    return 0;
}
