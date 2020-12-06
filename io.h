/**
 * @file
 * Diese Modul stellt die Funktionen zum byte- sowie bitweisen Lesen und
 * Schreiben zur Verfügung.
 *
 * @author  Tim Ostermann
 * @date    2020-12-05
 */

#include <stdbool.h>
#include "huffman_common.h"

#ifndef HUFFMAN_IO_H
#define HUFFMAN_IO_H

#define BUF_SIZE 4096

extern void init_in(char text[]);

extern void init_out(void);

extern void get_out_buffer(char text[]);

extern bool has_next_char(void);

extern unsigned char read_char(void);

extern void write_char(unsigned char c);

extern bool has_next_bit(void);

extern BIT read_bit(void);

extern void write_bit(BIT c);

extern void print_out_char_array(unsigned char array[]);

#endif //HUFFMAN_IO_H
