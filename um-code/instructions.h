#ifndef INSTRUCTIONS_INCLUDED
#define INSTRUCTIONS_INCLUDED

#include <stdint.h>
#include <seq.h>

extern void c_mov(uint32_t *source, uint32_t *dest, uint32_t *check);
extern void seg_load(uint32_t *source, uint32_t *dest);
extern void seg_store(uint32_t *source, uint32_t *dest);
extern void add(uint32_t *reg_a, uint32_t *reg_b, uint32_t *dest);
extern void mult(uint32_t *reg_a, uint32_t *reg_b, uint32_t *dest);
extern void div(uint32_t *reg_a, uint32_t *reg_b, uint32_t *dest);
extern void nand(uint32_t *reg_a, uint32_t *reg_b, uint32_t *dest);
extern void map(Seq_T other_segs, Seq_T available_indices, uint32_t num_words);
extern void unmap(Seq_T other_segs, Seq_T available_indices, uint32_t num_words);
extern void out(uint32_t *reg);
extern void in(uint32_t *reg);
extern void load_p(uint32_t **prog_seg_p, Seq_T     oth_segs, uint32_t *reg_b, 
                   uint32_t  *reg_c,      uint32_t *p_counter);
extern void load_v(uint32_t value, uint32_t *dest_reg);

#endif /* INSTRUCTIONS_INCLUDED */
