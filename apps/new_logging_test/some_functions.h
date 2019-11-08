#ifndef SOME_FUNCTIONS_H_
#define SOME_FUNCTIONS_H_

#include <thread>

void function0();
void function1();

#define NUM_ITERATIONS 3

extern std::thread *ext_thread0;
extern std::thread *ext_thread1;
extern std::thread *ext_thread2;

#endif
