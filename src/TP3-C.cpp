#include <iostream>

#include "cpu_loop.h"
#include "timespec.h"

int main()
{
    ///////////////////////////////////////////////////////
    //////////////////       TP3C      ////////////////////
    ///////////////////////////////////////////////////////
    // test the calibrator class
    Calibrator calibrator(1000, 5);
    CpuLoop cpuLoop(calibrator);
    timespec tic = timespec_now();
    cpuLoop.runTime(1000);
    timespec toc = timespec_now();
    std::cout << "nLoops estimated = " << calibrator.nLoops(1000) << std::endl;
    std::cout << "Elapsed time     = " << timespec_to_ms(toc - tic) << " ms" << std::endl;
    return 0;
}