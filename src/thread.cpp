#include "thread.h"

Thread::Thread(){};

Thread::~Thread(){};

void Thread::start()
{
    isActive = true;
    clock_gettime(CLOCK_REALTIME, &start_ts);
    PosixThread::start(call_run, this);
}

void Thread::sleep_ms(double ms)
{
    timespec_wait(timespec_from_ms(ms));
}

double Thread::startTime_ms()
{
    return timespec_to_ms(start_ts);
}

double Thread::endTime_ms()
{
    return timespec_to_ms(end_ts);
}

double Thread::execTime_ms()
{
    return timespec_to_ms(end_ts - start_ts);
}

void *Thread::call_run(void *arg)
{
    Thread *thread = static_cast<Thread *>(arg);
    thread->run();
    clock_gettime(CLOCK_REALTIME, &thread->end_ts);
    return thread;
}