#include <iterator>

//template <typename Cont>
//class back_insert_iterator: public std::iterator<std::output_iterator_tag, void, void>
//{
//  public:
//    back_insert_iterator(Cont &c): m_c(&c) 
//    {
//    }
//    
//    back_insert_iterator& operator =( const typename Cont::value_type &v)
//    {
//      m_c->push_back(v);
//      return *this;
//    }
//    
//    back_insert_iterator& operator *()
//    {
//      return *this;
//    }
//    
//    back_insert_iterator& operator ++()
//    {
//      return *this;
//    }
//    
//    back_insert_iterator& operator ++(int)
//    {
//      return *this;
//    }
//
//  private:
//    Cont* m_c;
//};
//
//template <typename Cont> 
//back_insert_iterator<Cont> back_inserter(Cont& c)
//{
//  return back_insert_iterator<Cont>(c);
//}

template <typename Out1, typename Out2>
class MultiOut: public std::iterator<std::output_iterator_tag, typename std::iterator_traits<Out1>::value_type, void>
{
  public:
    MultiOut(Out1 o1, Out2 o2 ): m_o1(o1), m_o2(o2)
    {
    }
    
    MultiOut& operator =( const value_type &v)
    {
      *m_o1=v;
      *m_o2=v;
      return *this;
    }
    
    MultiOut& operator *()
    {
      return *this;
    }
    
    MultiOut& operator ++()
    {
      m_o1++;
      m_o2++;
      return *this;
    }
    
    MultiOut& operator ++(int)
    {
      MultiOut tmp(*this); 
      ++*this; 
      return tmp;
    }

  private:
    Out1 m_o1;
    Out2 m_o2;
};

template <typename Out1, typename Out2> 
MultiOut<Out1, Out2> multiOut(Out1 o1, Out2 o2)
{
  return MultiOut<Out1, Out2>(o1, o2);
}
