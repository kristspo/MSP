
#include <msp430.h>
#include "serial.h"

void Serial::put_char(uint8_t ch)
{
    if (length < BUFF_SIZE)
    {
        buffer[put] = ch;
        put = (put + 1) & BUFF_MASK;
        length++;
    }
}

uint8_t Serial::get_char()
{
    uint8_t ch = 0;
    if (length)
    {
        ch = buffer[get];
        get = (get + 1) & BUFF_MASK;
        length--;
    }
    return ch;
}
