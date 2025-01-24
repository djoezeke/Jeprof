#include <iostream>
#include <unistd.h>
#include "Instrumentor.h"

#define USE_TIMEIT 1

#if USE_TIMEIT
#  define TIMEIT() InstrumentationTimer timer(__FUNCTION__);
#else
#  define TIMEIT()
#endif

void a()
{
    TIMEIT()
    usleep(50000);
}

void b()
{
    TIMEIT()
    usleep(50000);
}

void f1() {
    TIMEIT()
    usleep(200000);
    a();
}

void f2() {
    TIMEIT()
    usleep(200000);
    b();
}

void f3() {
    TIMEIT()
    usleep(200000);
    a();
    b();
}

int main()
{
    Instrumentor::Get().BeginSession("test-main");

    std::vector<std::thread> workers;

    workers.push_back(std::thread(f1));
    workers.push_back(std::thread(f2));
    workers.push_back(std::thread(f3));

    for (auto& w : workers)
    {
        w.join();
    }

    Instrumentor::Get().EndSession();

    return 0;
}

