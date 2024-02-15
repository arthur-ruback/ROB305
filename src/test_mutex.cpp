#include <time.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <pthread.h>
#include <vector>
#include <string.h>
#include <stdio.h>

#include "thread.h"
#include "timespec.h"
#include "mutex.h"

class ThreadIncrement : public Thread
{
public:
    ThreadIncrement(unsigned int nLoops, double *pCounter, Mutex *pMutex = nullptr) : nLoops(nLoops), pCounter(pCounter), pMutex(pMutex) {}
    void run() override
    {
        for (unsigned int i = 0; i < nLoops; i++)
        {
            if (pMutex != nullptr)
            {
                Mutex::Lock lock(*pMutex);
                *pCounter += 1.0;
            }
            else
            {
                *pCounter += 1.0;
            }
        }
    }

private:
    unsigned int nLoops;
    double *pCounter;
    Mutex *pMutex;
};

int main(int argc, char *argv[])
{

    ///////////////////////////////////////////////////////
    //////////////////       TP4B      ////////////////////
    ///////////////////////////////////////////////////////

    unsigned int nLoops = 0;
    unsigned int nTasks = 0;
    double counter = 0.0;
    bool protect = false;
    if (argc > 1)
    {
        nLoops = atoi(argv[1]);
    }
    else
    {
        nLoops = 1000000;
    }
    if (argc > 2)
    {
        nTasks = atoi(argv[2]);
    }
    else
    {
        nTasks = 1;
    }
    // third parameter protected or unprotected that makes use of a mutex or not
    if (argc > 3)
    {
        if (strcmp(argv[3], "protected") == 0)
        {
            printf("Protected mode\n");
            protect = true;
        }
        else if (strcmp(argv[3], "unprotected") == 0)
        {
            printf("Unprotected mode\n");
        }
        else
        {
            printf("Invalid third parameter\n");
            return 1;
        }
    }

    // instead of using pthreads, we'll use the thread class

    std::vector<Thread *> threads;

    // instead of using cpp mutex, we'll use our own implementation

    Mutex mutex;

    timespec before = timespec_now();

    if (protect)
    {
        for (unsigned int i = 0; i < nTasks; i++)
        {
            threads.push_back(new ThreadIncrement(nLoops, &counter, &mutex));
        }
    }
    else
    {
        for (unsigned int i = 0; i < nTasks; i++)
        {
            threads.push_back(new ThreadIncrement(nLoops, &counter));
        }
    }

    for (unsigned int i = 0; i < nTasks; i++)
    {
        threads[i]->start();
    }

    // Wait for all threads to finish
    for (unsigned int i = 0; i < nTasks; i++)
    {
        threads[i]->join();
    }

    timespec after = timespec_now();
    timespec duration = after - before;
    printf("Counter: %f\n", counter);
    printf("Execution time: %f\n", timespec_to_ms(duration) / 1000);
    return 0;
}
