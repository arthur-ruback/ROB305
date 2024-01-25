#ifndef timespec_h_INCLUDED
#define timespec_h_INCLUDED

#include <time.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <cerrno>

#define S_TO_NS 1000000000
#define S_TO_MS 1000
#define MS_TO_S 0.001
#define MS_TO_NS 1000000
#define NS_TO_MS 0.000001

void timespec_print(const timespec &time_ts);

double timespec_to_ms(const timespec &time_ts);

timespec timespec_from_ms(double time_ms);

timespec timespec_now();

timespec timespec_negate(const timespec &time_ts);

timespec timespec_add(const timespec &time1_ts, const timespec &time2_ts);

timespec timespec_subtract(const timespec &time1_ts, const timespec &time2_ts);

timespec timespec_wait(const timespec &delay_ts);

timespec operator-(const timespec &time_ts);

timespec operator+(const timespec &time1_ts, const timespec &time2_ts);

timespec operator-(const timespec &time1_ts, const timespec &time2_ts);

timespec &operator+=(timespec &time_ts, const timespec &delay_ts);

timespec &operator-=(timespec &time_ts, const timespec &delay_ts);

bool operator==(const timespec &time1_ts, const timespec &time2_ts);

bool operator!=(const timespec &time1_ts, const timespec &time2_ts);

bool operator<(const timespec &time1_ts, const timespec &time2_ts);

bool operator>(const timespec &time1_ts, const timespec &time2_ts);

#endif