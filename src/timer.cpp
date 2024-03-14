#include "timer.h"

Timer::Timer()
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = call_callback;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, nullptr);

    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = (void *)this;

    if (timer_create(CLOCK_REALTIME, &sev, &tid) == -1)
    {
        perror("Error creating timer");
        return;
    }
}

Timer::~Timer()
{
    timer_delete(tid);
}

void Timer::start(double duration_ms, bool isPeriodic)
{

    struct itimerspec its;
    its.it_value = timespec_from_ms(duration_ms);

    if (isPeriodic)
        its.it_interval = its.it_value; // Make it periodic
    else
        its.it_interval = {0, 0};

    if (timer_settime(tid, 0, &its, nullptr) == -1)
    {
        perror("Error setting timer");
        timer_delete(tid);
    }
}

void Timer::stop()
{
    struct itimerspec its;
    its.it_value = {0, 0};
    its.it_interval = {0, 0};

    if (timer_settime(tid, 0, &its, nullptr) == -1)
    {
        perror("Error setting timer");
        timer_delete(tid);
    }
}

void Timer::call_callback(int, siginfo_t *si, void *)
{
    Timer *timer = (Timer *)si->si_value.sival_ptr;
    if (timer)
    {
        timer->callback();
    }
}
