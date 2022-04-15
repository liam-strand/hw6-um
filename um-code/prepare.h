#ifndef PREPARE_INCLUDED
#define PREPARE_INCLUDED

/*
 * prepare.h
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

#include <stdint.h>
#include <stdio.h>

/* parse_file
 *    Purpose: Reads through the input file and pushes 32 bit encoded 
 *             instructions to the zero segment
 * Parameters: Pointers too...
 *               - File for reading in
 *               - char pointer (string indicating filename)
 *    Returns: Pointer to c-array of 32 bit instructions (zero segment)
 *    Effects: Stores instructions from input file into zero segment to execute
 *             in um_state
 *       CREs: If heap allocation of zero segment fails, throws CRE
 *      Notes: Utilizes system stat to calculate the initial length of zero_seg
 *
 */
extern uint32_t *parse_file(FILE *input_file, char *file_path);

#endif /* PREPARE_INCLUDED */
