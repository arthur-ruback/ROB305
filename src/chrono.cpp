#include "chrono.h"

Chrono::Chrono()
{
    restart();
}

void Chrono::restart()
{
    startTime_ = timespec_now();
    stopTime_ = {};
    isActive_ = true;
}

void Chrono::stop()
{
    if (isActive_)
    {
        stopTime_ = timespec_now();
        isActive_ = false;
    }
}

bool Chrono::isActive() const
{
    return isActive_;
}

timespec Chrono::startTime() const
{
    return startTime_;
}

timespec Chrono::stopTime() const
{
    return stopTime_;
}

long Chrono::lap() const
{
    if (isActive_)
    {
        timespec currentTime = timespec_now();
        return static_cast<long>(timespec_to_ms(currentTime - startTime_));
    }
    else
    {
        return static_cast<long>(timespec_to_ms(stopTime_ - startTime_));
    }
}
