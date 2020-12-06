/**
 * @mainpage huffman
 *
 * Dieses Projekt realisiert die Huffman-Kodierung.
 *
 * @author  Tim Ostermann
 * @date    2020-12-05
 */

/**
 * @file
 *
 * @author  Tim Ostermann
 * @date    2020-12-05
 */

#include <stdio.h>
#include <string.h>
#include "io.h"
#include "huffman.h"
#include "huffman_common.h"

/**
 * Hauptmethode des Programms
 * @return 0
 */
int main()
{
    // TODO
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

