/**
 * @mainpage huffman
 *
 * Dieses Projekt realisiert die Huffman-Kodierung.
 *
 * @author  Tim Ostermann
 * @date    2020-12-05
 */

/**
 * @file
 *
 * @author  Tim Ostermann
 * @date    2020-12-05
 */

#include "io.h"
#include "huffman.h"
#include "huffman_common.h"

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>

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
static EXIT read_arguments(char *argv[], int argc, OPERATION_MODE *operation_mode, bool *print_info, bool *should_view_help, int *level, char *out_filename, char *in_filename);

/**
 * Sucht nach bestimmten Parameter in den Eingabeparametern.
 * @param argv - Eingabeparameter
 * @param argc - Anzahl Eingabeparameter
 * @param arg - gesuchter Parameter
 * @return Index des Parameters, -1 wenn nicht gefunden
 */
static int search_for_argument(char *argv[], int argc, char *arg);

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
static int check_number_of_arguments(int argument_index_c, int argument_index_d, int argument_index_l, int argument_index_h, int argument_index_v, int argument_index_o);

/**
 * Hauptmethode des Programms
 * @param argv - Eingabeparameter
 * @param argc - Anzahl Eingabeparameter
 * @return Exit-Code
 */
int main(int argc, char *argv[])
{
    // time-taking variables
    clock_t prg_start = clock();
    clock_t prg_end;

    // variables for legal arguments
    OPERATION_MODE operation_mode = NONE;
    bool should_view_info = false;
    bool should_view_help = false;
    int level = 2;
    char out_filename[MAX_LENGTH_FILENAME] = {'\0'};
    char in_filename[MAX_LENGTH_FILENAME]= {'\0'};

    EXIT exit = read_arguments(argv, argc, &operation_mode, &should_view_info, &should_view_help, &level, out_filename, in_filename);

    if (should_view_help)
    {
        // print help
        printf("Programmhilfe Huffman:\n"
               "Aufruf: huffman <options> <filename>\n"
               " -c\tDie Eingabedatei wird komprimiert.\n"
               " -d\tDie Eingabedatei wird dekomprimiert.\n"
               " \tSind im Aufruf beide Optionen -c und -d angegeben, bestimmt die letzte Angabe, ob komprimiert oder dekomprimiert wird.\n"
               " -l<level>\tLegt den Level der Komprimierung fest. Der Wert für den Level folgt ohne Leerzeichen auf die Option -l und muss zwischen 1 und 9 liegen. Fehlt die Option, wird der Level standardmäßig auf 2 eingestellt. Der Parameter wird ignoriert, wenn die Option -d angegeben wurde.\n"
               " -v\tGibt Informationen über die Komprimierung bzw. Dekomprimierung aus.\n"
               " -o <outfile>\tLegt den Namen der Ausgabedatei fest. Wird die Option weggelassen, wird der Name der Ausgabedatei standardmäßig festgelegt.\n"
               " -h\tZeigt eine Hilfe an, die die Benutzung des Programms erklärt.\n"
               " <filename>\tName der Eingabedatei.\n\n");
    }

    if (operation_mode == COMPRESSION && exit == SUCCESS)
    {
        exit = test_rd_chars_wr_bits(in_filename, out_filename);
    }
    else if (operation_mode == DECOMPRESSION && exit == SUCCESS)
    {
        exit = test_rd_bits_wr_chars(in_filename, out_filename);
    }

    if (should_view_info && exit == SUCCESS)
    {
        // view further information
        struct stat attribut;
        stat(in_filename, &attribut);
        printf(" - Größe der Eingabedatei %s (byte): %d\n",
               in_filename, (int) attribut.st_size);

        stat(out_filename, &attribut);
        printf(" - Größe der Ausgabedatei %s (byte): %d\n",
               out_filename, (int) attribut.st_size);
        prg_end = clock();
        printf(" - Die Laufzeit betrug %.4f Sekunden\n",
               (float) (prg_end - prg_start) / CLOCKS_PER_SEC);
    }

    return exit;
}

