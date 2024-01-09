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
    // for (int i = 0; i < 10; i++)
    //     fprintf(fp, "This is the line #%d\n", i + 1);
        
    fprintf(fp, "%f", result);
    // close the file
    fclose(fp);

    return 0;
}
