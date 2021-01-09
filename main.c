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
 * Liest Eingabeparameter des Konsolenaufrufs aus.
 * @param argv - Eingabeparameter
 * @param argc - Anzahl Eingabeparameter
 * @param compress - Zeiger auf Komprimierungs-Wahrheitswert
 * @param print_info - Zeiger auf Wahrheitswert, der Angabe weiterer Informationen repräsentiert
 * @param help - Zeiger auf Wahrheitswert, der Angabe von Programmhilfe repräsentiert
 * @param level - Zeiger auf Komprimierungslevel
 * @param outfile - Zeiger auf Ausgabedatei
 * @param infile - Zeiger auf Eingabedatei
 * @return entsprechender Exit-Code
 */
EXIT read_arguments(char *argv[], int argc, bool *compress, bool *print_info, bool *help, int *level, char *outfile, char *infile);

/**
 * Sucht nach bestimmten Parameter in den Eingabeparametern.
 * @param argv - Eingabeparameter
 * @param argc - Anzahl Eingabeparameter
 * @param arg - gesuchter Parameter
 * @return Index des Parameters, -1 wenn nicht gefunden
 */
int search_for_argument(char *argv[], int argc, char *arg);

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
int check_number_of_arguments(int argument_index_c, int argument_index_d, int argument_index_l, int argument_index_h, int argument_index_v, int argument_index_o);

/**
 * Hauptmethode des Programms
 * @param argv - Eingabeparameter
 * @param argc - Anzahl Eingabeparameter
 * @return Exit-Code
 */
int main(int argc, char *argv[])
{
    clock_t prg_start;
    clock_t prg_end;
    prg_start = clock();

    bool compress = NULL;
    bool print_info = false;
    bool help = false;
    int level = 2;
    char outfile[MAX_LENGTH_FILENAME] = {'\0'};
    char infile[MAX_LENGTH_FILENAME]= {'\0'};

    EXIT exit = read_arguments(argv, argc, &compress, &print_info, &help, &level, &outfile, &infile);

    if (help)
    {
        printf("Programmhilfe Huffman:\n"
               "Aufruf: huffman <options> <filename>\n"
               " -c\tDie Eingabedatei wird komprimiert.\n"
               " -d\tDie Eingabedatei wird dekomprimiert.\n"
               " \tSind im Aufruf beide Optionen -c und -d angegeben, bestimmt die letzte Angabe, ob komprimiert oder dekomprimiert wird.\n"
               " -l<level>\tLegt den Level der Komprimierung fest. Der Wert für den Level folgt ohne Leerzeichen auf die Option -l und muss zwischen 1 und 9 liegen. Fehlt die Option, wird der Level standardmäßig auf 2 eingestellt. Der Parameter wird ignoriert, wenn die Option -d angegeben wurde.\n"
               " -v\tGibt Informationen über die Komprimierung bzw. Dekomprimierung aus.\n"
               " -o <outfile>\tLegt den Namen der Ausgabedatei fest. Wird die Option weggelassen, wird der Name der Ausgabedatei standardmäßig festgelegt.\n"
               " -h\tZeigt eine Hilfe an, die die Benutzung des Programms erklärt.\n"
               " <filename>\tName der Eingabedatei\n\n");
    }

    if (compress)
    {
        if (strcmp(outfile, infile) == 0)
        {
            strcat(outfile, ".hc");
        }
        test_rd_chars_wr_bits(infile, outfile);
    }
    else if (compress != NULL)
    {
        if (strcmp(outfile, infile) == 0)
        {
            strcat(outfile, ".hd");
        }
        test_rd_bits_wr_chars(infile, outfile);
    }

    if (print_info)
    {
        struct stat attribut;
        stat(infile, &attribut);
        printf(" - Größe der Eingabedatei %s (byte): %d\n",
               infile, attribut.st_size);

        stat(outfile, &attribut);
        printf(" - Größe der Ausgabedatei %s (byte): %d\n",
               outfile, attribut.st_size);
        prg_end = clock();
        printf(" - Die Laufzeit betrug %.4f Sekunden\n",
               (float) (prg_end - prg_start) / CLOCKS_PER_SEC);
    }

/*    // read chars write bits alphabet in order
    char in_alph_ord[] = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxX";
    char out_alph_ord[50] = {0};
    test_rd_chars_wr_bits(in_alph_ord, out_alph_ord);
    SPRINT(in_alph_ord);
    SPRINT(out_alph_ord);
    printf("\n");
    assert(strcmp(out_alph_ord, "UUUUUU") == 0);

    // read chars write bits alphabet in order
    char in_alph[] = "abCdefGHijKlmnOPqrStuvWXyzAbcdEF";
    char out_alph[50] = {0};
    test_rd_chars_wr_bits(in_alph, out_alph);
    SPRINT(in_alph);
    SPRINT(out_alph);
    printf("\n");
    assert(strcmp(out_alph, "####") == 0);

    // read bits write chars numbers in order
    char in_num_ord[] = "1234567890";
    char out_num_ord[100] = {0};
    test_rd_bits_wr_chars(in_num_ord, out_num_ord);
    SPRINT(in_num_ord);
    SPRINT(out_num_ord);
    printf("\n");
    assert(strcmp(out_num_ord, "00110001001100100011001100110100001101010011011000110111001110000011100100110000") == 0);

    // read bits write chars numbers out of order
    char in_num[] = "0192837465";
    char out_num[100] = {0};
    test_rd_bits_wr_chars(in_num, out_num);
    SPRINT(in_num);
    SPRINT(out_num);
    printf("\n");
    assert(strcmp(out_num, "00110000001100010011100100110010001110000011001100110111001101000011011000110101") == 0);
    return 0;
*/
    return exit;
}

