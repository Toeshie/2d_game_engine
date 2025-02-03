#include "MathHelper.h"
#include <cmath>
#include <random>
#include <time.h>

float MathHelper::square_root(float val)
{
    return sqrt(val);
}

int MathHelper::absolute_value(const int value)
{
    return std::abs(value);
}

int MathHelper::random_int_in_range(int min, int max)
{
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned>(time(nullptr)));
        seeded = true;
    }
    return min + (rand() % (max - min + 1));
}
