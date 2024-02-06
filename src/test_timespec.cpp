#include <iostream>
#include <assert.h>
#include "timespec.h"

void incr(unsigned int nLoops, double *pCounter);

int main(int argc, char *argv[])
{

    ///////////////////////////////////////////////////////
    //////////////////       TP1-A     ////////////////////
    ///////////////////////////////////////////////////////

    // Test print
    timespec a = {0, 1012397};
    timespec b = {923, 12345};
    timespec c = {-2, 1000000};
    timespec d = {1, 0};
    timespec e = {-2, 10000000};
    timespec f = {1, 990000000};
    timespec g = {0, 10000000};
    printf("Testing print timespec\n");
    timespec_print(a);
    timespec_print(c);

    // Test operator ==
    printf("Testing operator ==\n");
    assert(a == a);
    assert(!(a == b));
    assert(!(a == d));
    assert(!(a == e));

    // Test timespec_to_ms
    printf("Testing timespec_to_ms\n");
    assert(timespec_to_ms(a) == 1.012397);
    assert(timespec_to_ms(b) == 923000.012345);
    assert(timespec_to_ms(c) == -2001);

    // Test timespec_from_ms
    printf("Testing timespec_from_ms\n");
    assert(timespec_from_ms(1.012397) == a);
    assert(timespec_from_ms(923000.012345) == b);
    assert(timespec_from_ms(-2001) == c);

    // Test timespec_now
    printf("Testing timespec_now: ");
    struct timespec now = timespec_now();
    timespec_print(now);

    // Test timespec_negate
    printf("Testing timespec_negate\n");
    assert(timespec_negate(e) == f);
    assert(timespec_negate(f) == e);

    // Test timespec_add
    printf("Testing timespec_add\n");
    assert(timespec_add(f, g) == timespec_from_ms(2000));
    assert(timespec_add(timespec_negate(f), f) == timespec_from_ms(0));

    // Test timespec_subtract
    printf("Testing timespec_subtract\n");
    assert(timespec_subtract(d, g) == timespec_from_ms(990));
    assert(timespec_subtract(f, f) == timespec_from_ms(0));

    // Test timespec_wait
    printf("Testing timespec_wait\n");
    timespec delay = {2, 10000000};
    timespec r, t1, t2, dt;

    t1 = timespec_now();
    r = timespec_wait(delay);
    t2 = timespec_now();

    dt = timespec_subtract(t2, t1);
    printf("Real time passed: ");
    timespec_print(dt);
    printf("Remaining time: ");
    timespec_print(r);

    // Test operator -
    printf("Testing operator - (negate)\n");
    assert(-e == f);
    assert(-f == e);

    // Test operator +
    printf("Testing operator + \n");
    assert(f + g == timespec_from_ms(2000));
    assert((-f) + f == timespec_from_ms(0));

    // Test operator -
    printf("Testing operator - (subtract)\n");
    assert(d - g == timespec_from_ms(990));
    assert(f - f == timespec_from_ms(0));

    // Test operator +=
    printf("Testing operator +=\n");
    timespec h = f;
    h += g;
    assert(h == timespec_from_ms(2000));

    // Test operator -=
    printf("Testing operator -=\n");
    h -= g;
    assert(h == f);

    // Test operator !=
    printf("Testing operator !=\n");
    assert(!(a != a));
    assert((a != b));
    assert((a != d));
    assert((a != e));

    // Test operator >
    printf("Testing operator >\n");
    assert(b > a);
    assert(a > c);
    assert(b > c);
    assert(!(e > f));

    // Test operator <
    printf("Testing operator <\n");
    assert(a < b);
    assert(c < a);
    assert(c < b);
    assert(!(f < e));

    printf("SUCESS :)\n");

    ///////////////////////////////////////////////////////
    //////////////////       TP1-C     ////////////////////
    ///////////////////////////////////////////////////////

    unsigned int nLoops = 0;
    double counter = 0.0;
    if (argc > 1)
    {
        nLoops = atoi(argv[1]);
    }
    else
    {
        nLoops = 1000000;
    }

    timespec tic = timespec_now();
    incr(nLoops, &counter);
    timespec toc = timespec_now();
    dt = toc - tic;
    printf("Counter: %f\n", counter);
    printf("Execution time: %f\n", timespec_to_ms(dt) / 1000);

    return 0;
}

void incr(unsigned int nLoops, double *pCounter)
{
    for (unsigned int i = 0; i < nLoops; i++)
    {
        *pCounter += 1.0;
    }
}