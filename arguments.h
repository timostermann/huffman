#include "huffman_common.h"

#ifndef HUFFMAN_ARGUMENTS_H
#define HUFFMAN_ARGUMENTS_H

/**
 * Ausführungsmodi
 */
typedef enum
{
    NONE = -1,
    HELP = 0,
    COMPRESSION = 1,
    DECOMPRESSION = 2
} OPERATION_MODE;

/**
 * Liest Eingabeparameter des Konsolenaufrufs aus.
 * @param argv - Eingabeparameter
 * @param argc - Anzahl Eingabeparameter
 * @param operation_mode - Zeiger auf Ausführungsmodus
 * @param print_info - Zeiger auf Wahrheitswert, der Angabe weiterer Informationen repräsentiert
 * @param should_view_help - Zeiger auf Wahrheitswert, der Angabe von Programmhilfe repräsentiert
 * @param level - Zeiger auf Komprimierungslevel
 * @param out_filename - Zeiger auf Ausgabedatei
 * @param in_filename - Zeiger auf Eingabedatei
 * @return entsprechender Exit-Code
 */
extern EXIT read_arguments(char *argv[], int argc, OPERATION_MODE *operation_mode, bool *print_info, bool *should_view_help, int *level, char *out_filename, char *in_filename);

/**
 * Sucht nach bestimmten Parameter in den Eingabeparametern.
 * @param argv - Eingabeparameter
 * @param argc - Anzahl Eingabeparameter
 * @param arg - gesuchter Parameter
 * @return Index des Parameters, -1 wenn nicht gefunden
 */
extern int search_for_argument(char *argv[], int argc, char *arg);

/**
 * Bestimmt Anzahl der vorkommenden legalen Eingabeparameter.
 * @param argument_index_c - Index des "-c"-Parameters
 * @param argument_index_d - Index des "-d"-Parameters
 * @param argument_index_l - Index des "-l"-Parameters
 * @param argument_index_h - Index des "-h"-Parameters
 * @param argument_index_v - Index des "-v"-Parameters
 * @param argument_index_o - Index des "-o"-Parameters
 * @return Anzahl der legalen Eingabeparameter
 */
extern int check_number_of_arguments(int argument_index_c, int argument_index_d, int argument_index_l, int argument_index_h, int argument_index_v, int argument_index_o);

/**
 * Gibt Programmhilfe aus.
 */
extern void print_help(void);

/**
 * Startet Zeitmessung des Programmes.
 */
extern void start_clock(void);

/**
 * Gibt weitere Informationen zur Programmdurchführung aus.
 * @param in_filename - Name der Eingabedatei
 * @param out_filename - Name der Ausgabedatei
 */
extern void print_further_information(char *in_filename, char *out_filename);


#endif //HUFFMAN_ARGUMENTS_H
