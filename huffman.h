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

#include "huffman_common.h"

/**
 * Implementierung der Huffman-Komprimierung.
 * @param in_filename - Name der Eingabedatei
 * @param out_filename - Name der Ausgabedatei
 * @return Exit-Code
 */
extern EXIT compress(char *in_filename, char *out_filename);

/**
 * Implementierung der Huffman-Dekomprimierung.
 * @param in_filename - Name der Eingabedatei
 * @param out_filename - Name der Ausgabedatei
 * @return Exit-Code
 */
extern EXIT decompress(char *in_filename, char *out_filename);

#endif //HUFFMAN_HUFFMAN_H