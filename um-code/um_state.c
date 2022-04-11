
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
                          Seq_T     other_segs,
                          Seq_T     available_indices);

void get_regs(uint32_t inst, uint32_t *op_p, uint32_t *ra_p, 
                             uint32_t *rb_p, uint32_t *rc_p);

extern void um_run(FILE *input_file, char *file_path)
{
    uint32_t *prog_seg = parse_file(input_file, file_path);

    size_t prog_counter = 0;
    (void)prog_counter;

    uint32_t r[8];
    (void)r;

    Seq_T other_segs   = Seq_new(5);
    Seq_T recycled_ids = Seq_new(5);

    execute_instructions(&prog_counter, prog_seg, other_segs, recycled_ids);

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
                          Seq_T     other_segs,
                          Seq_T     available_indices)
{

    (void)other_segs;
    (void)available_indices;

    bool shouldContinue = true;

    while (shouldContinue) {

        uint32_t inst = prog_seg[*program_counter];

        uint32_t op, ra, rb, rc;
        get_regs(inst, &op, &ra, &rb, &rc);

        fprintf(stderr, "%d %d %d %d\n", op, ra, rb, rc);

        (*program_counter)++;

        switch(op) {
            case 0:
                fprintf(stderr, "cmov\n"); 
                break;
            case 1:
                fprintf(stderr, "segl\n"); 
                break;
            case 2:
                fprintf(stderr, "segs\n"); 
                break;
            case 3:
                fprintf(stderr, "addd\n"); 
                break;
            case 4:
                fprintf(stderr, "mult\n"); 
                break;
            case 5:
                fprintf(stderr, "divs\n"); 
                break;
            case 6:
                fprintf(stderr, "nand\n"); 
                break; 
            case 7:
                fprintf(stderr, "halt\n"); 
                break; 
            case 8:
                fprintf(stderr, "maps\n"); 
                break;
            case 9:
                fprintf(stderr, "umap\n"); 
                break;
            case 10:
                fprintf(stderr, "outp\n"); 
                break;
            case 11:
                fprintf(stderr, "inpu\n"); 
                break;
            case 12:
                fprintf(stderr, "loap\n"); 
                break;
            case 13:
                fprintf(stderr, "loav\n"); 
                break;
            default:
                fprintf(stderr, "fuck\n"); 
                break;
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
