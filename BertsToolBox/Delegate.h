#ifndef _Delegate_h
#define _Delegate_h
#include "Message.h"

//////////////////////////////////
// Message DELEGATE
///////////////////////////////////

class Delegate {
public:
  virtual bool invoke(Message*)=0;
  virtual ~Delegate(){}
protected:
  Delegate(){}
}; 

class NonTypeDelegate : public Delegate  
{
public:
  NonTypeDelegate(bool (*pfn)(Message*)):
  m_pfn(pfn)
  {
  }
  
  bool invoke(Message* evt)
  {
    return m_pfn(evt);
  }
  
  virtual ~NonTypeDelegate(){}
private:
  bool (*m_pfn)(Message*);
};


template <typename T>
class TypeDelegate : public Delegate  
{
public:
  TypeDelegate(T &t, bool (T::*pfn)(Message*)):
  m_t(t),
  m_pfn(pfn)
  {
    
  }

  bool invoke(Message* evt)
  {
    return (m_t.*m_pfn)(evt);
  }

  ~TypeDelegate(){}
  
private:
  T& m_t;
  bool (T::*m_pfn)(Message*);
};

#endif