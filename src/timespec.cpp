#include "timespec.h"

void timespec_print(const timespec &time_ts)
{
    printf("%ld,%.9ld s\n", time_ts.tv_sec, time_ts.tv_nsec);
}

double timespec_to_ms(const timespec &time_ts)
{
    return ((time_ts.tv_sec >= 0) ? 1 : -1) * time_ts.tv_nsec * NS_TO_MS + time_ts.tv_sec * S_TO_MS;
}

timespec timespec_from_ms(double time_ms)
{
    struct timespec aux;
    aux.tv_sec = (int)(time_ms * MS_TO_S);
    time_ms -= aux.tv_sec * S_TO_MS;
    aux.tv_nsec = (int)abs(time_ms * MS_TO_NS);
    return aux;
}

timespec timespec_now()
{
    timespec aux;
    clock_gettime(CLOCK_REALTIME, &aux);
    return aux;
}

timespec timespec_negate(const timespec &time_ts)
{
    timespec aux;
    aux.tv_sec = -time_ts.tv_sec - 1;
    aux.tv_nsec = S_TO_NS - time_ts.tv_nsec;
    return aux;
}

timespec timespec_add(const timespec &time1_ts, const timespec &time2_ts)
{
    timespec aux;
    aux.tv_nsec = time1_ts.tv_nsec + time2_ts.tv_nsec;
    aux.tv_sec = time1_ts.tv_sec + time2_ts.tv_sec + (aux.tv_nsec >= S_TO_NS);
    aux.tv_nsec = aux.tv_nsec - (aux.tv_nsec >= S_TO_NS) * S_TO_NS;
    return aux;
}

timespec timespec_subtract(const timespec &time1_ts, const timespec &time2_ts)
{
    timespec aux = timespec_negate(time2_ts);
    aux = timespec_add(time1_ts, aux);
    return aux;
}

timespec timespec_wait(const timespec &delay_ts)
{
    timespec remaining_ts;
    if (nanosleep(&delay_ts, &remaining_ts) < 0)
    {
        switch (errno)
        {
        case EFAULT:
            std::cerr << "Problem with copying information from user space, returning remaining time" << std::endl;
            break;
        case EINTR:
            std::cerr << "The pause has been interrupted by a signal that was delivered to the thread, returning remaining time" << std::endl;
            break;
        case EINVAL:
            std::cerr << "The value in the tv_nsec  field  was  not  in  the  range  0  to 999999999 or tv_sec was negative" << std::endl;
            break;
        default:
            std::cerr << "Unknown error " << errno << std::endl;
            break;
        }
    }
    else
    {
        remaining_ts = {0, 0};
    }
    return remaining_ts;
}

timespec operator-(const timespec &time_ts)
{
    return timespec_negate(time_ts);
}

timespec operator+(const timespec &time1_ts, const timespec &time2_ts)
{
    return timespec_add(time1_ts, time2_ts);
}

timespec operator-(const timespec &time1_ts, const timespec &time2_ts)
{
    return timespec_subtract(time1_ts, time2_ts);
}

timespec &operator+=(timespec &time_ts, const timespec &delay_ts)
{
    time_ts = timespec_add(time_ts, delay_ts);
    return time_ts;
}

timespec &operator-=(timespec &time_ts, const timespec &delay_ts)
{
    time_ts = timespec_subtract(time_ts, delay_ts);
    return time_ts;
}

bool operator==(const timespec &time1_ts, const timespec &time2_ts)
{
    return (time1_ts.tv_nsec == time2_ts.tv_nsec) && (time1_ts.tv_sec == time2_ts.tv_sec);
}

bool operator!=(const timespec &time1_ts, const timespec &time2_ts)
{
    return (time1_ts.tv_nsec != time2_ts.tv_nsec) || (time1_ts.tv_sec != time2_ts.tv_sec);
}

bool operator<(const timespec &time1_ts, const timespec &time2_ts)
{
    return ((time1_ts.tv_sec < time2_ts.tv_sec) || ((time1_ts.tv_sec == time2_ts.tv_sec) && (time1_ts.tv_nsec < time2_ts.tv_nsec)));
}

bool operator>(const timespec &time1_ts, const timespec &time2_ts)
{
    return ((time1_ts.tv_sec > time2_ts.tv_sec) || ((time1_ts.tv_sec == time2_ts.tv_sec) && (time1_ts.tv_nsec > time2_ts.tv_nsec)));
}