#include <stdio.h>

// This is comment

void main() // This comment
{
    for (char i = 0; i <= 10; i++)
        printf("%d\t", i);

    float floater = (10 / 3 * 2) % 5 + (+0.05) - (-1e-2);
    floater = floater + 2;
    floater -= 2;
    floater /= 1;
    floater *= 1;

    if (!(1 != 2) && (2 & 3 == 3 | 2) && 2 || 3)
        printf("Hello\n");
    else
        printf("World\n");

    long long longer = 5 ^ ~((int)floater);
    longer--;
    longer = longer - 1;
    longer %= 2;
    longer = longer >> 2;
    longer = longer << 1;
    longer += 10;
    longer ^= 100;

    float x = -10.23e10;
    int asdfd[10];

    while (longer >= 0 && longer--)
        printf("%lld\t", longer);
}