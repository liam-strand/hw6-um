/*
 * um_state.c
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


#include <stdbool.h>
#include <stdint.h>
#include <mem.h>
#include <seq.h>
#include <assert.h>
#include <bitpack.h>
#include <uarray.h>

#include "um_state.h"
#include "prepare.h"
#include "instructions.h"

/* clean_up
 *    Purpose: Frees memory associated with heap-allocated data structures
 * Parameters: Pointers to...
 *               - The array holding the program (zero) segment
 *               - The Seq holding the other segments
 *               - The Seq holding recycled segment IDs
 *    Returns: none
 *    Effects: Recycles all memory associated with the data structures above.
 *             Additionally sets their values to NULL to prevent unwanted
 *             access of uninitilized memory.
 *       CREs: Any of the parameters, or their dereferences are NULL
 *      Notes: none
 */
void clean_up(uint32_t **prog_seg_p, Seq_T *other_segs_p, Seq_T *recycled_p);

/* execute_instructions
 *    Purpose: Contains the main program loop. Reads through the program
 *             segment in 
 * Parameters: none
 *    Returns: none
 *    Effects: none
 *       CREs: none
 *      Notes: none
 */
void execute_instructions(size_t   *program_counter,
                          uint32_t *prog_seg,
                          uint32_t *regs,
                          Seq_T     other_segs,
                          Seq_T     available_indices);

void get_regs(uint32_t inst, uint32_t *op_p, uint32_t *ra_p, 
                             uint32_t *rb_p, uint32_t *rc_p);

void prepare_lv(uint32_t inst, uint32_t *reg_id, uint32_t *value);

uint32_t *seg_source(uint32_t *prog_seg, Seq_T    other_segs,
                     uint32_t  seg_num,  uint32_t seg_index);

void deep_free_uarray(Seq_T seq);
void deep_free_int(Seq_T seq);

extern void um_run(FILE *input_file, char *file_path)
{
    uint32_t *prog_seg = parse_file(input_file, file_path);

    size_t prog_counter = 0;

    uint32_t r[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    Seq_T other_segs = Seq_new(5);
    Seq_addlo(other_segs, NULL);

    Seq_T recycled_ids = Seq_new(5);

    execute_instructions(&prog_counter, prog_seg, r, other_segs, recycled_ids);

    clean_up(&prog_seg, &other_segs, &recycled_ids);
}

void execute_instructions(size_t   *program_counter,
                          uint32_t *prog_seg,
                          uint32_t *regs,
                          Seq_T     other_segs,
                          Seq_T     available_indices)
{
    bool shouldContinue = true;

    while (shouldContinue) {

        // fprintf(stderr, "%d %d %d\n", regs[1], regs[2], regs[3]);

        uint32_t inst = prog_seg[*program_counter];

        uint32_t op, ra, rb, rc, value;
        get_regs(inst, &op, &ra, &rb, &rc);

        // fprintf(stderr, "%d %d %d %d\n", op, ra, rb, rc);

        (*program_counter)++;

        switch(op) {
            case 0:
                I_c_mov(&regs[rb], &regs[ra], &regs[rc]);
                break;
            case 1:
                I_seg_load(seg_source(prog_seg, other_segs, regs[rb], regs[rc]), &regs[ra]); 
                break;
            case 2:
                I_seg_store(&regs[rc], seg_source(prog_seg, other_segs, regs[ra], regs[rb])); 
                break;
            case 3:
                I_add(&regs[rb], &regs[rc], &regs[ra]);
                break;
            case 4:
                I_mult(&regs[rb], &regs[rc], &regs[ra]);
                break;
            case 5:
                I_div(&regs[rb], &regs[rc], &regs[ra]);
                break;
            case 6:
                I_nand(&regs[rb], &regs[rc], &regs[ra]);
                break; 
            case 7:
                shouldContinue = false;
                break; 
            case 8:
                I_map(other_segs, available_indices, &regs[rb], regs[rc]);
                break;
            case 9:
                I_unmap(other_segs, available_indices, &regs[rc]);
                break;
            case 10:
                I_out(&regs[rc]);
                break;
            case 11:
                I_in(&regs[rc]);
                break;
            case 12:
                I_load_p(&prog_seg, other_segs, &regs[rb], &regs[rc], program_counter);
                break;
            case 13:
                prepare_lv(inst, &ra, &value);
                I_load_v(value, &regs[ra]);
                break;
            default:
                fprintf(stderr, "fuck\n"); 
                shouldContinue = false;
        }
    }
}

void get_regs(uint32_t inst, uint32_t *op_p, uint32_t *ra_p, 
                             uint32_t *rb_p, uint32_t *rc_p)
{
    *op_p = Bitpack_getu(inst, 4, 28);
    *ra_p = Bitpack_getu(inst, 3,  6);
    *rb_p = Bitpack_getu(inst, 3,  3);
    *rc_p = Bitpack_getu(inst, 3,  0);
}

void prepare_lv(uint32_t inst, uint32_t *reg_id, uint32_t *value)
{
    *reg_id = Bitpack_getu(inst, 3, 25);
    *value  = Bitpack_getu(inst, 25, 0);
}

uint32_t *seg_source(uint32_t *prog_seg, Seq_T    other_segs,
                     uint32_t  seg_num,  uint32_t seg_index)
{
    if (seg_num == 0) {
        return &prog_seg[seg_index];
    } else {
        uint32_t *segment = Seq_get(other_segs, seg_num);
        return &segment[seg_index];
    }
}

void clean_up(uint32_t **prog_seg_p, Seq_T *other_segs_p, Seq_T *recycled_p)
{
    assert( prog_seg_p != NULL &&  other_segs_p != NULL &&  recycled_p != NULL);
    assert(*prog_seg_p != NULL && *other_segs_p != NULL && *recycled_p != NULL);
    
    FREE(*prog_seg_p);

    deep_free_uarray(*other_segs_p);
    deep_free_int(*recycled_p);

    Seq_free(other_segs_p);
    Seq_free(recycled_p);

    *prog_seg_p   = NULL;
    *other_segs_p = NULL;
    *recycled_p   = NULL;
}

void deep_free_uarray(Seq_T seq)
{
    unsigned len = Seq_length(seq);
    for (unsigned i = 1; i < len; i++) {
        UArray_T ua = (UArray_T)Seq_get(seq, i);
        if (ua != NULL) {
            UArray_free(&ua);
        }
    }
}

void deep_free_int(Seq_T seq)
{
    unsigned len = Seq_length(seq);
    for (unsigned i = 0; i < len; i++) {
        int *n = (int *)Seq_get(seq, i);
        if (n != NULL) {
            FREE(n);
        }
    }
}
