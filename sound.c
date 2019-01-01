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
    int v;
    int decay = 0;
    int dur;
    int avgdur = 0;

    for (int t1 = 0, t2 = 0; feof(stdin) == 0; t2++) {
        v = rectify(fgetc(stdin));
        // if (t2 % 100== 0) printf(": %d\n", v);
        if (v > threshold && decay == 0) {
            dur = (int) ((t2-t1) / 100);
            avgdur = _avg(dur, avgdur);
            printf("beat %d %d\n", dur, avgdur);
            t1 = t2;
            decay = 3000;
        }
        if (decay > 0)
            decay--;
    }
    return 0;
}
