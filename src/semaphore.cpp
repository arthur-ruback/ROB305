#include "semaphore.h"

Semaphore::Semaphore(unsigned initCount, unsigned maxCount) : counter(initCount), maxCount(maxCount)
{
}

Semaphore::~Semaphore()
{
}

void Semaphore::give()
{
    Mutex::Lock lock(mutex);
    if (counter < maxCount)
    {
        counter++;
    }
    lock.notifyAll();
}

void Semaphore::take()
{
    Mutex::Lock lock(mutex);
    while (counter == 0)
    {
        lock.wait();
    }
    counter--;
    lock.notifyAll();
}

bool Semaphore::take(double timeout_ms)
{
    Mutex::Lock lock(mutex);
    while (counter == 0)
    {
        if (!lock.wait(timeout_ms))
        {
            return false;
        }
    }
    counter--;
    lock.notifyAll();
    return true;
}