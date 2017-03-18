#ifndef _ThinkDelegate_h
#define _ThinkDelegate_h


class ThinkDelegate {
public:
  virtual void invoke()=0;
  virtual ~ThinkDelegate();
protected:
  ThinkDelegate(){}
}; 

class NonTypeThinkDelegate : public ThinkDelegate  
{
public:
  NonTypeThinkDelegate(void (*pfn)()):
  m_pfn(pfn)
  {
  }
  
  virtual void invoke()
  {
    m_pfn();
  }
  
  virtual ~NonTypeThinkDelegate(){}
private:
  void (*m_pfn)();
};


template <typename T>
class TypeThinkDelegate : public ThinkDelegate  
{
public:
  TypeThinkDelegate(T &t, void (T::*pfn)()):
  m_t(t),
  m_pfn(pfn)
  {
    
  }

  virtual void invoke()
  {
    (m_t.*m_pfn)();
  }

  ~TypeThinkDelegate(){}
  
private:
  T& m_t;
  void (T::*m_pfn)();
};

#endif
