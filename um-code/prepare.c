
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>
#include <mem.h>
#include <bitpack.h>

#include "prepare.h"

static const unsigned BYTE_SIZE = 8;

/* union ArrToInt {
    unsigned char array[4];
    uint32_t      integer;
}; */

uint32_t read_one_instruction(FILE *input_file);

extern uint32_t *parse_file(FILE *input_file, char *file_path)
{
    struct stat buf;
    stat(file_path, &buf);

    size_t inst_count = buf.st_size / 4;

    uint32_t *zero_seg = ALLOC(sizeof(uint32_t) * inst_count);

    for (size_t i = 0; i < inst_count; i++) {
        zero_seg[i] = read_one_instruction(input_file);
    }

    return zero_seg;
}

uint32_t read_one_instruction(FILE *input_file)
{
    uint32_t inst = 0;

    for (int i = 3; i >= 0; i--) {
        unsigned char byte = fgetc(input_file);
        inst = Bitpack_newu(inst, BYTE_SIZE, i * BYTE_SIZE, byte);
    }

    return inst;
}
