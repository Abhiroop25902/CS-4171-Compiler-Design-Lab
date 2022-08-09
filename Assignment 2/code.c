#include <stdio.h>

// This is comment

void main() // This comment
{
    for (char i = 0; i <= 10; i++)
        printf("%d\t", i);

    float a = (10 / 3 * 2) % 5;
    a = a + 2;
    a -= 2;
    a /= 1;
    a *= 1;

    if (!(1 != 2) && (2 & 3 == 3 | 2) && 2 || 3)
        printf("Hello\n");
    else
        printf("World\n");

    long long d = 5 ^ ~((int)a);
    d--;
    d = d - 1;
    d %= 2;
    d = d >> 2;
    d = d << 1;
    d += 10;
    d ^= 100;

    while (d >= 0 && d--)
        printf("%lld\t", d);
}