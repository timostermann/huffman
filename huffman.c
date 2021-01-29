#include "huffman.h"
#include "huffman_common.h"
#include "io.h"
#include "frequency.h"
#include "btree.h"
#include "btreenode.h"
#include "binary_heap.h"
#include "huffman_code.h"
#include <string.h>
#include <stdio.h>

/**
 * Zeichen, um das der Huffman-Code erweitert wird, wenn man in der Baumstruktur "nach links" geht.
 */
#define LEFT_SIGN "1"

/**
 * Zeichen, um das der Huffman-Code erweitert wird, wenn man in der Baumstruktur "nach rechts" geht.
 */
#define RIGHT_SIGN "0"

/**
 * Frequencies der gelesenen Datei
 */
static FREQUENCY **frequencies;

/**
 * Huffman-Code-Tabelle
 */
static HUFFMAN_CODE **huffman_code_table;

/**
 * Optimaler Binärbaum
 */
static BTREE *optimal_tree;

/**
 * Größe der Huffman-Code-Tabelle
 */
static unsigned int huff_size;

/**
 * Füllstand der Huffman-Code-Tabelle
 */
static unsigned int huff_filling_level;

/**
 * Größe der Frequencies
 */
static unsigned int freq_size;

/**
 * Füllstand der Frequencies
 */
static unsigned int freq_filling_level;

/**
 * Bestimmt die Huffman-Code-Tabelle.
 * @param node - Knoten des Binärbaumes
 * @param code - Huffman-Code
 */
static void get_code_table(BTREE_NODE *node, char *code);

/**
 * Liefert Index des Eintrags der Huffman-Code-Tabelle, dessen Zeichenkette dem Parameter-Code entspricht.
 * @param code - Zeichenkette der gesuchten Huffman-Code-Tabelle
 * @return -1 falls Huffman-Code-Tabelle keinen entsprechenden Eintrag hat, sonst den Index.
 */
static int get_code_table_index_by_code(char *code);

/**
 * Liefert Index des Eintrags der Huffman-Code-Tabelle, dessen Zeichen dem Parameter-Zeichen entspricht.
 * @param code - Zeichenkette der gesuchten Huffman-Code-Tabelle
 * @return -1 falls Huffman-Code-Tabelle keinen entsprechenden Eintrag hat, sonst den Index.
 */
static char *get_huffman_code_by_char(unsigned char next_char);

/**
 * Liefert Index der Frequencies, dessen Zeichen dem Parameter-Zeichen entspricht.
 * @param pp_frequency - Frequencies
 * @param next_char - Zeichen der gesuchten Frequencies
 * @return -1 falls Frequencies keinen entsprechenden Eintrag hat, sonst den Index.
 */
static int get_frequency_index_by_char(FREQUENCY **pp_frequency, unsigned char next_char);

/**
 * Vergleicht zwei Binärbäume anhand der Häufigkeit in ihrer Wurzel.
 * Es wird vorausgesetzt, dass der Wert der Wurzel des Baumes vom Typ FREQUENCY ist.
 * @param btree1 - erster zu vergleichender Binärbaum
 * @param btree2 - zweiter zu vergleichender Binärbaum
 * @return -1, wenn der der erste Baum eine geringere Häufigkeit in der Wurzel hat, sonst 1
 */
static int compare_btrees_by_frequency(BTREE *btree1, BTREE *btree2);

