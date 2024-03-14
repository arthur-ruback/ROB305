#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <mutex>
#include <vector>
#include "timespec.h"

void incr(unsigned int nLoops, double *pCounter);
void *call_incr(void *v_data);
void *call_incrP(void *v_data);

struct ThreadArgs
{
    unsigned int nLoops;
    double *pCounter;
    pthread_mutex_t *pMutex;
} ThreadArgs;

int main(int argc, char *argv[])
{

    ///////////////////////////////////////////////////////
    //////////////////       TP2       ////////////////////
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

    std::vector<pthread_t> threads(nTasks);
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    struct ThreadArgs args = {nLoops, &counter, &mutex};

    timespec before = timespec_now();

    if (protect)
    {
        for (unsigned int i = 0; i < nTasks; i++)
        {
            pthread_create(&threads[i], NULL, call_incrP, &args);
        }
    }
    else
    {
        for (unsigned int i = 0; i < nTasks; i++)
        {
            pthread_create(&threads[i], NULL, call_incr, &args);
        }
    }

    // Wait for all threads to finish
    for (unsigned int i = 0; i < nTasks; i++)
    {
        pthread_join(threads[i], NULL);
    }

    timespec after = timespec_now();
    timespec duration = after - before;
    printf("Counter: %f\n", counter);
    printf("Execution time: %f\n", timespec_to_ms(duration) / 1000);

    pthread_mutex_destroy(&mutex);

    return 0;
}

void incr(unsigned int nLoops, double *pCounter)
{
    for (unsigned int i = 0; i < nLoops; i++)
    {
        *pCounter += 1.0;
    }
}

void incrP(unsigned int nLoops, double *pCounter, pthread_mutex_t *mutex)
{
    for (unsigned int i = 0; i < nLoops; i++)
    {
        pthread_mutex_lock(mutex);
        *pCounter += 1.0;
        pthread_mutex_unlock(mutex);
    }
}

void *call_incr(void *v_data)
{
    struct ThreadArgs *args = (struct ThreadArgs *)v_data;
    incr(args->nLoops, args->pCounter);
    return NULL;
}

void *call_incrP(void *v_data)
{
    struct ThreadArgs *args = (struct ThreadArgs *)v_data;
    incrP(args->nLoops, args->pCounter, args->pMutex);
    return NULL;
}