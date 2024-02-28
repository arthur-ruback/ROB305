#ifndef CHRONO_H_INCLUDED
#define CHRONO_H_INCLUDED

#include "timespec.h"

class Chrono
{
private:
    timespec startTime_;
    timespec stopTime_;
    bool isActive_;

public:
    Chrono();
    void restart();
    void stop();
    bool isActive() const;
    timespec startTime() const;
    timespec stopTime() const;
    long lap() const;
};

#endif