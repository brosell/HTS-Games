#ifndef STLFunctorDelegate_h
#define STLFunctorDelegate_h

#include <functional>
namespace hts
{
  template <typename DelegateType, typename ThingType, typename ReturnType>
    class STLFunctorUnaryDelegate : public std::unary_function<ThingType, ReturnType>
  {
public:
  STLFunctorUnaryDelegate(DelegateType &t, ReturnType (DelegateType::*pfn)(ThingType)):
      m_t(t),
        m_pfn(pfn)
      {
        
      }
      
      ReturnType operator()(ThingType thing)
      {
        return (m_t.*m_pfn)(thing);
      }
      
      ~STLFunctorUnaryDelegate(){}
      
private:
  DelegateType& m_t;
  ReturnType (DelegateType::*m_pfn)(ThingType);
  };
  
  template <typename DelegateType, typename ThingType>
    class STLVoidFunctorUnaryDelegate : public std::unary_function<ThingType, void>
  {
public:
  STLVoidFunctorUnaryDelegate(DelegateType &t, void (DelegateType::*pfn)(ThingType)):
      m_t(t),
        m_pfn(pfn)
      {
        
      }
      
      void operator()(ThingType thing)
      {
        (m_t.*m_pfn)(thing);
      }
      
      ~STLVoidFunctorUnaryDelegate(){}
      
private:
  DelegateType& m_t;
  void (DelegateType::*m_pfn)(ThingType);
  };
  
  
  template <typename DelegateType, typename ThingType1, typename ThingType2, typename ReturnType>
    class STLFunctorBinaryDelegate : public std::binary_function<ThingType1, ThingType2, ReturnType>
  {
public:
  STLFunctorBinaryDelegate(DelegateType &t, ReturnType (DelegateType::*pfn)(ThingType1, ThingType2)):
      m_t(t),
        m_pfn(pfn)
      {
        
      }
      
      ReturnType operator()(ThingType1 thing1, ThingType2 thing2)
      {
        return (m_t.*m_pfn)(thing1, thing2);
      }
      
      ~STLFunctorBinaryDelegate(){}
      
private:
  DelegateType& m_t;
  ReturnType (DelegateType::*m_pfn)(ThingType1, ThingType2);
  };
  
  template <typename DelegateType, typename ThingType1, typename ThingType2>
    class STLVoidFunctorBinaryDelegate : public std::binary_function<ThingType1, ThingType2, void>
  {
public:
  STLVoidFunctorBinaryDelegate(DelegateType &t, void (DelegateType::*pfn)(ThingType1, ThingType2)):
      m_t(t),
        m_pfn(pfn)
      {
        
      }
      
      void operator()(ThingType1 thing1, ThingType2 thing2)
      {
        (m_t.*m_pfn)(thing1, thing2);
      }
      
      ~STLVoidFunctorBinaryDelegate(){}
      
private:
  DelegateType& m_t;
  void (DelegateType::*m_pfn)(ThingType1, ThingType2);
  };
}
#endif