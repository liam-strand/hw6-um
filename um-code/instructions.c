
#include "instructions.h"
#include "assert.h"
#include <math.h>
#include <uarray.h>

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
    UArray_T mapped_arr = UArray_new(num_words, sizeof(uint32_t));
    
    if (Seq_length(available_indices) != 0) {
        int *recycled_index = *(int *) Seq_remlo(available_indices);
        Seq_put(other_segs, *recycled_index, mapped_arr);
        *dest = *recycled_index;
        FREE(recycled_index);
    }
    else {
        int new_index = Seq_length(available_indices);
        Seq_addhi(other_segs, mapped_arr);
        *dest = new_index;
    }
}

extern void I_unmap(Seq_T other_segs, Seq_T available_indices, uint32_t *source)
// extern void I_unmap(Seq_T other_segs, Seq_T available_indices, uint32_t num_words, 
                                                             // uint32_t *reg_c)
{
    int *free_index = ALLOC(sizeof(*free_index));
    *free_index = (int *) source;
    UArray_free((UArray_T *)Seq_put(other_segs, *source, NULL));
    Seq_addhi(available_indices, free_index);
}

extern void I_out(uint32_t *reg)
{
    fputc(*reg, stdout);
}

extern void I_in(uint32_t *reg)
{
    *reg = (uint32_t)fgetc(stdin);
}

extern void I_load_p(uint32_t **prog_seg_p, Seq_T     oth_segs, uint32_t *reg_b, 
                     uint32_t  *reg_c,      uint32_t *p_counter)
{
    if (*reg_b != 0) {
        uint32_t *prog = *prog_seg_p
        UArrray_T to_copy = (UArray_T) Seq_get(oth_segs, *reg_b);
        int len = UArray_length(to_copy);
        prog = (uint32_t *) RESIZE(prog, sizeof(uint32_t) * len);
        for (int i = 0; i < len; i++) {
            prog[i] = *(uint32_t *) UArray_at(to_copy, i);
        }
    }
    *p_counter = *reg_c;
}

extern void I_load_v(uint32_t value, uint32_t *dest_reg)
{
    *dest_reg = value;
}
