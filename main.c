#include <stdio.h>
#include <string.h>
#include "io.h"
#include "huffman.h"
#include "huffman_common.h"

int main()
{
    char in[] = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxX";
    print_out_char_array(in);
    printf("\nsize: %d \n", sizeof(in));
    char out[50] = {0};
    printf("size: %d \n", sizeof(out));

    test_rd_chars_wr_bits(in, out);
    strcmp(out, "UUUUUU");
    print_out_char_array(out);
    return 0;
}

