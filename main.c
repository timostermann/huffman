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

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "io.h"
#include "huffman.h"
#include "huffman_common.h"

EXIT read_arguments(char *argv[], int argc, bool *compress, bool *print_info, bool *help, int *level, char *outfile, char *infile);

int search_for_argument(char *argv[], int argc, char *arg);

int check_number_of_arguments(int argument_index_c, int argument_index_d, int argument_index_l, int argument_index_h, int argument_index_v, int argument_index_o);

/**
 * Hauptmethode des Programms
 * @return Exit-Code
 */
int main(int argc, char *argv[])
{
    bool compress = NULL;
    bool print_info = false;
    bool help = false;
    int level = 2;
    char outfile[MAX_LENGTH_FILENAME] = {'\0'};
    char infile[MAX_LENGTH_FILENAME]= {'\0'};

    EXIT exit = read_arguments(argv, argc, &compress, &print_info, &help, &level, &outfile, &infile);

    // read chars write bits alphabet in order
//    char in_alph_ord[] = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxX";
//    char out_alph_ord[50] = {0};
//    test_rd_chars_wr_bits(in_alph_ord, out_alph_ord);
//    SPRINT(in_alph_ord);
//    SPRINT(out_alph_ord);
//    printf("\n");
//    assert(strcmp(out_alph_ord, "UUUUUU") == 0);
//
//    // read chars write bits alphabet in order
//    char in_alph[] = "abCdefGHijKlmnOPqrStuvWXyzAbcdEF";
//    char out_alph[50] = {0};
//    test_rd_chars_wr_bits(in_alph, out_alph);
//    SPRINT(in_alph);
//    SPRINT(out_alph);
//    printf("\n");
//    assert(strcmp(out_alph, "####") == 0);
//
//    // read bits write chars numbers in order
//    char in_num_ord[] = "1234567890";
//    char out_num_ord[100] = {0};
//    test_rd_bits_wr_chars(in_num_ord, out_num_ord);
//    SPRINT(in_num_ord);
//    SPRINT(out_num_ord);
//    printf("\n");
//    assert(strcmp(out_num_ord, "00110001001100100011001100110100001101010011011000110111001110000011100100110000") == 0);
//
//    // read bits write chars numbers out of order
//    char in_num[] = "0192837465";
//    char out_num[100] = {0};
//    test_rd_bits_wr_chars(in_num, out_num);
//    SPRINT(in_num);
//    SPRINT(out_num);
//    printf("\n");
//    assert(strcmp(out_num, "00110000001100010011100100110010001110000011001100110111001101000011011000110101") == 0);
//    return 0;

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

    // Bestimme, komprimiert oder dekomprimiert werden soll
    if (argument_index_c == -1 && argument_index_d == -1)
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
    else
    {
        *compress = false;
    }

    // Bestimme, ob Informationen zur (De-)komprimierung angezeigt werden sollen
    if (argument_index_v != -1)
    {
        *print_info = true;
    }
    else
    {
        *print_info = false;
    }

    // Bestimme, ob Hilfe zum Programm angegeben werden soll
    if (argument_index_h != -1)
    {
        *help = true;
    }
    else
    {
        *help = false;
    }

    // Bestimme Level der Komprimierung
    if (argument_index_d == -1 && argument_index_l != -1)
    {
        if (strlen(argv[argument_index_l]) == 3)
        {
            *level = (int) argv[argument_index_l][2];
        }
        else
        {
           return ARGUMENTS_EXCEPTION;
        }
    }

    // Bestimme Name der Ausgabedatei
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

    // Bestimme Name der Eingabedatei
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