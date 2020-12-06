#include "huffman.h"
#include "io.h"
#include <stdio.h>

extern void test_rd_chars_wr_bits(char in[], char out[])
{
    printf("size: %d \n", sizeof(in));
    printf("size: %d \n", sizeof(out));

    init_in(in);
    init_out();

    while (has_next_char())
    {
        unsigned char next_char = read_char();

        if (next_char < 'a')
        {
            next_char = '1';
        }
        else
        {
            next_char = '0';
        }

        write_char(next_char);
    }

    get_out_buffer(out);
}

extern void test_rd_bits_wr_chars(char in[], char out[]) {
    init_in(in);
    init_out();

    while (has_next_bit())
    {
        BIT next_bit = read_bit();
        write_bit(next_bit);
    }

    get_out_buffer(out);
}