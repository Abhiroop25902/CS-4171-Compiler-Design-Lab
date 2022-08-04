#include <stdio.h>

void main()
{
    for (char i = 0; i < 10; i++)
        printf("%d\t", i);

    float a = (10 / 3 * 2) % 5;

    if (!(1 == 2) && 2 || 3)
        printf("Hello\n");
    else
        printf("World\n");

    long long d = 5 ^ ~((int)a);

    while (d < 0 && d++)
        printf("%lld\t", d);
}