#ifndef INSTRUCTIONS_INCLUDED
#define INSTRUCTIONS_INCLUDED

#include <stdint.h>
#include <seq.h>

extern void I_c_mov(uint32_t *source, uint32_t *dest, uint32_t *check);
extern void I_seg_load(uint32_t *source, uint32_t *dest);
extern void I_seg_store(uint32_t *source, uint32_t *dest);
extern void I_add(uint32_t *reg_a, uint32_t *reg_b, uint32_t *dest);
extern void I_mult(uint32_t *reg_a, uint32_t *reg_b, uint32_t *dest);
extern void I_div(uint32_t *reg_a, uint32_t *reg_b, uint32_t *dest);
extern void I_nand(uint32_t *reg_a, uint32_t *reg_b, uint32_t *dest);
extern void I_map(Seq_T other_segs, Seq_T available_indices, uint32_t *dest, uint32_t num_words);
extern void I_unmap(Seq_T other_segs, Seq_T available_indices, uint32_t *source);
extern void I_out(uint32_t *reg);
extern void I_in(uint32_t *reg);
extern void I_load_p(uint32_t **prog_seg_p, Seq_T   oth_segs, uint32_t *reg_b, 
                     uint32_t  *reg_c,      size_t *p_counter);
extern void I_load_v(uint32_t value, uint32_t *dest_reg);

#endif /* INSTRUCTIONS_INCLUDED */
