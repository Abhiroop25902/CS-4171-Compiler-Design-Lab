#include <stdio.h>

// This is comment

void main() // This comment
{
    for (char i = 0; i <= 10; i++)
        printf("%d\t", i);

    float float_er = (10 / 3 * 2) % 5 + (+0.05) - (-1e-2);
    float_er = float_er + 2;
    float_er -= 2;
    float_er /= 1;
    float_er *= 1;

    if (!(1 != 2) && (2 & 3 == 3 | 2) && 2 || 3)
        printf("Hello\n");
    else
        printf("World\n");

    long long longer = 5 ^ ~((int)float_er);
    longer--;
    longer = longer - 1;
    longer %= 2;
    longer = longer >> 2;
    longer = longer << 1;
    longer += 10;
    longer ^= 00;

    float _x = -10.23e10;
    int asdfd[10];

    while (longer >= 0 && longer--)
        printf("%lld\t", longer);

    return;
}