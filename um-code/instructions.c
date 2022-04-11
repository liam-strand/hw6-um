/*
 * instructions.c
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
#include <math.h>
#include <assert.h>
#include <seq.h>

#include "instructions.h"

extern void I_c_mov(uint32_t *source, uint32_t *dest, uint32_t *check)
{
    assert(source != NULL && dest != NULL && check != NULL);
    if ((*check) != 0) {
        *dest = *source;
    }
}

extern void I_seg_load(uint32_t *source, uint32_t *dest)
{
    assert(source != NULL && dest != NULL);
    *dest = *source;
}

extern void I_seg_store(uint32_t *source, uint32_t *dest)
{
    assert(source != NULL && dest != NULL);
    *dest = *source;
}

extern void I_add(uint32_t *reg_a, uint32_t *reg_b, uint32_t *dest)
{
    *dest = ((*reg_a) + (*reg_b)) % pow(2, 32);
}

extern void I_mult(uint32_t *reg_a, uint32_t *reg_b, uint32_t *dest)
{
    *dest = ((*reg_a) * (*reg_b)) % pow(2, 32);
}

extern void I_div(uint32_t *reg_a, uint32_t *reg_b, uint32_t *dest)
{
    *dest = ((*reg_a) / (*reg_b));
}

extern void I_nand(uint32_t *reg_a, uint32_t *reg_b, uint32_t *dest)
{
    *dest = ~((*reg_a) & (*reg_b));
}

extern void I_map(Seq_T other_segs, Seq_T available_indices, uint32_t *dest, uint32_t num_words)
// extern void I_map(Seq_T other_segs, Seq_T available_indices, uint32_t num_words, 
                                                             // uint32_t *reg_b)
{
    if (Seq_length(available_indices) == 0) {
        Seq_T recycled = (Seq_T) Seq_remlo(available_indices);
    }
    else {
      
    }
}

extern void I_unmap(Seq_T other_segs, Seq_T available_indices, uint32_t *source)
// extern void I_unmap(Seq_T other_segs, Seq_T available_indices, uint32_t num_words, 
                                                             // uint32_t *reg_c)
{

}

extern void I_out(uint32_t *reg)
{
    printf("%c", *reg);
}

extern void I_in(uint32_t *reg)
{
    *reg = fgetc();
}

extern void I_load_p(uint32_t **prog_seg_p, Seq_T     oth_segs, uint32_t *reg_b, 
                     uint32_t  *reg_c,      uint32_t *p_counter)
{

}

extern void I_load_v(uint32_t value, uint32_t *dest_reg)
{

}
