#include <iostream>
#include <assert.h>
#include <unistd.h>
#include "timer.h"
#include "timespec.h"

// countdown class declaration
class CountDown : public Timer
{
private:
    int nCount;

protected:
    void callback() override;

public:
    CountDown(int n);
    int getNCount();
};

// main function
int main()
{
    // test the countdown class
    CountDown cd(10);
    cd.start(1000, true);
    while (cd.getNCount() > 0)
    {
        std::cout << "Main thread doing something else" << std::endl;
        usleep(500000);
    }
    // cd.stop();
    return 0;
}

// countdown class definition
CountDown::CountDown(int n)
{
    nCount = n;
}

void CountDown::callback()
{
    if (nCount > 0)
    {
        std::cout << "Counter = " << nCount << std::endl;
        --nCount;
    }
    else
    {
        stop();
    }
}

int CountDown::getNCount()
{
    return nCount;
}