extern EXIT compress(char *in_filename, char *out_filename)
{
    freq_size = NUM_OF_ELEMENTS;
    frequencies = (FREQUENCY **) malloc((sizeof(FREQUENCY *) * (size_t) freq_size));
    huffman_code_table = (HUFFMAN_CODE **) malloc(sizeof(HUFFMAN_CODE *) * (size_t) NUM_OF_ELEMENTS);
    freq_filling_level = 0;

    if (open_infile(in_filename) != SUCCESS || open_outfile(out_filename) != SUCCESS)
    {
        return IO_EXCEPTION;
    }

    int index = -1;
    // get and store frequencies
    while (has_next_char())
    {
        unsigned char next_char = read_char();
        if (freq_filling_level != 0)
        {
            index = get_frequency_index_by_char(frequencies, next_char);
        }

        if (index != -1)
        {
            frequency_set_count((*(frequencies + index)),
                                frequency_get_count(*(frequencies + index)) + 1);
        }
        else
        {
            if (freq_filling_level == freq_size)
            {
                freq_size += NUM_OF_ELEMENTS;
                frequencies = (FREQUENCY **) realloc(frequencies, (size_t) (sizeof(FREQUENCY *) *freq_size));
            }

            *(frequencies + freq_filling_level) = frequency_create(next_char, 1);
            freq_filling_level++;
        }
    }

    // build optimal tree with heap
    heap_init((HEAP_ELEM_COMP) compare_btrees_by_frequency, (HEAP_ELEM_PRINT) btree_print);

    // fill heap with btrees of found frequencies
    for (int i = 0; i < freq_filling_level; i++)
    {
        heap_insert(btree_new(*(frequencies + i), (DESTROY_DATA_FCT) frequency_destroy, (PRINT_DATA_FCT) frequency_print));
    }

    // write number of frequencies
    write_int(freq_filling_level);

    // write frequencies
    for (int j = 0; j < freq_filling_level; j++)
    {
        write_char((*(frequencies + j))->word);
        write_int((*(frequencies + j))->count);
    }

    BTREE *min_element1 = NULL;
    BTREE *min_element2 = NULL;
    while (heap_extract_min((void **)&min_element1) && heap_extract_min((void **)&min_element2))
    {
        // merge minimal trees and insert merged tree back in the heap
        heap_insert(btree_merge(min_element1, min_element2,
                    frequency_create('\0',
                            ((FREQUENCY *)(btreenode_get_data(btree_get_root(min_element1))))->count
                            + ((FREQUENCY *)(btreenode_get_data(btree_get_root(min_element2))))->count)));
    }
    optimal_tree = min_element1;

    // fill code table with codes
    huff_filling_level = 0;
    huff_size = NUM_OF_ELEMENTS;
    get_code_table(btree_get_root(optimal_tree), malloc(sizeof(char) * (size_t) NUM_OF_ELEMENTS));

    // read infile and write huffman-codes as bits
    close_infile();
    open_infile(in_filename);

    while (has_next_char())
    {
        unsigned char next_char = read_char();
        char *next_code = get_huffman_code_by_char(next_char);

        // write bits in code
        // TODO fix
        for (int i = 0; i < strlen(next_code); i++)
        {
            if (next_code[i] == '1')
            {
                write_bit(BIT1);
            }
            else
            {
                write_bit(BIT0);
            }
        }
    }

    close_infile();
    close_outfile();

    return SUCCESS;
}

extern EXIT decompress(char *in_filename, char *out_filename)
{
    huffman_code_table = (HUFFMAN_CODE **) malloc(sizeof(HUFFMAN_CODE *) * (size_t) NUM_OF_ELEMENTS);
    unsigned int char_count = 0;

    if (open_infile(in_filename) != SUCCESS || open_outfile(out_filename) != SUCCESS)
    {
        return IO_EXCEPTION;
    }

    // read frequencies and insert in heap
    heap_init((HEAP_ELEM_COMP) compare_btrees_by_frequency, (HEAP_ELEM_PRINT) btree_print);
    freq_size = read_int();
    frequencies = (FREQUENCY **) malloc((size_t) (sizeof(FREQUENCY *) * (size_t) freq_size));

    for (int i = 0; i < freq_size; i++)
    {
        unsigned char character = read_char();
        unsigned int count = read_int();
        char_count += count;
        *(frequencies + i) = frequency_create(character, count);
        heap_insert(btree_new(*(frequencies + i), (DESTROY_DATA_FCT) frequency_destroy, (PRINT_DATA_FCT) frequency_print));
    }

    BTREE *min_element1 = NULL;
    BTREE *min_element2 = NULL;
    while (heap_extract_min((void **)&min_element1) && heap_extract_min((void **)&min_element2))
    {
        // merge minimal trees and insert merged tree back in the heap
        heap_insert(btree_merge(min_element1, min_element2,
                                frequency_create('\0',
                                                 ((FREQUENCY *)(btreenode_get_data(btree_get_root(min_element1))))->count
                                                 + ((FREQUENCY *)(btreenode_get_data(btree_get_root(min_element2))))->count)));
    }

    optimal_tree = min_element1;
    // fill code table with codes
    huff_filling_level = 0;
    huff_size = NUM_OF_ELEMENTS;
    get_code_table(btree_get_root(optimal_tree), malloc(sizeof(char) * (size_t) NUM_OF_ELEMENTS));

    char *code = malloc(sizeof(char) * NUM_OF_ELEMENTS);
    int code_size = NUM_OF_ELEMENTS;
    int index;
    // TODO fix
    while (has_next_bit())
    {
        BIT next_bit = read_bit();

        if (strlen(code) == code_size)
        {
            code_size += NUM_OF_ELEMENTS;
            code = realloc(code, sizeof(char) * (size_t) code_size);
        }

        if (next_bit == BIT0)
        {
            code = strncat(code, "0", 1);
        }
        else
        {
            code = strncat(code, "1", 1);
        }

        index = get_code_table_index_by_code(code);
        if (index != -1 && char_count > 0)
        {
            char_count--;
            write_char(huffman_code_get_character(*(huffman_code_table + index)));
            memset(code, 0, strlen(code));
            code = realloc(code, sizeof(char) * (size_t) NUM_OF_ELEMENTS);
            code_size = NUM_OF_ELEMENTS;
        }
    }

    close_infile();
    close_outfile();

    return SUCCESS;
}

