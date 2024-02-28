#include <iostream>
#include <vector>

#include "timer.h"

class Looper
{
private:
    bool doStop;
    double iLoop;

public:
    double runLoop(double nLoops = __DBL_MAX__);
    double getSample();
    double stopLoop();
};

class Calibrator : public Timer
{
private:
    double a;
    double b;
    Looper looper;
    unsigned nTotalSamples;

    std::vector<double> samples;

protected:
    void callback();

public:
    Calibrator(double samplingPeriod_ms, unsigned nSamples);
    double nLoops(double duration_ms);
};

class CpuLoop : public Looper
{
private:
    Calibrator &calibrator;

public:
    CpuLoop(Calibrator &calibrator);
    void runTime(double duration_ms);
};

int main()
{
    ///////////////////////////////////////////////////////
    //////////////////       TP3C      ////////////////////
    ///////////////////////////////////////////////////////
    // test the calibrator class
    Calibrator calibrator(3, 1000);
    CpuLoop cpuLoop(calibrator);
    cpuLoop.runTime(1000);
    std::cout << "nLoops estimated = " << calibrator.nLoops(1000) << std::endl;
    std::cout << "nLoops real      = " << cpuLoop.getSample() << std::endl;
    return 0;
}

///////////////////////////
// implementation of CPU loop

CpuLoop::CpuLoop(Calibrator &calibrator) : calibrator(calibrator)
{
}

void CpuLoop::runTime(double duration_ms)
{
    runLoop(calibrator.nLoops(duration_ms));
}

///////////////////////////
// implementation of Looper

double Looper::runLoop(double nLoops)
{
    doStop = false;
    iLoop = 0;
    while (!doStop && iLoop < nLoops)
    {
        iLoop++;
    }
    return iLoop;
}

double Looper::getSample()
{
    return iLoop;
}

double Looper::stopLoop()
{
    doStop = true;
    return iLoop;
}

///////////////////////////
// implementation of Calibrator

Calibrator::Calibrator(double samplingPeriod_ms, unsigned nSamples) : Timer(), looper(), nTotalSamples(nSamples)
{
    start(samplingPeriod_ms, true);
    looper.runLoop(nSamples);
    // wait for the end of the samples
    while (samples.size() < nSamples)
    {
    }
    // Least mean squares method
    double sumX = 0;
    double sumY = 0;
    double sumXY = 0;
    double sumX2 = 0;
    for (unsigned i = 0; i < nSamples; i++)
    {
        sumX += i * samplingPeriod_ms;
        sumY += samples[i];
        sumXY += i * samplingPeriod_ms * samples[i];
        sumX2 += i * samplingPeriod_ms * i * samplingPeriod_ms;
    }
    a = (nSamples * sumXY - sumX * sumY) / (nSamples * sumX2 - sumX * sumX);
    b = (sumY - a * sumX) / nSamples;
}

void Calibrator::callback()
{
    samples.push_back(looper.getSample());
    if (samples.size() >= nTotalSamples)
    {
        stop();
    }
}

double Calibrator::nLoops(double duration_ms)
{
    return (a * duration_ms + b);
}