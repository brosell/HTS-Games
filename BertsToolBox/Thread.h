#ifndef _BR_Thread_h
#define _BR_Thread_h

#include <windows.h>
#include "Mutex.h"

typedef void (Thread_threadFn) (void * arg);

int thread_create(Thread_threadFn* fn, void* arg=0);
bool thread_isRunning(int handle);
bool thread_anyRunning();
void thread_lock(int handle);

#endif
