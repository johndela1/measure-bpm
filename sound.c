#include <stdio.h>

static double _avg(double new, double rate, double old)
{
    return new*rate + old*(1-rate);
}

static int rectify(int v)
{
    return v < 127 ? 127 - v : v - 127;
}

int main()
{
    double avgbpm1 = 0;
    double avgbpm2 = 0;
    double bpm = 0;
    int decay = 1000;
    int hz = 8000;
    int t1, t2, v;
    int threshold = 40;

    for (t1 = t2 = 0; feof(stdin) == 0; t2++) {
        v = rectify(fgetc(stdin));
        // if (t2 % 1000== 0) printf(": %d\n", (t2-t1)>>1);
        if (v > threshold && decay == 0) {
            bpm = 60 / (((double)(t2-t1)) / hz);
            avgbpm1 = _avg(bpm, .75, avgbpm1);
            avgbpm2 = _avg(bpm, .5, avgbpm2);
            printf("bpm: %f %f %f\n", bpm, avgbpm1, avgbpm2);
            t1 = t2;
            decay = 3000;
        }
        decay = decay > 0 ? decay-1 : 0;
    }
    return 0;
}
