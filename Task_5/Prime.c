#include "Prime.h"

int isPrime(unsigned int num)
{
    if (num <= 1)
        return 0;
    if (num % 2 == 0 && num > 2)
        return 0;
    for (unsigned int i = 3; i <= sqrt(num); i += 2)
    {
        if (num % i == 0)
            return 0;
    }
    return 1;
}
