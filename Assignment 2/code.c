#include <stdio.h>

// This is comment

void main() // This comment
{
    for (char i = 0; i <= 10; i++)
        printf("%d\t", i);

    float f = (10 / 3 * 2) % 5 + (+0.05) - (-1e-2);
    f = f + 2;
    f -= 2;
    f /= 1;
    f *= 1;

    if (!(1 != 2) && (2 & 3 == 3 | 2) && 2 || 3)
        printf("Hello\n");
    else
        printf("World\n");

    long long d = 5 ^ ~((int)f);
    d--;
    d = d - 1;
    d %= 2;
    d = d >> 2;
    d = d << 1;
    d += 10;
    d ^= 100;

    float x = -10.23e10;
    int asdfd[10];

    while (d >= 0 && d--)
        printf("%lld\t", d);
}