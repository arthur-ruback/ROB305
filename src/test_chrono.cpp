#include <iostream>
#include "chrono.h"

int main()
{
    ///////////////////////////////////////////////////////
    //////////////////       TP3A      ////////////////////
    ///////////////////////////////////////////////////////

    Chrono chrono;
    std::cout << "Chrono is active: " << chrono.isActive() << std::endl;
    chrono.restart();
    std::cout << "Chrono is active: " << chrono.isActive() << std::endl;
    std::cout << "Chrono start time: " << timespec_to_ms(chrono.startTime()) << " ms" << std::endl;
    for (int i = 0; i < 100000000; ++i)
    {
    }
    std::cout << "Chrono lap: " << chrono.lap() << " ms" << std::endl;
    chrono.stop();
    std::cout << "Chrono is active: " << chrono.isActive() << std::endl;
    std::cout << "Chrono stop time: " << timespec_to_ms(chrono.stopTime()) << " ms" << std::endl;
    std::cout << "Chrono lap: " << chrono.lap() << " ms" << std::endl;
    return 0;
}