#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <time.h>
#include <signal.h>
#include <iostream>
#include <cstring>

#include "timespec.h"

class Timer
{
private:
    timer_t tid;

public:
    Timer();
    virtual ~Timer();
    void start(double duration_ms, bool isPeriodic = false);
    void stop();

protected:
    virtual void callback() = 0;

private:
    static void call_callback(int signo, siginfo_t *si, void *user_data);
};

#endif
