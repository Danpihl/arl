#include "apps/new_logging_test/some_functions.h"
#include "arl/utilities/logging.h"

std::thread *ext_thread0;
std::thread *ext_thread1;
std::thread *ext_thread2;

void bee_threadfunction0()
{
    for (size_t k = 0; k < NUM_ITERATIONS; k++)
    {
        LOG_TRACE() << "threadFunction1: " << k;
    }
}

void bee_threadfunction1()
{
    for (size_t k = 0; k < NUM_ITERATIONS; k++)
    {
        LOG_FATAL() << "threadFunction1: " << k;
    }
}

void bee_threadfunction2()
{
    for (size_t k = 0; k < NUM_ITERATIONS; k++)
    {
        LOG_INFO() << "threadFunction1: " << k;
    }
}

void function0()
{
    ext_thread0 = new std::thread(bee_threadfunction0);
    ext_thread2 = new std::thread(bee_threadfunction2);
}

void function1()
{
    ext_thread1 = new std::thread(bee_threadfunction1);
}
