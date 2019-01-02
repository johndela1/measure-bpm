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
    int avgbpm = 0;
    int bpm = 0;
    int decay = 1000;
    int hz = 8000;
    int t1, t2, v;
    int threshold = 40;

    for (t1 = 0, t2 = 0; feof(stdin) == 0; t2++) {
        v = rectify(fgetc(stdin));
        // if (t2 % 1000== 0) printf(": %d\n", (t2-t1)>>1);
        if (v > threshold && decay == 0) {
            bpm = (int) (60 / (((double)(t2-t1)) / hz));
            avgbpm = _avg(bpm, avgbpm);
            printf("bpm: %d %d\n", bpm, avgbpm);
            t1 = t2;
            decay = 3000;
        }
        if (decay > 0)
            decay--;
    }
    return 0;
}
