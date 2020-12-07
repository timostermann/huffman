#include "io.h"
#include <stdio.h>

/**
 * liefert Bitwert an bestimmter Position in einem Byte
 * @param BYTE - zu untersuchendes Byte
 * @param POS - Position des Bits (0-7)
 */
#define GET_BIT(BYTE, POS) ((BYTE & (0x01 << POS)) > 0)

/**
* setzt Bitwert an bestimmter Position in einem Byte
* @param BYTE - zu veränderndes Byte
* @param BIT - zu setzendes Bit
* @param POS - Position des Bits (0-7)
*/
#define PUT_BIT(BYTE, BIT, POS) BIT == BIT0 ? (BYTE & ~(0x01 << POS)) : (BYTE | (0x01 << POS))

/**
 * Eingabepuffer
 */
static unsigned char in_buffer[BUF_SIZE];

/**
 * Leseposition Byte Eingabepuffer
 */
static unsigned int read_byte_position = 0;

/**
 * Füllstand Byte Eingabepuffer
 */
static unsigned int read_byte_filling_level = 0;

/**
 * Lesepostion Bit Eingabepuffer
 */
static unsigned short read_bit_position = 0;

/**
 * Füllstand Bit Eingabepuffer
 */
static unsigned short read_bit_filling_level = 0;

/**
 * Ausgabepuffer
 */
static unsigned char out_buffer[BUF_SIZE] = {0};

/**
 * Schreibposition Byte Ausgabepuffer
 */
static unsigned int write_byte_position = 0;

/**
 * Schreibposition Bit Ausgabepuffer
 */
static unsigned short write_bit_position = 0;

extern void init_in(char text[])
{
    // fill in_buffer with values of text
    unsigned int index = 0;
    while (text[index] != '\0') {
        in_buffer[index] = text[index];
        index++;
    }

    read_byte_position = 0;
    read_bit_position = 0;
    read_bit_filling_level = 7;
    // TODO: Konsistenz überprüfen
    read_byte_filling_level = index;
}

extern void init_out(void)
{
    write_byte_position = 0;
    write_bit_position = 0;
}

extern void get_out_buffer(char text[])
{
    // write values of out_buffer in text
    for (int i = 0; i < write_byte_position; i++)
    {
        text[i] = out_buffer[i];
    }
    text[write_byte_position] = '\0';
}

extern bool has_next_char(void)
{
    return read_byte_position < read_byte_filling_level;
}

extern unsigned char read_char(void)
{
    unsigned char next_char = in_buffer[read_byte_position];
    read_byte_position++;
    return next_char;
}

extern void write_char(unsigned char c)
{
    out_buffer[write_byte_position] = c;
    write_byte_position++;
}

extern bool has_next_bit(void)
{
    // TODO
    return has_next_char()
           && read_bit_position <= read_bit_filling_level;
}

extern BIT read_bit(void)
{
    BIT bit = GET_BIT(in_buffer[read_byte_position], read_bit_position);
    read_bit_position++;

    if (read_bit_position == 8)
    {
        read_bit_position = 0;
        read_byte_position++;
    }
    return bit;
}

extern void write_bit(BIT c)
{
    out_buffer[write_byte_position] = PUT_BIT(
            out_buffer[write_byte_position], c, write_bit_position);
    write_bit_position++;

    if (write_bit_position == 8)
    {
        write_bit_position = 0;
        write_byte_position++;
    }
}

extern void print_out_char_array(char array[])
{
    printf("\n");
    int i = 0;
    while (array[i] != '\0') {
        printf("%c ", array[i]);
        i++;
    }
}