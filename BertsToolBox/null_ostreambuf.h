#ifndef null_ostreambuf_h
#define null_ostreambuf_h
#include <iostream>

namespace hts
{
  /** eats all output */
  template <typename charT, typename traits = std::char_traits<charT> >
  class null_ostreambuf: public std::basic_streambuf<charT, traits>
  {
  public:
  protected:
    virtual int_type overflow(int_type c)
    {
      return traits::not_eof(c);
    }
  };
}
#endif