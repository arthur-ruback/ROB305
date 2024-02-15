#pragma once

#include <pthread.h>
#include <exception>
#include "timespec.h"

class PosixThread
{
public:
    using ThreadPosix = void *(*)(void *);

public:
    PosixThread();
    PosixThread(pthread_t);
    ~PosixThread();

    void start(ThreadPosix, void *);
    void join();
    bool join(double);
    bool setScheduling(int, int);
    bool getScheduling(int *, int *);

    // exception class
    class Exception : public std::exception
    {
    public:
        Exception(int errorCode) : errorCode(errorCode) {}
        const char *exceptionMsg() const noexcept;

    private:
        int errorCode;
    };

protected:
    pthread_t posixId;
    pthread_attr_t posixAttr;
    bool isActive;
};
