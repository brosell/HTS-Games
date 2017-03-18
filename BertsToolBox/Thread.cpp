/*
Portions of the file are from the JThread package by Jori Liesenborgs
original copyright:
    This file is a part of the JThread package, which contains some object-
    oriented thread wrappers for different thread implementations.

    Copyright (c) 2000-2001  Jori Liesenborgs (jori@lumumba.luc.ac.be)

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.

The remainder is copyright (c) 2002 Bert Rosell
*/

#pragma warning (disable: 4786)

#include "Thread.h"
#include <map>
#include <iostream>
#include <assert.h>
using namespace std;

struct ThreadRep
{
  ThreadRep():handle(0), running(false), fn(0), arg(0) {}
  int handle;
  bool running;
  Thread_threadFn* fn;
  void* arg;
};

map<int, ThreadRep*> _threads;
Mutex _mapMutex;


DWORD WINAPI threadStart(LPVOID lpParameter);

int thread_create(Thread_threadFn* fn, void* arg)
{
  ThreadRep* tr=new ThreadRep;
  tr->fn=fn;
  tr->arg=arg;
  tr->handle=(int)CreateThread(0,0,threadStart, tr, 0, 0);
  _threads[tr->handle]=tr;
  while(tr->running == false) Sleep(1);
  return tr->handle;
}

DWORD WINAPI threadStart(LPVOID lpParameter)
{
  ThreadRep* tr=(ThreadRep*)lpParameter;
  tr->running=true;
  tr->fn(tr->arg);
  tr->running=false;
  return 0;
}


bool thread_anyRunning()
{
  synchronized(_mapMutex);
  map<int, ThreadRep*>::iterator pair;
  for (pair=_threads.begin(); pair!=_threads.end(); pair++)
  {
    if(pair!=_threads.end())
    {
      if (pair->second->running)
      {
        return true;
      }
    }
  }
  return false;
}

bool thread_isRunning(int handle)
{
  map<int, ThreadRep*>::iterator pair;
  pair=_threads.find(handle);
  if(pair!=_threads.end())
  {
    if (pair->second->running)
    {
      return true;
    }
  }
  return false;
}

void thread_release(int handle)
{
  // assert (skThread_isRunning(handle) == false)
  map<int, ThreadRep*>::iterator pair;
  pair=_threads.find(handle);
  if(pair!=_threads.end())
  {
    delete pair->second;
    _threads.erase(pair);
  }
}

static class ski_staticThreader
{
public:
  ~ski_staticThreader()
  {
    cout << "waiting for threads to finish" << endl;
    while (thread_anyRunning())
    {
      Sleep(1);
    }
  }
} waitForThreads;






void testthread1(void* arg);
static Mutex _mutex;
static unsigned long _total=0;

void testthread1(void* arg)
{
  _mutex.lock();
  cout << "thread: " << (int)arg << " started" << endl;
  _mutex.unlock();
  for (int x=0; x < 10; x++)
  {
    _mutex.lock();
    _total+=x;
    cout << "thread: " << (int)arg << ": " << x << endl;
    _mutex.unlock();
  }
  _mutex.lock();
  cout << "thread: " << (int)arg << " ended" << endl;
  _mutex.unlock();
}

void testthread2(void* arg);
void testthread2(void* arg)
{
  synchronized(_mutex);
  cout << "thread: " << (int)arg << " started" << endl;
  for (int x=0; x < 10; x++)
  {
    _total+=x;
    cout << "thread: " << (int)arg << ": " << x << endl;
  }
  cout << "thread: " << (int)arg << " ended" << endl;
  _mutex.unlock();
}

void testthread3(void* arg);
void testthread3(void* arg)
{
  
  for (int x=0; x<999; x++)
  {
    Sleep(1);
    synchronized(_mutex);

  }
}


bool testThreads()
{
  thread_create(testthread1, (void*)1);
  thread_create(testthread1, (void*)2);
  thread_create(testthread1, (void*)3);
  thread_create(testthread1, (void*)4);
  thread_create(testthread1, (void*)5);
  thread_create(testthread1, (void*)6);
  thread_create(testthread1, (void*)7);
  thread_create(testthread1, (void*)8);
  
  while (thread_anyRunning())
  {
    Sleep(1);
  }
  cout << "all Done!" << endl;
  assert(_total == 8*(0+1+2+3+4+5+6+7+8+9));

  _total=0;
  thread_create(testthread2, (void*)1);
  thread_create(testthread2, (void*)2);
  thread_create(testthread2, (void*)3);
  thread_create(testthread2, (void*)4);
  thread_create(testthread2, (void*)5);
  thread_create(testthread2, (void*)6);
  thread_create(testthread2, (void*)7);
  thread_create(testthread2, (void*)8);
  
  while (thread_anyRunning())
  {
    Sleep(1);
  }
  cout << "all Done!" << endl;
  assert(_total == 8*(0+1+2+3+4+5+6+7+8+9));

  cout << "anoying thread starting" << endl;
  thread_create(testthread3, 0);

  return true; 
}