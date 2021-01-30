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
 * Initialisiert Eingabepuffer.
 */
extern void init_in(void);

/**
 * Initialisiert Ausgabepuffer.
 * @param save_last_byte - Gibt an, ob letztes Byte als neues erstes behalten werden soll.
 */
extern void init_out(bool save_last_byte);

/**
 * Öffnet Eingabedatei.
 * @param in_filename - Name der Eingabedatei
 * @return Exit-Code
 */
extern EXIT open_infile(char in_filename[]);

/**
 * Öffnet Ausgabedatei.
 * @param out_filename - Name der Ausgabedatei
 * @return Exit-Code
 */
extern EXIT open_outfile(char out_filename[]);

/**
 * Schließt Eingabedatei.
 */
extern void close_infile(void);

/**
 * Schließt Ausgabedatei.
 */
extern void close_outfile(void);

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
 * Liefert den nächsten Integerwert aus dem Eingabepuffer.
 * @return den nächsten Integerwert
 */
extern unsigned int read_int(void);

/**
 * Schreibt Integerwert an die nächste freie Position im Ausgabepuffer.
 * @param i - zu schreibender Integerwert
 */
extern void write_int(unsigned int i);

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
