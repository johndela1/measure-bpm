#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define rectify(v) ((v) < 128 ? 128 - (v) : (v) - 128)

static double _avg(double new, double rate, double old)
{
    return new*rate + old*(1-rate);
}

int test()
{
    int tests[][2] = {{127, 1}, {128, 0}, {129, 1}};

    for (int i = 0; i < 3; i++) {
        assert(rectify(tests[i][0]) == tests[i][1]);
    }
    return 1;
}

int main(int argc, char *argv[])
{
    test();

    double avgbpm1 = 0;
    double avgbpm2 = 0;
    double bpm1= 0;
    double bpm2 = 0;
    int decay = 100;
    int hz = 8000;
    int t1, t2, v;
    int thresh = 100;

    if (argc == 2)
        thresh = atoi(argv[1]);

    for (t1 = t2 = 0; feof(stdin) == 0; t2++) {
        v = rectify(fgetc(stdin));
        // if (t2 % 1000== 0) printf(": %d\n", (t2-t1)>>1);
        if (v > thresh && decay == 0) {
            bpm1 = bpm2;
            bpm2 = 60 / (((double)(t2-t1)) / hz);
            avgbpm1 = _avg(bpm2, .75, avgbpm1);
            avgbpm2 = _avg(bpm2, .5, avgbpm2);
            printf("dev %7.3f bpm %f %f %f\n", bpm2-bpm1, bpm2, avgbpm1, avgbpm2);
            t1 = t2;
            decay = 3000;
        }
        decay = decay > 0 ? decay-1 : 0;
    }
    return 0;
}
