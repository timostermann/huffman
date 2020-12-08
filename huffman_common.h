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
 * Gibt an, ob System im Debug-Modus läuft
 */
 /* @unused@ */
static const bool DEBUG = true;

/**
 * Debug-Ausgabe von Ausdrücken, die eine ganze Zahl liefern
 */
#define DPRINT(P) if(DEBUG) printf(#P "= %d\n", P)

/**
 * Debug-Ausgabe von Ausdrücken, die eine Zeichenkette liefern
 */
#define SPRINT(P) if(DEBUG) printf(#P "= \"%s\"\n", P)

/**
 * Debug-Ausgabe von Ausdrücken, die ein Zeichen liefern
 */
#define CPRINT(P) if(DEBUG) printf(#P "= %c\n", P)

/**
 * Debug-Ausgabe von Ausdrücken, die eine ganze Zahl liefern
 * (hexadezimale Ausgabe)
 */
#define XPRINT(P) if(DEBUG) printf(#P "= %x\n", P)

/**
 * Debug-Ausgabe von Ausdrücken, die eine Gleitkommazahl liefern (float)
 */
#define FPRINT(P) if(DEBUG) printf(#P "= %f\n", P)

/**
 * Debug-Ausgabe von Ausdrücken, die eine Gleitkommazahl liefern (double)
 */
#define LFPRINT(P) if(DEBUG) printf(#P "= %lf\n", P)


#endif //HUFFMAN_HUFFMAN_COMMON_H
