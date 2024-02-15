#pragma once

#include <pthread.h>
#include <exception>
#include "timespec.h"
#include "posix_thread.h"

class Thread : public PosixThread
{
public:
    Thread();
    ~Thread();

    void start();

    void sleep_ms(double);

    double startTime_ms();
    double endTime_ms();
    double execTime_ms();

protected:
    virtual void run() = 0;

private:
    static void *call_run(void *);

    timespec start_ts;
    timespec end_ts;
};