static EXIT read_arguments(char *argv[], int argc, OPERATION_MODE *operation_mode, bool *should_view_info, bool *should_view_help, int *level, char *out_filename, char *in_filename)
{
    // indices of legal arguments
    int argument_index_c = search_for_argument(argv, argc, "-c");
    int argument_index_d = search_for_argument(argv, argc, "-d");
    int argument_index_v = search_for_argument(argv, argc, "-v");
    int argument_index_h = search_for_argument(argv, argc, "-h");
    int argument_index_l = search_for_argument(argv, argc, "-l");
    int argument_index_o = search_for_argument(argv, argc, "-o");

    // determine, if program help shall be viewed
    if (argument_index_h != -1)
    {
        *should_view_help = true;
    }
    else
    {
        *should_view_help = false;
    }

    // get operation mode
    if (argument_index_c == -1 && argument_index_d == -1 && !*should_view_help)
    {
        return ARGUMENTS_EXCEPTION;
    }
    else if (argument_index_c != -1 && argument_index_d != -1)
    {
        if (argument_index_c > argument_index_d)
        {
            *operation_mode = COMPRESSION;
        }
        else
        {
            *operation_mode = DECOMPRESSION;
        }
    }
    else if (argument_index_c != -1)
    {
        *operation_mode = COMPRESSION;
    }
    else if (argument_index_d != -1)
    {
        *operation_mode = DECOMPRESSION;
    }
    else
    {
        *operation_mode = HELP;
        return SUCCESS;
    }

    // determine, if further information of the (de-)compression shall be viewed
    if (argument_index_v != -1)
    {
        *should_view_info = true;
    }
    else
    {
        *should_view_info = false;
    }

    // determine level of compression
    if (*operation_mode == COMPRESSION && argument_index_l != -1)
    {
        if (strlen(argv[argument_index_l]) == 3)
        {
            *level = (int) (argv[argument_index_l][2] - '0');
            if (*level < 1 || *level > 9)
            {
                return ARGUMENTS_EXCEPTION;
            }
        }
        else
        {
           return ARGUMENTS_EXCEPTION;
        }
    }

    // determine name of infile
    if (argc < 2
        || argc - 1 == argument_index_c
        || argc - 1 == argument_index_d
        || argc - 1 == argument_index_h
        || argc - 1 == argument_index_l
        || argc - 1 == argument_index_v
        || argc - 1 == argument_index_o
        || argc - 2 == argument_index_o)
    {
        return ARGUMENTS_EXCEPTION;
    }
    else
    {
        strncpy(in_filename, argv[argc - 1], MAX_LENGTH_FILENAME);
    }

    // determine name of outfile
    if (argument_index_o != -1)
    {
        if (argument_index_o + 1 == argument_index_c
            || argument_index_o + 1 == argument_index_d
            || argument_index_o + 1 == argument_index_h
            || argument_index_o + 1 == argument_index_l
            || argument_index_o + 1 == argument_index_v
            || argument_index_o + 2 >= argc
            || strlen(argv[argument_index_o + 1]) > MAX_LENGTH_FILENAME - 4
            )
        {
            return ARGUMENTS_EXCEPTION;
        }
        strncpy(out_filename, argv[argument_index_o + 1], MAX_LENGTH_FILENAME - 4);
    }
    else
    {
        strncpy(out_filename, in_filename, MAX_LENGTH_FILENAME - 4);
        if (*operation_mode == COMPRESSION)
        {
            strncat(out_filename, ".hc", MAX_LENGTH_FILENAME);
        }
        else if (*operation_mode == DECOMPRESSION)
        {
            strncat(out_filename, ".hd", MAX_LENGTH_FILENAME);
        }
        else
        {
            return ARGUMENTS_EXCEPTION;
        }
    }

    if (strcmp(in_filename, out_filename) == 0)
    {
        return ARGUMENTS_EXCEPTION;
    }

    if (check_number_of_arguments(argument_index_c, argument_index_d, argument_index_l, argument_index_h, argument_index_v, argument_index_o) != argc)
    {
        return ARGUMENTS_EXCEPTION;
    }

    return SUCCESS;
}

static int search_for_argument(char *argv[], int argc, char *arg)
{
    int argument_index = -1;

    for (int i = 0; i < argc; i++)
    {
        if (strncmp(*(argv + i), arg, strlen(arg)) == 0)
        {
            argument_index = i;
        }
    }

    return argument_index;
}

static int check_number_of_arguments(int argument_index_c, int argument_index_d, int argument_index_l, int argument_index_h, int argument_index_v, int argument_index_o)
{
    // program name and filename already counted
    int arg_count = 2;

    if (argument_index_c != -1 && argument_index_d != -1)
    {
        arg_count += 2;
    }
    else
    {
        arg_count++;
    }

    if (argument_index_l != -1)
    {
        arg_count++;
    }

    if (argument_index_h != -1)
    {
        arg_count++;
    }

    if (argument_index_v != -1)
    {
        arg_count++;
    }

    if (argument_index_o != -1)
    {
        arg_count += 2;
    }

    return arg_count;
}