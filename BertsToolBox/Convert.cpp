#include "Convert.h"

char ___buf[255];

std::string toString(int i)
{
  sprintf(___buf, "%d", i);
  return std::string(___buf);
}
