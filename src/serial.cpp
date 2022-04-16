
#include <msp430.h>
#include "serial.h"

/**
 * Put character into buffer. Ignores character if buffer is full.
 */
void Buffer::put_char(uint8_t ch)
{
    if (length < BUFF_SIZE)
    {
        buffer[put] = ch;
        put = (put + 1) & BUFF_MASK;
        length++;
    }
}

/**
 * Get character from buffer. Returns 0 if buffer is empty.
 */
uint8_t Buffer::get_char()
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
