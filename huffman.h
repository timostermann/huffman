/**
 * @file
 *
 * Dieses Modul implementiert (momentan) Test-Methoden.
 *
 * @author  Tim Ostermann
 * @date    2020-12-05
 */

#ifndef HUFFMAN_HUFFMAN_H
#define HUFFMAN_HUFFMAN_H

/**
 * Testet Funktionalität der byte-basierten io-Funktionen.
 * @param in_filename - Eingabedatei
 * @param out_filename - Ausgabedatei
 */
extern void test_rd_chars_wr_bits(char in_filename[], char out_filename[]);

/**
 * Testet Funktionalität der bit-basierten io-Funktionen.
 * @param in_filename - Eingabedatei
 * @param out_filename - Ausgabedatei
 */
extern void test_rd_bits_wr_chars(char in_filename[], char out_filename[]);

#endif //HUFFMAN_HUFFMAN_H