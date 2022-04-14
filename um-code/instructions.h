#ifndef INSTRUCTIONS_INCLUDED
#define INSTRUCTIONS_INCLUDED

/*
 * instructions.h
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

#include <stdlib.h>
#include <stdint.h>
#include <seq.h>

/* 
 *    Purpose: 
 * Parameters: none
 *    Returns: none
 *    Effects: none
 *       CREs: none
 *      Notes: none
 */
extern void I_c_mov(uint32_t *source, uint32_t *dest, uint32_t *check);

/* 
 *    Purpose: 
 * Parameters: none
 *    Returns: none
 *    Effects: none
 *       CREs: none
 *      Notes: none
 */
extern void I_seg_load(uint32_t *source, uint32_t *dest);

/* 
 *    Purpose: 
 * Parameters: none
 *    Returns: none
 *    Effects: none
 *       CREs: none
 *      Notes: none
 */
extern void I_seg_store(uint32_t *source, uint32_t *dest);

/* 
 *    Purpose: 
 * Parameters: none
 *    Returns: none
 *    Effects: none
 *       CREs: none
 *      Notes: none
 */
extern void I_add(uint32_t *reg_a, uint32_t *reg_b, uint32_t *dest);

/* 
 *    Purpose: 
 * Parameters: none
 *    Returns: none
 *    Effects: none
 *       CREs: none
 *      Notes: none
 */
extern void I_mult(uint32_t *reg_a, uint32_t *reg_b, uint32_t *dest);

/* 
 *    Purpose: 
 * Parameters: none
 *    Returns: none
 *    Effects: none
 *       CREs: none
 *      Notes: none
 */
extern void I_div(uint32_t *reg_a, uint32_t *reg_b, uint32_t *dest);

/* 
 *    Purpose: 
 * Parameters: none
 *    Returns: none
 *    Effects: none
 *       CREs: none
 *      Notes: none
 */
extern void I_nand(uint32_t *reg_a, uint32_t *reg_b, uint32_t *dest);

/* 
 *    Purpose: 
 * Parameters: none
 *    Returns: none
 *    Effects: none
 *       CREs: none
 *      Notes: none
 */
extern void I_map(Seq_T     other_segs, Seq_T    available_indices, 
                  uint32_t *dest,       uint32_t num_words);

/* 
 *    Purpose: 
 * Parameters: none
 *    Returns: none
 *    Effects: none
 *       CREs: none
 *      Notes: none
 */
extern void I_unmap(Seq_T other_segs, Seq_T     available_indices, 
                                      uint32_t *source);

/* 
 *    Purpose: 
 * Parameters: none
 *    Returns: none
 *    Effects: none
 *       CREs: none
 *      Notes: none
 */
extern void I_out(uint32_t *reg);

/* 
 *    Purpose: 
 * Parameters: none
 *    Returns: none
 *    Effects: none
 *       CREs: none
 *      Notes: none
 */
extern void I_in(uint32_t *reg);

/* 
 *    Purpose: 
 * Parameters: none
 *    Returns: none
 *    Effects: none
 *       CREs: none
 *      Notes: none
 */
extern void I_load_p(uint32_t **prog_seg_p, Seq_T   oth_segs, uint32_t *reg_b, 
                     uint32_t  *reg_c,      size_t *p_counter);

/* 
 *    Purpose: 
 * Parameters: none
 *    Returns: none
 *    Effects: none
 *       CREs: none
 *      Notes: none
 */
extern void I_load_v(uint32_t value, uint32_t *dest_reg);

#endif /* INSTRUCTIONS_INCLUDED */
