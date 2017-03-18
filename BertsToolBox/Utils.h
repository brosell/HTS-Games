#ifndef Utils_h
#define Utils_h

#include <functional>

#define SAFE_DELETE(p) if (p) delete (p); (p) = 0;
#define SAFE_DELETE_ARRAY(p) if (p) delete [] (p); (p) = 0;

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#include <iterator>
using namespace std;

namespace hts
{
  template<typename T> T min(T one, T two) { return (std::less<T>()(one, two)?one:two); }
  
  template<typename T> T max(T one, T two) { return (std::less<T>()(two, one)?one:two); }

  class Noncopyable
  {
  protected:
    Noncopyable() {}
    ~Noncopyable() {}
  private:  // emphasize the following members are private
    Noncopyable( const Noncopyable& );
    const Noncopyable& operator=( const Noncopyable& );
  };
  
  template<typename InputIterator, typename OutputIterator, typename Predicate>
    OutputIterator copy_if(InputIterator begin, InputIterator end, OutputIterator destBegin, Predicate p)
  {
    while (begin != end)
    {
      if (p(*begin)) *destBegin++ = *begin;
      ++begin;
    }
    return destBegin;
  }
  
  class Delete
  {
  public:
    template<typename T>
      void operator()(T*& ptr)
    {
      delete ptr;
      ptr = 0;
    }
  };

  template<typename T>
    void SafeDelete(T*& ptr)
  {
    if (ptr != 0)
    {
      delete ptr;
      ptr = 0;
    }
  }

  template <typename T>
  struct average
  {
    average(): m_num(0), m_tot(0) {}
    void operator()(T t)
    {
      m_num++;
      m_tot+=t;
    }
    operator T() { return m_tot/m_num; }
  private:
    size_t m_num;
    T m_tot;
  };

  template <typename ForwardIterator, typename ValType>
  pair<ForwardIterator, ForwardIterator> getInclusive(ForwardIterator begin, ForwardIterator end, ValType low, ValType high)
  {
    return getInclusive(begin, end, low, high, std::less<ValType>());
  }

  template <typename ForwardIterator, typename ValType, typename Pred>
  pair<ForwardIterator, ForwardIterator> getInclusive(ForwardIterator begin, ForwardIterator end, ValType low, ValType high, Pred pred)
  {
    if (pred(high, low)) swap(low, high);
    pair<ForwardIterator, ForwardIterator> ret;
    ret.first = std::lower_bound(begin, end, low, pred);
    ret.second = std::upper_bound(begin, end, high, pred);
    return ret;
  }

  template <typename ForwardIterator, typename ValType>
  pair<ForwardIterator, ForwardIterator> getRange(ForwardIterator begin, ForwardIterator end, ValType low, ValType high)
  {
    return getRange(begin, end, low, high, std::less<ValType>());
  }
  
  template <typename ForwardIterator, typename ValType, typename Pred>
  pair<ForwardIterator, ForwardIterator> getRange(ForwardIterator begin, ForwardIterator end, ValType low, ValType high, Pred pred)
  {
    if (pred(high, low)) swap(low, high);
    pair<ForwardIterator, ForwardIterator> ret;
    ret.first = std::lower_bound(begin, end, low, pred);
    ret.second = std::lower_bound(begin, end, high, pred);
    return ret;
  }

  template <typename ForwardIterator, typename ValType>
  pair<ForwardIterator, ForwardIterator> getExclusive(ForwardIterator begin, ForwardIterator end, ValType low, ValType high)
  {
    return getExclusive(begin, end, low, high, std::less<ValType>());
  }

  template <typename ForwardIterator, typename ValType, typename Pred>
  pair<ForwardIterator, ForwardIterator> getExclusive(ForwardIterator begin, ForwardIterator end, ValType low, ValType high, Pred pred)
  {
    if (pred(high, low)) swap(low, high);
    pair<ForwardIterator, ForwardIterator> ret;
    if (low == high)
    {
      ret.first = end;
      ret.second = end;
    }
    else
    {
      ret.first = std::upper_bound(begin, end, low, pred);
      ret.second = std::lower_bound(begin, end, high, pred);
    }
    return ret;
  }
};
#endif
