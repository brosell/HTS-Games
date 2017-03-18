#ifndef nocase_compare_h
#define nocase_compare_h

#include <functional>
#include <algorithm>
#include <string>

namespace hts
{
  template <typename T>
  struct nocase_compare: public std::binary_function<T, T, bool>
  {
    bool operator()(T c1, T c2) const
    {
      return (toupper(c1) < toupper(c2));
    }
  };

  template <>
  struct nocase_compare<std::string>: public std::binary_function<std::string, std::string, bool>
  {
    bool operator()(std::string s1, std::string s2) const
    {
      return std::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), nocase_compare<char>());
    }
  };

  /** ignores case and the differnece between forward and back slashes */
  template <typename T>
  struct nocase_path_compare: public std::binary_function<T, T, bool>
  {
    bool operator()(T c1, T c2) const
    {
      return (toupper( (c1=='\\')?'/':c1) < toupper( (c2=='\\')?'/':c2));
    }
  };

  template <>
  struct nocase_path_compare<std::string>: public std::binary_function<std::string, std::string, bool>
  {
    bool operator()(std::string s1, std::string s2) const
    {
      return std::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), nocase_path_compare<char>());
    }
  };

}

#endif