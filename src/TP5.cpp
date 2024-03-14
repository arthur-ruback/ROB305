#include <iostream>
#include <signal.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sched.h>
#include <errno.h>

#include "cpu_loop.h"
#include "thread.h"
#include "mutex.h"
#include "timespec.h"
#include "chrono.h"

#define TICK_TO_MS 10

#define tics(n) cpuLoop.runTime(n *TICK_TO_MS)

class ThreadA : public Thread
{
public:
    ThreadA(Mutex *R, Calibrator *calib) : R(R), calib(calib), cpuLoop(*calib)
    {
        setScheduling(SCHED_RR, 80);
    }
    void run() override
    {
        // I execute for 10 tics
        tics(10);
        {
            Mutex::Lock lock(*R);
            // I execute for 10 tics
            tics(10);
        } // free mutex
        // I execute for 20 tics
        tics(20);
    }

private:
    Mutex *R;
    Calibrator *calib;
    CpuLoop cpuLoop;
};

class ThreadB : public Thread
{
public:
    ThreadB(Calibrator *calib) : calib(calib), cpuLoop(*calib)
    {
        setScheduling(SCHED_RR, 70);
    }
    void run() override
    {
        // I execute for 10 tics
        tics(10);
    }

private:
    Calibrator *calib;
    CpuLoop cpuLoop;
};

class ThreadC : public Thread
{
public:
    ThreadC(Mutex *R, Calibrator *calib) : R(R), calib(calib), cpuLoop(*calib)
    {
        setScheduling(SCHED_RR, 60);
    }
    void run() override
    {
        // I execute for 20 tics
        tics(20);
        {
            Mutex::Lock lock(*R);
            // I execute for 20 tics
            tics(20);
        } // free mutex
        // I execute for 10 tics
        tics(10);
    }

private:
    Mutex *R;
    Calibrator *calib;
    CpuLoop cpuLoop;
};

int main(int argc, char *argv[])
{
    ///////////////////////////////////////////////////////
    //////////////////       TP5      /////////////////////
    ///////////////////////////////////////////////////////
    // example inversion de prioritées

    // get runtime argument for the mutex
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <inversion safe mutex> (true/false)" << std::endl;
        return 1;
    }

    bool inversionSafe = std::string(argv[1]) == "true";

    // binding this process to the first CPU
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    if (sched_setaffinity(0, sizeof(mask), &mask) == -1)
    {
        std::cerr << "sched_setaffinity failed" << std::endl;
        return 1;
    }

    // set the scheduling policy and priority of the process
    struct sched_param param;
    param.sched_priority = sched_get_priority_max(SCHED_RR);
    int err = pthread_setschedparam(pthread_self(), SCHED_RR, &param);
    if (err != 0)
    {
        if (err == EPERM)
        {
            std::cerr << "pthread_setschedparam failed with error EPERM, Not Enough Permission" << std::endl;
            return 1;
        }
        else
        {
            std::cerr << "pthread_setschedparam failed with error " << err << std::endl;
            return 1;
        }
    }

    Calibrator calibrator(100, 50);

    // create a mutex (inversion safe = true)
    Mutex R(inversionSafe);

    // launch 3 threads with different priorities
    ThreadA threadA(&R, &calibrator);
    ThreadB threadB(&calibrator);
    ThreadC threadC(&R, &calibrator);

    std::cout << "Starting threads" << std::endl;
    threadC.start();
    // wait for 30 tics
    timespec_wait(timespec_from_ms(30 * TICK_TO_MS));
    threadA.start();
    threadB.start();

    // wait for the threads to finish
    threadA.join();
    threadB.join();
    threadC.join();

    // print the time taken for each thread to execute
    std::cout << "Thread A took " << threadA.execTime_ms() << " ms" << std::endl;
    std::cout << "Thread B took " << threadB.execTime_ms() << " ms" << std::endl;
    std::cout << "Thread C took " << threadC.execTime_ms() << " ms" << std::endl;

    // print the finish order of three threads based on thread.endTime_ms()
    double timeA_ms = threadA.endTime_ms();
    double timeB_ms = threadB.endTime_ms();
    double timeC_ms = threadC.endTime_ms();
    if (timeA_ms < timeB_ms && timeB_ms < timeC_ms)
    {
        std::cout << "A then B then C" << std::endl;
    }
    else if (timeA_ms < timeC_ms && timeC_ms < timeB_ms)
    {
        std::cout << "A then C then B" << std::endl;
    }
    else if (timeB_ms < timeA_ms && timeA_ms < timeC_ms)
    {
        std::cout << "B then A then C" << std::endl;
    }
    else if (timeB_ms < timeC_ms && timeC_ms < timeA_ms)
    {
        std::cout << "B then C then A" << std::endl;
    }
    else if (timeC_ms < timeA_ms && timeA_ms < timeB_ms)
    {
        std::cout << "C then A then B" << std::endl;
    }
    else if (timeC_ms < timeB_ms && timeB_ms < timeA_ms)
    {
        std::cout << "C then B then A" << std::endl;
    }
    else
    {
        std::cout << "Error" << std::endl;
    }

    return 0;
}
