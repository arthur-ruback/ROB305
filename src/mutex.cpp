#include "mutex.h"

Mutex::Mutex(bool isInversionSafe)
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
    if (isInversionSafe)
    {
        pthread_mutexattr_setprotocol(&attr, PTHREAD_PRIO_INHERIT);
    }
    pthread_mutex_init(&id, &attr);
    pthread_cond_init(&condId, nullptr);
    pthread_mutexattr_destroy(&attr);
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&id);
    pthread_cond_destroy(&condId);
}

void Mutex::lock()
{
    pthread_mutex_lock(&id);
}

bool Mutex::lock(double timeout)
{
    timespec ts = timespec_now();
    ts = ts + timespec_from_ms(timeout * 1000);
    return pthread_mutex_timedlock(&id, &ts) == 0;
}

void Mutex::unlock()
{
    pthread_mutex_unlock(&id);
}

void Mutex::Monitor::wait()
{
    pthread_cond_wait(&mutex.condId, &mutex.id);
}

bool Mutex::Monitor::wait(double timeout_ms)
{
    timespec ts = timespec_now();
    ts = ts + timespec_from_ms(timeout_ms);
    return pthread_cond_timedwait(&mutex.condId, &mutex.id, &ts) == 0;
}

void Mutex::Monitor::notify()
{
    pthread_cond_signal(&mutex.condId);
}

void Mutex::Monitor::notifyAll()
{
    pthread_cond_broadcast(&mutex.condId);
}

Mutex::Monitor::Monitor(Mutex &m) : mutex(m)
{
}

Mutex::Lock::Lock(Mutex &m) : Monitor(m)
{
    mutex.lock();
}

Mutex::Lock::Lock(Mutex &m, double timeout_ms) : Monitor(m)
{
    if (!mutex.lock(timeout_ms))
    {
        throw TimoutException();
    }
}

Mutex::Lock::~Lock()
{
    mutex.unlock();
}