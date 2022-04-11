
#include <stdbool.h>
#include <mem.h>
#include <seq.h>
#include <bitpack.h>

#include "um_state.h"
#include "prepare.h"
#include "instructions.h"

void clean_up(uint32_t **prog_seg_p, 
              Seq_T     *other_segs_p, 
              Seq_T     *recycled_seg_ids_p);

void execute_instructions(size_t   *program_counter,
                          uint32_t *prog_seg,
                          uint32_t *regs,
                          Seq_T     other_segs,
                          Seq_T     available_indices);

void get_regs(uint32_t inst, uint32_t *op_p, uint32_t *ra_p, 
                             uint32_t *rb_p, uint32_t *rc_p);

uint32_t *seg_source(uint32_t *prog_seg, Seq_T    other_segs, 
                     uint32_t  seg_num,  uint32_t seg_index);

extern void um_run(FILE *input_file, char *file_path)
{
    uint32_t *prog_seg = parse_file(input_file, file_path);

    size_t prog_counter = 0;
    (void)prog_counter;

    uint32_t r[8];
    (void)r;

    Seq_T other_segs   = Seq_new(5);
    Seq_T recycled_ids = Seq_new(5);

    execute_instructions(&prog_counter, prog_seg, r, other_segs, recycled_ids);

    clean_up(&prog_seg, &other_segs, &recycled_ids);
}

void clean_up(uint32_t **prog_seg_p, 
              Seq_T     *other_segs_p, 
              Seq_T     *recycled_seg_ids_p)
{
    FREE(*prog_seg_p);
    Seq_free(other_segs_p);
    Seq_free(recycled_seg_ids_p);

    *prog_seg_p         = NULL;
    *other_segs_p       = NULL;
    *recycled_seg_ids_p = NULL;
}

void execute_instructions(size_t   *program_counter,
                          uint32_t *prog_seg,
                          uint32_t *regs,
                          Seq_T     other_segs,
                          Seq_T     available_indices)
{

    (void)other_segs;
    (void)available_indices;

    bool shouldContinue = true;

    while (shouldContinue) {

        uint32_t inst = prog_seg[*program_counter];

        uint32_t op, ra, rb, rc;
        get_regs(inst, &op, &ra, &rb, regs[rc]);

        fprintf(stderr, "%d %d %d %d\n", op, ra, rb, rc);

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
                I_add(&regs[ra], &regs[rb], &regs[rc]);
                break;
            case 4:
                I_mult(&regs[ra], &regs[rb], &regs[rc]);
                break;
            case 5:
                I_div(&regs[ra], &regs[rb], &regs[rc]);
                break;
            case 6:
                I_nand(&regs[ra], &regs[rb], &regs[rc]);
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
                uint32_t reg_id = Bitpack_getu(inst, 3, 25);
                uint32_t value  = Bitpack_getu(inst, 25, 0);
                I_load_v(value, &regs[reg_id]);
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
