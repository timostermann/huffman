#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * liefert Bitwert an bestimmter Position in einem Byte
 * @param BYTE - zu untersuchendes Byte
 * @param POS - Position des Bits (0-7)
 */
#define GET_BIT(BYTE, POS) ((BYTE & (0x01 << (7 - POS))) > 0)

/**
* setzt Bitwert an bestimmter Position in einem Byte
* @param BYTE - zu veränderndes Byte
* @param BIT - zu setzendes Bit
* @param POS - Position des Bits (0-7)
*/
#define PUT_BIT(BYTE, BIT, POS) BIT == BIT0 ? (BYTE & ~(0x01 << (7 - POS))) : (BYTE | (0x01 << (7 - POS)))

/**
 * Liest einen Block aus Eingabedatei.
 * @return Anzahl eingelesener Werte
 */
static int read_infile(void);

/**
 * Schreibt einen Block in Ausgabedatei.
 */
static void write_outfile(void);

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
static unsigned int read_bit_position = 0;

/**
 * Füllstand Bit Eingabepuffer
 */
static unsigned int read_bit_filling_level = 0;

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
static unsigned int write_bit_position = 0;

/**
 * Eingabestream
 */
static FILE *p_infile;

/**
 * Ausgabestream
 */
static FILE *p_outfile;

static bool end_of_infile;

/**
 * Union, mit deren Hilfe man auf die einzelnen Bytes eines Integerwertes zugreifen kann.
 */
typedef union
{
    /**
     * Wert als Integer
     */
    unsigned int i;

    /**
     * Wert als Char-Array
     */
    unsigned char c[4];
} CHARS_IN_INT;

extern void init_in(void)
{
    read_byte_position = 0;
    read_bit_position = 0;
    read_bit_filling_level = 0;
    read_byte_filling_level = 0;
}

extern void init_out(bool save_last_byte)
{
    if (save_last_byte)
    {
        out_buffer[0] = out_buffer[write_byte_position];
    }
    else
    {
        write_bit_position = 0;
    }
    write_byte_position = 0;
}

extern EXIT open_infile(char in_filename[])
{
    p_infile = fopen(in_filename, "rb");
    init_in();
    end_of_infile = false;
    if (p_infile == NULL)
    {
        return IO_EXCEPTION;
    }
    return SUCCESS;
}

extern EXIT open_outfile(char out_filename[])
{
    p_outfile = fopen(out_filename, "wb");
    init_out(false);
    if (p_outfile == NULL)
    {
        return IO_EXCEPTION;
    }
    return SUCCESS;
}

extern void close_infile(void)
{
    fclose(p_infile);
}

extern void close_outfile(void)
{
    fclose(p_outfile);
}

static int read_infile(void)
{
    init_in();
    size_t size = fread(in_buffer, sizeof(char), BUF_SIZE, p_infile);
    read_byte_filling_level = size;
    read_bit_filling_level = 7;
    SPRINT(in_buffer);
    return size;
}

static void write_outfile(void)
{
    if (write_bit_position != 0 && end_of_infile)
    {
        write_byte_position++;
    }

    fwrite(out_buffer, sizeof(char), write_byte_position, p_outfile);
    SPRINT(out_buffer);
    init_out(write_bit_position != 0);
}

extern bool has_next_char(void)
{
    bool has_next = read_byte_position < read_byte_filling_level;

    if (write_byte_position == BUF_SIZE && write_bit_position == 0)
    {
        write_outfile();
    }

    if (!has_next)
    {
        has_next = read_infile() > 0;
        end_of_infile = !has_next;
        write_outfile();
    }
    return has_next;
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

extern unsigned int read_int(void)
{
    CHARS_IN_INT *chars_in_int = (CHARS_IN_INT *) malloc(sizeof(CHARS_IN_INT));
    for (int i = 3; i >= 0; i--)
    {
        if (has_next_char())
        {
            chars_in_int->c[i] = read_char();
        }
    }
    return chars_in_int->i;
}

extern void write_int(unsigned int i)
{
    CHARS_IN_INT *chars_in_int = (CHARS_IN_INT *) malloc(sizeof(CHARS_IN_INT));
    chars_in_int->i = i;
    for (int j = 3; j >= 0; j--)
    {
        write_char(chars_in_int->c[j]);
    }
}

extern bool has_next_bit(void)
{
    bool has_next = read_byte_position < read_byte_filling_level
                    && read_bit_position <= read_bit_filling_level;

    if (write_byte_position == BUF_SIZE)
    {
        write_outfile();
    }

    if (!has_next)
    {
        write_outfile();
        has_next = read_infile() > 0;
        end_of_infile = has_next;
    }
    return has_next;
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
    if (write_bit_position == 0)
    {
        out_buffer[write_byte_position] = '\0';
    }

    out_buffer[write_byte_position] = PUT_BIT(
            out_buffer[write_byte_position], c, write_bit_position);
    write_bit_position++;

    if (write_bit_position == 8)
    {
        write_bit_position = 0;
        write_byte_position++;
    }
}