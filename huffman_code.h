#ifndef HUFFMAN_HUFFMAN_CODE_H
#define HUFFMAN_HUFFMAN_CODE_H

/**
 * Repräsentation eines Eintrags der Huffman-Code-Tabelle
 */
typedef struct _HUFFMAN_CODE HUFFMAN_CODE;

/**
 * Erzeugt eine Instanz vom Typ Huffman-Code.
 * @param character - Zeichen des Codes
 * @param code - Zeichenkette des Codes
 * @return Adresse des erzeugten Huffman-Codes
 */
extern HUFFMAN_CODE *huffman_code_create(unsigned char character, char *code);

/**
 * Löscht übergebenen Huffman-Code.
 * @param huffman_code - zu löschender Huffman-Code
 */
extern void huffman_code_destroy(HUFFMAN_CODE *huffman_code);

/**
 * Liefert Zeichen eines Huffman-Codes.
 * @param huffman_code - Huffman-Code, dessen Zeichen geliefert werden soll
 * @return Zeichen des Huffman-Codes
 */
extern unsigned char huffman_code_get_character(HUFFMAN_CODE *huffman_code);

/**
 * Liefert Zeichenkette eines Huffman-Codes.
 * @param huffman_code - Huffman-Code, dessen Zeichenkette geliefert werden soll
 * @return Zeichenkette des Huffman-Codes
 */
extern char *huffman_code_get_code(HUFFMAN_CODE *huffman_code);

/**
 * Setzt Zeichen eines Huffman-Codes.
 * @param huffman_code - Huffman-Code, dessen Zeichen gesetzt werden soll
 * @param character - zu setzendes Zeichen
 */
extern void huffman_code_set_character(HUFFMAN_CODE *huffman_code, unsigned char character);

/**
 * Setzt Zeichenkette eines Huffman-Codes.
 * @param huffman_code - Huffman-Code, dessen Zeichenkette gesetzt werden soll
 * @param code - zu setzende Zeichenkette
 */
extern void huffman_code_set_code(HUFFMAN_CODE *huffman_code, char *code);

#endif //HUFFMAN_HUFFMAN_CODE_H
