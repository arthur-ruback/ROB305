#pragma once

#include <climits>
#include "mutex.h"

class Semaphore
{
private:
    unsigned counter;
    unsigned maxCount;
    Mutex mutex;

public:
    Semaphore(unsigned initCount = 0, unsigned maxCount = UINT_MAX);
    ~Semaphore();
    void give();
    void take();
    bool take(double timeout_ms);
    unsigned getCounter_DEBUG() { return counter; }
};