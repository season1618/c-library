#include "syscall.h"
#include "bool.h"
#include "time.h"

#define CLOCK_REALTIME 0
#define CLOCK_MONOTONIC 1
#define CLOCK_PROCESS_CPUTIME_ID 2
#define CLOCK_THREAD_CPUTIME_ID 3
#define CLOCK_MONOTONIC_RAW 4
#define CLOCK_REALTIME_COARSE 5
#define CLOCK_MONOTONIC_COARSE 6
#define CLOCK_BOOTTIME 7
#define CLOCK_REALTIME_ALARM 8
#define CLOCK_BOOTTIME_ALARM 9
#define CLOCK_TAI 11

int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void get_real_time(struct real_time *rt) { // UTC
    struct timespec tp;
    clock_gettime(CLOCK_REALTIME, &tp);
    unsigned long x = tp.tv_sec;
    rt->second = x % 60; x /= 60;
    rt->minute = x % 60; x /= 60;
    rt->hour = x % 24; x /= 24;

    int y = 1970;
    while ((y - 1970) * 365 + (y - 1969) / 4 - (y - 1901) / 400 < x) y++;
    x -= (y - 1971) * 365 + (y - 1970) / 4 - (y - 1902) / 400;
    y--;
    bool is_leap = y % 4 == 0 && y % 400 != 0;
    int m = 1;
    while (month[m-1] + (is_leap && m == 2) < x) {
        x -= month[m-1] + (is_leap && m == 2);
        m++;
    }
    x++;

    rt->year = y;
    rt->month = m;
    rt->day = x;
}

void get_cpu_time(struct timespec *ct) {
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, ct);
}