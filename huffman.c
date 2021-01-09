#include "huffman.h"
#include "huffman_common.h"
#include "io.h"

extern void test_rd_chars_wr_bits(char in_filename[], char out_filename[])
{
    open_infile(in_filename);
    open_outfile(out_filename);

    while (read_infile() != 0)
    {
        while (has_next_char())
        {
            unsigned char next_char = read_char();
            BIT next_bit = BIT0;

            if (next_char < 'a')
            {
                next_bit = BIT1;
            }

            write_bit(next_bit);
        }

        write_outfile();
    }

    close_infile();
    close_outfile();
}

extern void test_rd_bits_wr_chars(char in_filename[], char out_filename[]) {

    open_infile(in_filename);
    open_outfile(out_filename);


    while (read_infile() != 0)
    {
        while (has_next_bit())
        {
            BIT next_bit = read_bit();
            unsigned char next_char = '0';

            if (next_bit == BIT1)
            {
                next_char = '1';
            }

            write_char(next_char);
        }

        write_outfile();
    }


    close_infile();
    close_outfile();
}
