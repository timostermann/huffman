/**
 * @file
 * Dieses Modul beinhaltet allgemeine Definitionen.
 *
 * @author  Tim Ostermann
 * @date    2020-12-05
 */

#ifndef HUFFMAN_HUFFMAN_COMMON_H
#define HUFFMAN_HUFFMAN_COMMON_H

#include <stdbool.h>

/**
 * Repräsentation Bitzustände
 */
typedef enum
{
    BIT0 = 0,
    BIT1 = 1
} BIT;

/**
 * Exit-Codes
 */
typedef enum
{
    SUCCESS = 0,
    UNKNOWN_EXCEPTION = 1,
    ARGUMENTS_EXCEPTION = 2,
    IO_EXCEPTION = 3,
    COMPRESSION_EXCEPTION = 4
} EXIT;

/**
 * Gibt an, ob System im Debug-Modus läuft
 */
#define DEBUG false

/**
 * Maximale Länge des Filenamen
 */
#define MAX_LENGTH_FILENAME 2000

/**
 * Anzahl Elemente, die reserviert/gelöscht werden
 */
#define NUM_OF_ELEMENTS 10

/**
 * Debug-Ausgabe von Ausdrücken, die eine ganze Zahl liefern
 */
#define DPRINT(P) if(DEBUG) printf(#P " = %d\n", P)

/**
 * Debug-Ausgabe von Ausdrücken, die eine Zeichenkette liefern
 */
#define SPRINT(P) if(DEBUG) printf(#P " = \"%s\"\n", P)

/**
 * Debug-Ausgabe von Ausdrücken, die ein Zeichen liefern
 */
#define CPRINT(P) if(DEBUG) printf(#P " = %c\n", P)

/**
 * Debug-Ausgabe von Ausdrücken, die eine ganze Zahl liefern
 * (hexadezimale Ausgabe)
 */
#define XPRINT(P) if(DEBUG) printf(#P " = %x\n", P)

/**
 * Debug-Ausgabe von Ausdrücken, die eine Gleitkommazahl liefern (float)
 */
#define FPRINT(P) if(DEBUG) printf(#P " = %f\n", P)

/**
 * Debug-Ausgabe von Ausdrücken, die eine Gleitkommazahl liefern (double)
 */
#define LFPRINT(P) if(DEBUG) printf(#P "= %lf\n", P)


#endif //HUFFMAN_HUFFMAN_COMMON_H
