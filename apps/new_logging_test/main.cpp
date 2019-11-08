#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>

#include "arl/utilities/logging.h"
#include "apps/new_logging_test/some_functions.h"

void threadFunction0()
{
    for (size_t k = 0; k < NUM_ITERATIONS; k++)
    {
        LOG_DEBUG() << "threadFunction0: " << k;
    }
}

void threadFunction1()
{
    for (size_t k = 0; k < NUM_ITERATIONS; k++)
    {
        LOG_WARNING() << "threadFunction1: " << k;
    }
}

void threadFunction2()
{
    for (size_t k = 0; k < NUM_ITERATIONS; k++)
    {
        LOG_ERROR() << "threadFunction2: " << k;
    }
}

int main()
{
    std::thread thread0(threadFunction0);
    std::thread thread1(threadFunction1);
    std::thread thread2(threadFunction2);

    function0();
    function1();
    ext_thread0->join();
    ext_thread1->join();
    ext_thread2->join();

    thread0.join();
    thread1.join();
    thread2.join();

    arl::logging::showFile(true);
    arl::logging::showFunction(true);
    arl::logging::showLineNumber(true);
    arl::logging::showThreadId(true);

    std::cout << std::endl
              << std::endl;

    std::cout << "Before" << std::endl;

    LOG_INFO() << "INFO: "
               << "Some str and num: " << 3.2;
    LOG_DEBUG() << "DEBUG: "
                << "Some str and num: " << 3.2;
    LOG_WARNING() << "WARNING: "
                  << "Some str and num: " << 3.2;
    LOG_TRACE() << "TRACE: "
                << "Some str and num: " << 3.2;
    LOG_ERROR() << "ERROR: "
                << "Some str and num: " << 3.2;
    LOG_FATAL() << "FATAL: "
                << "Some str and num: " << 3.2;
    PRINT() << "PRINT: "
            << "Some str and num: " << 3.2;
    LOG() << "LOG: "
          << "Some str and num: " << 3.2;
    std::cout << "After";

    std::cout << std::endl
              << std::endl;

    ASSERT(true) << "Assertion message";
    // EXIT() << "Exit message";

    PRINT() << "Some more printout";

    TIC();

    usleep(523);
    TOC_MS();

    TIC();

    usleep(437);
    TOC_US();
    std::cout << std::endl
              << std::endl;

    return 0;
}
