#include <stdint.h>

class Serial
{
     uint8_t buffer[64];
     uint8_t put, get;
     void output();

public:
     Serial();

};
