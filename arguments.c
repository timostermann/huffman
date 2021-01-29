#include "arguments.h"
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

/**
 * Variable zum Festhalten der Startzeit des Programms.
 */
static clock_t prg_start;

extern EXIT read_arguments(char *argv[], int argc, OPERATION_MODE *operation_mode, bool *should_view_info, bool *should_view_help, int *level, char *out_filename, char *in_filename)
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
        || argc - 2 == argument_index_o
        || strlen(argv[argc - 1]) > MAX_LENGTH_FILENAME)
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

extern int search_for_argument(char *argv[], int argc, char *arg)
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

extern int check_number_of_arguments(int argument_index_c, int argument_index_d, int argument_index_l, int argument_index_h, int argument_index_v, int argument_index_o)
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

extern void print_help(void)
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
           " <filename>\tName der Eingabedatei.\n\n");
}

extern void start_clock(void)
{
    prg_start = clock();
}

extern void print_further_information(char *in_filename, char *out_filename)
{
    struct stat attribut;
    stat(in_filename, &attribut);
    printf(" - Größe der Eingabedatei %s (byte): %d\n",
           in_filename, (int) attribut.st_size);

    stat(out_filename, &attribut);
    printf(" - Größe der Ausgabedatei %s (byte): %d\n",
           out_filename, (int) attribut.st_size);
    clock_t prg_end = clock();
    printf(" - Die Laufzeit betrug %.4f Sekunden\n",
           (float) (prg_end - prg_start) / CLOCKS_PER_SEC);
}