static void get_code_table(BTREE_NODE *node, char *code)
{
    if (node == NULL)
    {
        return;
    }

    if (!btreenode_is_leaf(node))
    {
        // proceed with left node
        if (btreenode_get_left(node) != NULL)
        {
            char *new_code = malloc(((int) sizeof(char) * ((int) strlen(code) + 1)));
            memset(new_code, 0, (int) strlen(code) + 1);
            strncpy(new_code, code, strlen(code));
            strncat(new_code, LEFT_SIGN, 1);
            get_code_table(btreenode_get_left(node), new_code);
        }
        // proceed with right node
        if (btreenode_get_right(node) != NULL)
        {
            char *new_code = malloc(sizeof(char) * ((int) strlen(code) + 1));
            memset(new_code, 0, (int) strlen(code) + 1);
            strncpy(new_code, code, strlen(code));
            strncat(new_code, RIGHT_SIGN, 1);
            get_code_table(btreenode_get_right(node), new_code);
        }
    }
    else
    {
        if (huff_filling_level == huff_size)
        {
            huff_size += NUM_OF_ELEMENTS;
            huffman_code_table = (HUFFMAN_CODE **) realloc(huffman_code_table, sizeof(HUFFMAN_CODE *) * huff_size);
        }
        if (strlen(code) == 0)
        {
            code = "0";
        }
        // fill table with code
        if (((FREQUENCY *)btreenode_get_data(node))->word == '2')
        {
            printf("test");
        }

        printf("[%c -> %s]\n", ((FREQUENCY *)btreenode_get_data(node))->word, code);
        *(huffman_code_table + huff_filling_level) = huffman_code_create(((FREQUENCY *)btreenode_get_data(node))->word, code);
        huff_filling_level++;
    }

}

static int get_code_table_index_by_code(char *code)
{
    for (int i = 0; i < huff_filling_level; i++)
    {
        if (strlen(code) == strlen(huffman_code_get_code(*(huffman_code_table + i)))
            && strncmp(huffman_code_get_code(*(huffman_code_table + i)), code, strlen(code)) == 0)
        {
            return i;
        }
    }
    return -1;
}

static char *get_huffman_code_by_char(unsigned char next_char)
{
    for (int i = 0; i < huff_filling_level; i++)
    {
        if (huffman_code_get_character(huffman_code_table[i]) == next_char)
        {
            return huffman_code_get_code(huffman_code_table[i]);
        }
    }
    return "";
}

static int get_frequency_index_by_char(FREQUENCY **pp_frequency, unsigned char next_char)
{
    if (pp_frequency != NULL)
    {
        for (int i = 0; i < freq_filling_level && *(pp_frequency + i) != NULL; i++)
        {
            if (frequency_get_word(*(pp_frequency + i)) == next_char)
            {
                return i;
            }
        }
    }

    return -1;
}

static int compare_btrees_by_frequency(BTREE *btree1, BTREE *btree2)
{
    return ((FREQUENCY *) btreenode_get_data(btree_get_root(btree1)))->count < ((FREQUENCY *)btreenode_get_data(btree_get_root(btree2)))->count
        ? -1
        : 1;
}