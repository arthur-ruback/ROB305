#include "posix_thread.h"

PosixThread::PosixThread() : posixId(0), isActive(false), myPolicy(SCHED_OTHER), myPriority(1)
{
    pthread_attr_init(&posixAttr);
}

PosixThread::PosixThread(pthread_t posixId) : posixId(posixId), isActive(true)
{
    pthread_attr_init(&posixAttr);
    int policy;
    sched_param schedParams;
    if (pthread_getschedparam(this->posixId, &policy, &schedParams) < 0)
    {
        isActive = false;
        posixId = 0;
        throw PosixThread::Exception(-1);
    }

    pthread_attr_setschedparam(&posixAttr, &schedParams);
    pthread_attr_setschedpolicy(&posixAttr, policy);
    myPolicy = policy;
    myPriority = schedParams.sched_priority;
}

PosixThread::~PosixThread()
{
    if (isActive)
    {
        pthread_attr_destroy(&posixAttr);
    }
}

void PosixThread::start(ThreadPosix threadFunc, void *threadArg)
{
    pthread_create(&posixId, &posixAttr, threadFunc, threadArg);
    isActive = true;
    setScheduling(myPolicy, myPriority);
}

void PosixThread::join()
{
    if (isActive)
    {
        pthread_join(posixId, NULL);
    }
    isActive = false;
}

bool PosixThread::join(double timeout_ms)
{
    if (isActive)
    {
        timespec timeout = timespec_from_ms(timeout_ms);
        return pthread_timedjoin_np(posixId, NULL, &timeout) == 0;
    }
    return false;
}

bool PosixThread::setScheduling(int policy, int priority)
{
    if (isActive)
    {
        sched_param schedParams;
        schedParams.sched_priority = priority;
        return pthread_setschedparam(posixId, policy, &schedParams) == 0;
    }
    // save for when the thread is activated
    else
    {
        myPolicy = policy;
        myPriority = priority;
    }
    return false;
}

bool PosixThread::getScheduling(int *policy, int *priority)
{
    if (isActive)
    {
        sched_param schedParams;
        if (pthread_getschedparam(posixId, policy, &schedParams) == 0)
        {
            *priority = schedParams.sched_priority;
            return true;
        }
    }
    return false;
}

const char *PosixThread::Exception::exceptionMsg() const noexcept
{
    return "\nThread does not exist!\n";
}
