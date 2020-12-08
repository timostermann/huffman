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

/**
 * Puffergröße
 */
#define BUF_SIZE 4096

/**
 * Initialisiert Eingabepuffer mit übergebenem Vektor.
 * @param text - Vektor
 */
extern void init_in(char text[]);

/**
 * Initialisiert Ausgabepuffer.
 */
extern void init_out(void);

/**
 * Schreibt Werte des Ausgabevektors in übergebenen Vektor.
 * @param text - Vektor, der mit den Werten des Ausgabepuffers gefüllt wird
 */
extern void get_out_buffer(char text[]);

/**
 * Gibt an, ob noch weitere Zeichen aus dem Eingabepuffer mit read_char()
 * gelesen werden können.
 * @return
 */
extern bool has_next_char(void);

/**
 * Liefert das nächste Zeichen aus dem Eingabepuffer.
 * Vorbedingung: has_next_char() liefert true.
 * @return das nächste Zeichen
 */
extern unsigned char read_char(void);

/**
 * Schreibt Zeichen an die nächste freie Position im Ausgabepuffer.
 * @param c - zu schreibendes Zeichen
 */
extern void write_char(unsigned char c);

/**
 * Gibt an, ob noch weitere Bits aus dem Eingabepuffer gelesen werden können.
 * @return Wahrheitswert
 */
extern bool has_next_bit(void);

/**
 * Liefert das nächste Bit aus dem Eingabepuffer.
 * @return ermittelter Bitwert
 */
extern BIT read_bit(void);

/**
 * Schreibt Bit an der nächsten freien Bit-Position in den Ausgabepuffer.
 * @param c - zu schreibendes Bit
 */
extern void write_bit(BIT c);

#endif //HUFFMAN_IO_H
