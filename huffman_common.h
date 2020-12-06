/**
 * @file
 * Dieses Modul beihnaltet allgemeine Definitionen.
 *
 * @author  Tim Ostermann
 * @date    2020-12-05
 */

#ifndef HUFFMAN_HUFFMAN_COMMON_H
#define HUFFMAN_HUFFMAN_COMMON_H

/**
 * Repräsentation Bitzustände
 */
typedef enum
{
    BIT0 = 0,
    BIT1 = 1
} BIT;

/**
 * Debug-Ausgabe von Ausdrücken, die eine ganze Zahl liefern
 */
#define DPRINT(P) printf(#P "= %d\n", P)

/**
 * Debug-Ausgabe von Ausdrücken, die eine Zeichenkette liefern
 */
#define SPRINT(P) printf(#P "= \"%s\"\n", P)

/**
 * Debug-Ausgabe von Ausdrücken, die ein Zeichen liefern
 */
#define CPRINT(P) printf(#P "= %c\n", P)

/**
 * Debug-Ausgabe von Ausdrücken, die eine ganze Zahl liefern
 * (hexadezimale Ausgabe)
 */
#define XPRINT(P) printf(#P "= %x\n", P)

#endif //HUFFMAN_HUFFMAN_COMMON_H
