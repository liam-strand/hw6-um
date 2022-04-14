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
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <assert.h>
#include <seq.h>
#include <mem.h>
#include <uarray.h>

#include "instructions.h"

/* 
 * 
 * 
 */
extern void I_c_mov(uint32_t *source, uint32_t *dest, uint32_t *check)
{
    assert(source != NULL && dest != NULL && check != NULL);
    if ((*check) != 0) {
        *dest = *source;
    }
}

/* 
 * 
 * 
 */
extern void I_seg_load(uint32_t *source, uint32_t *dest)
{
    assert(source != NULL && dest != NULL);
    *dest = *source;
}

/* 
 * 
 * 
 */
extern void I_seg_store(uint32_t *source, uint32_t *dest)
{
    assert(source != NULL && dest != NULL);
    *dest = *source;
}

/* 
 * 
 * 
 */
extern void I_add(uint32_t *reg_a, uint32_t *reg_b, uint32_t *dest)
{
    *dest = *reg_a + *reg_b;
}

/* 
 * 
 * 
 */
extern void I_mult(uint32_t *reg_a, uint32_t *reg_b, uint32_t *dest)
{
    *dest = ((*reg_a) * (*reg_b));
}

/* 
 * 
 * 
 */
extern void I_div(uint32_t *reg_a, uint32_t *reg_b, uint32_t *dest)
{
    *dest = ((*reg_a) / (*reg_b));
}

/* 
 * 
 * 
 */
extern void I_nand(uint32_t *reg_a, uint32_t *reg_b, uint32_t *dest)
{
    *dest = ~((*reg_a) & (*reg_b));
}

/* 
 * 
 * 
 */
extern void I_map(Seq_T     other_segs, 
                  Seq_T     available_indices, 
                  uint32_t *dest, 
                  uint32_t  num_words)
{
    UArray_T mapped_arr = UArray_new(num_words, sizeof(uint32_t));
    if (Seq_length(available_indices) != 0) {
        int *recycled_index = (int *) Seq_remlo(available_indices);
        Seq_put(other_segs, *recycled_index, mapped_arr);
        *dest = *recycled_index;
        FREE(recycled_index);
    }
    else {
        int new_index = Seq_length(other_segs);
        Seq_addhi(other_segs, mapped_arr);
        *dest = new_index;
    }
}

/* 
 * 
 * 
 */
extern void I_unmap(Seq_T     other_segs, 
                    Seq_T     available_indices, 
                    uint32_t *source)
{
    int *free_index = ALLOC(sizeof(*free_index));
    *free_index = *(int *) source;
    UArray_T to_free = (UArray_T)Seq_put(other_segs, *source, NULL);
    UArray_free(&to_free);
    Seq_addhi(available_indices, free_index);
}

/* 
 * 
 * 
 */
extern void I_out(uint32_t *reg)
{
    assert(*reg < 256);
    fputc(*reg, stdout);
}

/* 
 * 
 * 
 */
extern void I_in(uint32_t *reg)
{
    *reg = (uint32_t)fgetc(stdin);
}

/* 
 * 
 * 
 */
extern void I_load_p(uint32_t **prog_seg_p, Seq_T   oth_segs, uint32_t *reg_b, 
                     uint32_t  *reg_c,      size_t *p_counter)
{
    if (*reg_b != 0) {
        FREE(*prog_seg_p);
        UArray_T to_copy = (UArray_T) Seq_get(oth_segs, *reg_b);
        int len = UArray_length(to_copy);
        uint32_t *new_prog = ALLOC(sizeof(*new_prog) * len);
        for (int i = 0; i < len; i++) {
            new_prog[i] = *(uint32_t *) UArray_at(to_copy, i);
        }
        // fprintf(stderr, "prog_seg1: %p\n", (void *)*prog_seg_p);
        *prog_seg_p = new_prog;
        // fprintf(stderr, "prog_seg2: %p\n", (void *)*prog_seg_p);
        // fprintf(stderr, "heyo\n");
    }
    *p_counter = *reg_c;
    // fprintf(stderr, "reg_c: %d\n", *reg_c);
}

/* 
 * 
 * 
 */
extern void I_load_v(uint32_t value, uint32_t *dest_reg)
{
    *dest_reg = value;
}
