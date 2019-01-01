#include <stdio.h>
#include <stdlib.h>

int decayed(unsigned char new, unsigned char old)
{
    double rate = .05;
    return (unsigned char) new*rate + old*(1-rate);
}

unsigned char rectified(unsigned char v)
{
    //printf("after: %d\n", v < 127 ? 127 - v : v - 127);
    return v < 127 ? 127 - v : v - 127;
}

int main()
{
    unsigned char v, v1 = 0;
    int sound = 0;
    int avg = 0;
    for (int t1 = 0, t2 = 0; !feof(stdin); t2++) {
        v1 = v = decayed(rectified(fgetc(stdin)), v1);

        if (t2 % 100 == 0) printf("voltage %d\n", v);

        if (v > 20) {
            if (!sound) {
                t1 = t2;
                printf("start %d\n", t1);
                sound = 1;
            }
        }
        else {
            if (sound) {
                printf("duration: %d\n", t2-t1);
                sound = 0;
            }
        }
    }
}
