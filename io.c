#include "io.h"
#include <stdio.h>

#define GET_BIT(BYTE, POS) ((BYTE & (0x01 << POS)) > 0)
#define PUT_BIT(BYTE, BIT, POS) (BIT == 0 ? (BYTE & ~(0x01 << POS)) : (BYTE | (0x01 << POS)))

static unsigned char in_buffer[BUF_SIZE];
static unsigned int read_position_byte = 0;
static unsigned int read_filling_level_byte = 0;
static unsigned short read_position_bit = 0;
static unsigned short read_filling_level_bit = 0;

static unsigned char out_buffer[BUF_SIZE] = {0};
static unsigned int write_position_byte = 0;
static unsigned int write_filling_level_byte = 0;
static unsigned short write_position_bit = 0;
static unsigned short write_filling_level_bit = 0;

extern void init_in(char text[])
{
    unsigned int index;
    for (index = 0; index < sizeof(text); index++)
    {
        in_buffer[index] = text[index];
    }
    read_position_byte = 0;
    read_position_bit = 0;
    read_filling_level_bit = 7;
    read_filling_level_byte = index - 1;
}

extern void init_out(void)
{
    write_filling_level_byte = 0;
    write_position_byte = 0;
}

extern void get_out_buffer(char text[])
{
    for (int i = 0; i < write_filling_level_byte; i++)
    {
        text[i] = out_buffer[i];
    }
}

extern bool has_next_char(void)
{
    return read_position_byte <= read_filling_level_byte;
}

extern unsigned char read_char(void)
{
    unsigned char next_char = in_buffer[read_position_byte];
    read_position_byte++;
    return next_char;
}

extern void write_char(unsigned char c)
{
    out_buffer[write_position_byte] = c;
    write_position_byte++;
    write_filling_level_byte++;
}

extern bool has_next_bit(void)
{
    return (read_position_byte < read_filling_level_byte)
           || ((read_position_byte == read_filling_level_byte)
               && read_position_bit <= read_filling_level_bit);
}

extern BIT read_bit(void)
{
    BIT bit = GET_BIT(in_buffer[read_position_byte], read_position_bit);
    read_position_bit++;

    if (read_position_bit == 8)
    {
        read_position_bit = 0;
        read_position_byte++;
    }
    return bit;
}

extern void write_bit(BIT c)
{
    PUT_BIT(out_buffer[write_position_byte], c, write_position_bit);
    write_position_bit++;

    if (write_position_bit == 8)
    {
        write_position_bit = 0;
        write_position_byte++;
    }
}

extern void print_out_char_array(unsigned char array[])
{
    for (int i = 0; i < sizeof(array); i++)
    {
        printf("%c ", array[i]);
    }
}