EXIT read_arguments(char *argv[], int argc, bool *compress, bool *print_info, bool *help, int *level, char *outfile, char *infile)
{
    int argument_index_c = search_for_argument(argv, argc, "-c");
    int argument_index_d = search_for_argument(argv, argc, "-d");
    int argument_index_v = search_for_argument(argv, argc, "-v");
    int argument_index_h = search_for_argument(argv, argc, "-h");
    int argument_index_l = search_for_argument(argv, argc, "-l");
    int argument_index_o = search_for_argument(argv, argc, "-o");

    // determine, if program help shall be viewed
    if (argument_index_h != -1)
    {
        *help = true;
    }
    else
    {
        *help = false;
    }

    // get operation mode
    if (argument_index_c == -1 && argument_index_d == -1 && !*help)
    {
        return ARGUMENTS_EXCEPTION;
    }
    else if (argument_index_c != -1 && argument_index_d != -1)
    {
        if (argument_index_c > argument_index_d)
        {
            *compress = true;
        }
        else
        {
            *compress = false;
        }
    }
    else if (argument_index_c != -1)
    {
        *compress = true;
    }
    else if (argument_index_d != -1)
    {
        *compress = false;
    }
    else
    {
        return SUCCESS;
    }

    // determine, if further information of the (de-)compression shall be viewed
    if (argument_index_v != -1)
    {
        *print_info = true;
    }
    else
    {
        *print_info = false;
    }

    // determine level of compression
    if (argument_index_d == -1 && argument_index_l != -1)
    {
        if (strlen(argv[argument_index_l]) == 3)
        {
            *level = (int) (argv[argument_index_l][2] - '0');
        }
        else
        {
           return ARGUMENTS_EXCEPTION;
        }
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
            )
        {
            return ARGUMENTS_EXCEPTION;
        }
        strncpy(outfile, argv[argument_index_o + 1], strlen(argv[argument_index_o + 1]));
    }
    else
    {
        strncpy(outfile, infile, strlen(infile));
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
    strncpy(infile, argv[argc - 1], strlen(argv[argc - 1]));

    if (strcmp(infile, outfile) == 0)
    {
        return ARGUMENTS_EXCEPTION;
    }

    if (check_number_of_arguments(argument_index_c, argument_index_d, argument_index_l, argument_index_h, argument_index_v, argument_index_o) != argc)
    {
        return ARGUMENTS_EXCEPTION;
    }

    return SUCCESS;
}

int search_for_argument(char *argv[], int argc, char *arg)
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

int check_number_of_arguments(int argument_index_c, int argument_index_d, int argument_index_l, int argument_index_h, int argument_index_v, int argument_index_o)
{
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