
#include <stdint.h>

class Serial
{
    static const uint8_t BUFF_SIZE = 16;
    static const uint8_t BUFF_MASK = (16 - 1);

    // store and read characters in circular buffer
    uint8_t buffer[BUFF_SIZE];
    uint8_t put, get, length;

public:
    Serial() : put(0), get(0), length(0){};
    void put_char(uint8_t ch);
    uint8_t get_char();
};
