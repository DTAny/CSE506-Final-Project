#include "types.h"

#define SEED 0xACE1u

ushort get_rand(ushort limit)
{

    static ushort state = SEED;
    ushort lfsr;
    ushort b;
    ushort i = 0;

    if (state == 0)
    {
        state = state + 1;
    }

    lfsr = state;
    state = state + 1;

    do
    {
        b = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5));
        lfsr = (lfsr >> 1) | (b << 15);
        i++;
    } while (i < limit);
    return lfsr % limit;
}
