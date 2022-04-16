
#include <stdint.h>

/*! \class Buffer
    \brief A test class.
    Circular buffer to store BUFF_SIZE characters
*/
class Buffer
{
    static const uint8_t BUFF_SIZE = 16; // BUFF_SIZE should be power of two
    static const uint8_t BUFF_MASK = (16 - 1);
    uint8_t buffer[BUFF_SIZE];
    uint8_t put, get, length;

public:
    Buffer() : put(0), get(0), length(0){};

    void put_char(uint8_t ch);
    uint8_t get_char();

    //!
    //! Get character count in buffer
    inline uint8_t get_length()
    {
        return length;
    }
};
