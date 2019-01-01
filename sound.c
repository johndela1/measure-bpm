#include <stdio.h>
#include <stdlib.h>

int _avg(unsigned char new, unsigned char old)
{
    double rate = .05;
    return (unsigned char) new*rate + old*(1-rate);
}

static int rectify(int v)
{
    return v < 127 ? 127 - v : v - 127;
}

int main()
{
    int threshold = 20;
    int v = 0;
    int decay = 0;

    for (int t1 = 0, t2 = 0; feof(stdin) == 0; t2++) {
        v = rectify(fgetc(stdin));

        // if (t2 % 100== 0) printf(": %d\n", v);
        if (v > threshold && decay == 0) {
            printf("beat %d\n", (int) (t2-t1) / 100);
            t1 = t2;
            decay = 3000;
        }
        if (decay > 0)
            decay--;
    }
    return 0;
}
