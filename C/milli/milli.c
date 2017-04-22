#include <time.h>
#include <sys/time.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

#include <stdio.h>

// MAJOR Credit to jbenet at stackoverflow.com

int main() {
    struct timespec ts;

    #ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    ts.tv_sec = mts.tv_sec;
    ts.tv_nsec = mts.tv_nsec;

    #else
    clock_gettime(CLOCK_REALTIME, &ts);
    #endif

    long millis = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
    printf("%ld\n", millis);

    return 0;
}
