#include "AutoBuffer.h"



bool testAutoBuffer()
{
  AutoBuffer<char> buf(3); // buffer with each block being 3 bytes big

  buf.push_back('q');
  
  assert(buf.front() == 'q');
  assert(buf.back() == 'q');
  assert(buf.size() == 1);
  
  buf.push_back('w');
  
  assert(buf.front() == 'q');
  assert(buf.back() == 'w');
  assert(buf.size() == 2);

  char* x="abcdefghijklmnop";

  buf.write(x, 5);
  assert(buf.front() == 'q');
  assert(buf.back() == 'e');
  assert(buf.size() == 7);

  char y[26];
  memset(y, 0, 26);

  buf.read(y, 5);
  cout << buf.front() << endl;
  assert(buf.front() == 'd');
  assert(buf.back() == 'e');
  assert(buf.size() == 2);
  
  cout << buf.capacity() << endl;
  assert(buf.capacity() == 9);

  buf.shrink();
  cout << buf.capacity() << endl;
  assert(buf.capacity() == 6);

  AutoBuffer<char> buf2(3, 2); // only two blocks will be allocated through the life of this instance. so only 6 objects can be stored

  int w = buf2.write(x, 9);

  assert (w==6);
  assert (buf2.size() == 6);
  assert (buf2.capacity() == 6);
  assert (buf2.write(x, 9) == 0);
  
  {
    AutoBuffer<string> Strings(256);
    Strings.setShrinkTo(15);
    
    char it[10];
    while (Strings.size() < 0xffff)
    {
      Strings.push_back(string(itoa(Strings.size(), it, 10)));
    }
    cout << "averageBlockCount: " << Strings.getAverage() << endl;
    
    Strings.report("Holy Cow");
    while (Strings.size())
    {
      Strings.pop_front();
    }
    cout << "averageBlockCount: " << Strings.getAverage() << endl;
    Strings.report("2");
    Strings.shrink();
    Strings.report("3");

    cout << "averageBlockCount: " << Strings.getAverage() << endl;
  }

  
  {
    AutoBuffer<string> Strings(256);
    //Strings.setShrinkTo(15);
    
    char it[10];
    while (Strings.size() < 0xffff)
    {
      Strings.push_back(string(itoa(Strings.size(), it, 10)));
    }
    cout << "averageBlockCount: " << Strings.getAverage() << endl;
    
    Strings.report("Holy Cow");
    while (Strings.size())
    {
      Strings.pop_front();
    }
    cout << "averageBlockCount: " << Strings.getAverage() << endl;
    Strings.report("2");
    Strings.shrink();
    Strings.report("3");
    cout << "averageBlockCount: " << Strings.getAverage() << endl;
  }
  return true;
}




