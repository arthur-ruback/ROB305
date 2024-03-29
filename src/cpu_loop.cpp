#include "cpu_loop.h"

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
    looper.runLoop();
    // Least mean squares method
    double sumX = 0;
    double sumY = 0;
    double sumXY = 0;
    double sumX2 = 0;
    for (unsigned i = 0; i < nSamples; i++)
    {
        sumX += (i + 1) * samplingPeriod_ms;
        sumY += samples[i];
        sumXY += (i + 1) * samplingPeriod_ms * samples[i];
        sumX2 += (i + 1) * samplingPeriod_ms * (i + 1) * samplingPeriod_ms;
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
        looper.stopLoop();
    }
}

double Calibrator::nLoops(double duration_ms)
{
    return (a * duration_ms + b);
}