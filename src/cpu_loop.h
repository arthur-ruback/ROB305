#pragma once

#include <vector>
#include "timer.h"

class Looper
{
private:
    bool volatile doStop;
    double volatile iLoop;

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