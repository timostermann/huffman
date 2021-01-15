#include "io.h"
#include <stdio.h>
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

/**
 * Eingabestream
 */
static FILE *p_infile;

/**
 * Ausgabestream
 */
static FILE *p_outfile;

extern void init_in(void)
{
    read_byte_position = 0;
    read_bit_position = 0;
    read_bit_filling_level = 0;
    read_byte_filling_level = 0;
}

extern void init_out(void)
{
    write_byte_position = 0;
    write_bit_position = 0;
}

extern EXIT open_infile(char in_filename[])
{
    p_infile = fopen(in_filename, "rb");
    init_in();
    if (p_infile == NULL)
    {
        return IO_EXCEPTION;
    }
    return SUCCESS;
}

extern EXIT open_outfile(char out_filename[])
{
    p_outfile = fopen(out_filename, "wb");
    init_out();
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
    fwrite(out_buffer, sizeof(char), write_byte_position, p_outfile);
    SPRINT(out_buffer);
    init_out();
}

extern bool has_next_char(void)
{
    bool has_next = read_byte_position < read_byte_filling_level;

    if (write_byte_position == BUF_SIZE)
    {
        write_outfile();
    }

    if (!has_next)
    {
        write_outfile();
        has_next = read_infile() > 0;
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

extern bool has_next_bit(void)
{
    bool has_next = has_next_char()
                    && read_bit_position <= read_bit_filling_level;

    if (write_byte_position == BUF_SIZE)
    {
        write_outfile();
    }

    if (!has_next)
    {
        write_outfile();
        has_next = read_infile() > 0;
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
    out_buffer[write_byte_position] = PUT_BIT(
            out_buffer[write_byte_position], c, write_bit_position);
    write_bit_position++;

    if (write_bit_position == 8)
    {
        write_bit_position = 0;
        write_byte_position++;
    }
}