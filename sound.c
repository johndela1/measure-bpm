#include <stdio.h>

static int _avg(int new, int old)
{
    double rate = .75;
    return (int) (new*rate + old*(1-rate));
}

static int rectify(int v)
{
    return v < 127 ? 127 - v : v - 127;
}

int main()
{
    int threshold = 20;
    int decay = 0;
    int bpm, period, t1, t2, v;
    int avgperiod = 0;
    int hz = 8000;

    for (t1 = t2 = 0; feof(stdin) == 0; t2++) {
        v = rectify(fgetc(stdin));
        // if (t2 % 1000== 0) printf(": %d\n", (t2-t1)>>1);
        if (v > threshold && decay == 0) {
            period = t2-t1;
            bpm = (int) (60 / (((double)(t2-t1)) / hz));
            avgperiod = _avg(period, avgperiod);
            printf("period %d %d\n", period, avgperiod);
            printf("bpm %d\n", bpm);
            t1 = t2;
            decay = 3000;
        }
        if (decay > 0)
            decay--;
    }
    return 0;
}
