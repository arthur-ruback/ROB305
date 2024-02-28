#include <iostream>
#include <vector>
#include "semaphore.h"
#include "thread.h"

// define a producting thread
class Producer : public Thread
{
public:
    Producer(Semaphore &semaphore) : semaphore(semaphore) {}
    void run() override
    {
        semaphore.give();
    }

private:
    Semaphore &semaphore;
};

// define a consuming thread

class Consumer : public Thread
{
public:
    Consumer(Semaphore &semaphore) : semaphore(semaphore) {}
    void run() override
    {
        semaphore.take();
    }

private:
    Semaphore &semaphore;
};

int main(int argc, char *argv[])
{
    ///////////////////////////////////////////////////////
    //////////////////       TP4C      ////////////////////
    ///////////////////////////////////////////////////////

    // receive the number of producers and consumers
    int Nprod = 5;
    int Ncons = 5;
    if (argc > 1)
    {
        Nprod = atoi(argv[1]);
    }
    if (argc > 2)
    {
        Ncons = atoi(argv[2]);
    }

    Semaphore semaphore(0);

    std::vector<Thread *> threadsConsumer;
    std::vector<Thread *> threadsProducer;

    // create all producer threads
    for (int i = 0; i < Nprod; i++)
    {
        threadsProducer.push_back(new Producer(semaphore));
    }

    // create all consumer threads
    for (int i = 0; i < Ncons; i++)
    {
        threadsConsumer.push_back(new Consumer(semaphore));
    }

    // start all producer threads
    for (auto thread : threadsProducer)
    {
        thread->start();
    }

    // start all consumer threads
    for (auto thread : threadsConsumer)
    {
        thread->start();
    }

    // wait for all producer threads to finish
    for (auto thread : threadsProducer)
    {
        thread->join();
    }

    // wait for all consumer threads to finish
    for (auto thread : threadsConsumer)
    {
        thread->join();
    }

    std::cout << "All threads finished" << std::endl;
    std::cout << "Semaphore counter: " << semaphore.getCounter_DEBUG() << std::endl;

    return 0;
}