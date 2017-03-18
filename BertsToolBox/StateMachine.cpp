#include "StateMachine.h"

#if 0

#include <assert.h>

class MyContext
{
public:
  MyContext(): i1(0), i2(0) {}
  int i1;
  int i2;
};

typedef State<MyContext*, int> StateDef;
typedef StateMachine<MyContext*, int> StateMachineDef;


class State1: public StateDef
{
public:
  virtual StateEvent processMessage(MyContext* smc, int msg)
  {
    if (msg == 1)
    {
      return 1;
    }
    if (msg == 3)
    {
      return 3;
    }
    smc->i1 = msg;
    return 0;
  }
};

class State2: public StateDef
{
public:
  virtual StateEvent processMessage(MyContext* smc, int msg)
  {
    if (msg == 2)
    {
      return 2;
    }
    if (msg == 3)
    {
      return 3;
    }
    smc->i2 = msg;
    return 0;
  }
};


int main(int c, char** v)
{
  MyContext myContext;
  StateMachineDef sm(&myContext);
  StateDef* s1 = new State1;
  StateDef* s2 = new State2;

  sm[0][0] = s1;
  sm[s1][1] = s2;
  sm[s1][3] = 0; // end it
  sm[s2][2] = s1;
  sm[s2][3] = 0; // end it

  sm.start();

  assert(sm.getCurrentState() == s1);

  sm.processMessage(4);
  assert(sm.getCurrentState() == s1);
  assert(myContext.i1 == 4);

  sm.processMessage(1);
  assert(sm.getCurrentState() == s2);
  assert(myContext.i1 == 4);

  sm.processMessage(7);
  assert(sm.getCurrentState() == s2);
  assert(myContext.i1 == 4);
  assert(myContext.i2 == 7);

  sm.processMessage(2);
  assert(sm.getCurrentState() == s1);
  assert(myContext.i1 == 4);
  assert(myContext.i2 == 7);

  sm.processMessage(16);
  assert(sm.getCurrentState() == s1);
  assert(myContext.i1 == 16);
  assert(myContext.i2 == 7);

  sm.processMessage(3);
  assert(sm.getCurrentState() == 0);
  assert(myContext.i1 == 16);
  assert(myContext.i2 == 7);


  return 0;
}


#endif