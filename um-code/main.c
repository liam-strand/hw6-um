/*
 * main.c
 *
 * COMP 40 HW6: um
 *
 * By:   Matt Ung (mung01)
 *    Liam Strand (lstran01)
 *
 * On: April 2022
 *
 * TODO
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <assert.h>

#include "um_state.h"

FILE *prepare_args(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    FILE *input_file = prepare_args(argc, argv);
    
    if (input_file == NULL) {
        return EXIT_FAILURE;
    } 

    um_run(input_file, argv[1]);

    fclose(input_file);

    return EXIT_SUCCESS;
}

/* prepare_args
 *    Purpose: Prepares and verifies the command line arguments
 * Parameters: The number of arguments and the arguments themselves
 *    Returns: An opened FILE pointer to the umfile, or NULL
 *    Effects: Prints to stderr if contract violation or file cannot be opened
 *       CREs: none
 *      Notes: none
 */
FILE *prepare_args(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: um <umfile>\n");
        return NULL;
    }


    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        fprintf(stderr, "%s could not be opened\n", argv[1]);
        return NULL;
    }

    return file;
}
