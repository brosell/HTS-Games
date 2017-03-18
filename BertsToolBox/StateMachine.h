#ifndef StateMachine_h
#define StateMachine_h

#pragma warning (disable:4786)

#include <string>
#include <map>
#include <assert.h>
using std::string;
using std::map;


/** the StateEvent def */
enum 
{
  NON_EVENT = 0,
  USER_STATE_EVENT = 1
};

typedef int StateEvent;

/**
  State class (abstract)
  */
template <typename ContextType = void*, typename MessageType = void*>
class State
{
public:
  virtual StateEvent enterState(ContextType smc) { return 0; }
  virtual StateEvent processMessage(ContextType smc, MessageType msg) = 0;
  virtual void exitState(ContextType smc) { return; }
};


/**
  The StateMachine class
*/
template <typename ContextType = void*, typename MessageType = void*>
class StateMachine: public map<State<ContextType, MessageType>*, map<StateEvent, State<ContextType, MessageType>* > >
{
public:
  StateMachine(ContextType context): m_context(context) { }
  ~StateMachine() {};

  /**
	 * initializes the state machine and starts the first state.
	 */
	void start()
  {
    m_currentState=(*this)[0][0];
    assert (m_currentState != 0);
    initCurrentState();
  }

  /**
	 * initializes the current state.  if the initialization causes the state
	 * to change, then the state will change.  This method will not return
	 * until the state(s) have settled down.
	 */
	void initCurrentState()
  {
    StateEvent event;
    do
    {
      event=m_currentState->enterState(m_context);
      if (event!=NON_EVENT)
      {
        m_currentState->exitState(m_context);
        m_currentState = (*this)[m_currentState][event];
      }
    }while (event!=NON_EVENT);
  }

  State<ContextType, MessageType>* getCurrentState() { return m_currentState; }

  /**
	 * allows the outside world to pass in messages that affect the States. 
	 * The message will be passed as is to the current state object.
	 * 
	 * @param msg a implementation define massage
	 * @return true if the state machine is still running, false if the state machine is not or is no longer running.
	 */
  bool processMessage(MessageType msg)
  {
    if (m_currentState == 0)
    {
      return false;
    }
    
    StateEvent event=m_currentState->processMessage(m_context, msg);
    if (event != NON_EVENT)
    {
      m_currentState->exitState(m_context);
      m_currentState=(*this)[m_currentState][event];
      if (m_currentState == 0)
      {
        return false;
      }
      initCurrentState();
    }
    return true;
  }

protected:
  ContextType m_context;
private:
  State<ContextType, MessageType>* m_currentState;
};

#endif

