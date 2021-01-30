#include "huffman_code.h"
#include <stdlib.h>

/**
 * Implementierung des Eintrags der Huffman-Code-Tabelle.
 */
typedef struct _HUFFMAN_CODE
{
    /**
     * Zeichen des Huffman-Codes
     */
    unsigned char character;

    /**
     * Zeichenkette des Huffman-Codes.
     */
    char *code;
} HUFFMAN_CODE;

extern HUFFMAN_CODE *huffman_code_create(unsigned char character, char *code)
{
    HUFFMAN_CODE *huff_code = (HUFFMAN_CODE *) malloc(sizeof(HUFFMAN_CODE *));
    huff_code->code = code;
    huff_code->character = character;
    return huff_code;
}

extern void huffman_code_destroy(HUFFMAN_CODE *huffman_code)
{
    free(huffman_code);
    huffman_code = NULL;
}

extern unsigned char huffman_code_get_character(HUFFMAN_CODE *huffman_code)
{
    if (huffman_code != NULL)
    {
        return huffman_code->character;
    }
    else
    {
        return '\0';
    }
}

extern char *huffman_code_get_code(HUFFMAN_CODE *huffman_code)
{
    if (huffman_code != NULL)
    {
        return huffman_code->code;
    }
    else
    {
        return NULL;
    }
}

extern void huffman_code_set_character(HUFFMAN_CODE *huffman_code, unsigned char character)
{
    if (huffman_code != NULL)
    {
        huffman_code->character = character;
    }
}

extern void huffman_code_set_code(HUFFMAN_CODE *huffman_code, char *code)
{
    if (huffman_code != NULL)
    {
        huffman_code->code = code;
    }
}