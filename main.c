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
#include "arguments.h"

// TODO filenames als Pointer

/**
 * Hauptmethode des Programms
 * @param argv - Eingabeparameter
 * @param argc - Anzahl Eingabeparameter
 * @return Exit-Code
 */
int main(int argc, char *argv[])
{
    // variables for legal arguments
    OPERATION_MODE operation_mode = NONE;
    bool should_view_info = false;
    bool should_view_help = false;
    int level = 2;
    char out_filename[MAX_LENGTH_FILENAME] = {'\0'};
    char in_filename[MAX_LENGTH_FILENAME]= {'\0'};

    start_clock();

    EXIT exit = read_arguments(argv, argc, &operation_mode, &should_view_info, &should_view_help, &level, out_filename, in_filename);

    if (should_view_help)
    {
        print_help();
    }

    if (operation_mode == COMPRESSION && exit == SUCCESS)
    {
        exit = compress(in_filename, out_filename);
    }
    else if (operation_mode == DECOMPRESSION && exit == SUCCESS)
    {
        exit = decompress(in_filename, out_filename);
    }

    if (should_view_info && exit == SUCCESS)
    {
        print_further_information(in_filename, out_filename);
    }

    return exit;
}