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
#include <assert.h>
#include "io.h"
#include "huffman.h"
#include "huffman_common.h"

void print_dauer(unsigned long kombinationen);

/**
 * Hauptmethode des Programms
 * @return 0
 */
int main()
{
    //TODO: Fehler im Bit-Lesen und/oder Schreiben

    // read chars write bits alphabet in order
    char in_alph_ord[] = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxX";
    char out_alph_ord[50] = {0};
    test_rd_chars_wr_bits(in_alph_ord, out_alph_ord);
    print_out_char_array(in_alph_ord);
    print_out_char_array(out_alph_ord);
    printf("\n");
//    assert(strcmp(out_alph_ord, "UUUUUU") == 0);

    // read chars write bits alphabet in order
    char in_alph[] = "abCdefGHijKlmnOPqrStuvWXyzAbcdEF";
    char out_alph[50] = {0};
    test_rd_chars_wr_bits(in_alph, out_alph);
    print_out_char_array(in_alph);
    print_out_char_array(out_alph);
    printf("\n");
//    assert(strcmp(out_alph, "####") == 0);

    // read bits write chars numbers in order
    char in_num_ord[] = "1234567890";
    char out_num_ord[100] = {0};
    test_rd_bits_wr_chars(in_num_ord, out_num_ord);
    print_out_char_array(in_num_ord);
    print_out_char_array(out_num_ord);
    printf("\n");
//    assert(strcmp(out_num_ord, "00110001001100100011001100110100001101010011011000110111001110000011100100110000") == 0);

    // read bits write chars numbers out of order
    char in_num[] = "0192837465";
    char out_num[100] = {0};
    test_rd_bits_wr_chars(in_num, out_num);
    print_out_char_array(in_num);
    print_out_char_array(out_num);
    printf("\n");
//    assert(strcmp(out_num_ord, "00110000001100010011100100110010001110000011001100110111001101000011011000110101") == 0);

    printf("\n%d", 'b' < 'a');
    return 0;
}

