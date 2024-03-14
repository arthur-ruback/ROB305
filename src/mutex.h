#pragma once

#include <pthread.h>
#include "timespec.h"

class Mutex
{
public:
    class Lock;
    class Monitor;

private:
    pthread_mutex_t id;
    pthread_cond_t condId;

public:
    Mutex(bool isInversionSafe = false);
    ~Mutex();

private:
    void lock();
    bool lock(double);
    void unlock();
};

class Mutex::Monitor
{
public:
    class TimoutException
    {
    };
    void wait();
    bool wait(double);
    void notify();
    void notifyAll();

protected:
    explicit Monitor(Mutex &);

protected:
    Mutex &mutex;
};

class Mutex::Lock : public Mutex::Monitor
{
public:
    Lock(Mutex &);
    Lock(Mutex &, double);
    ~Lock();
};