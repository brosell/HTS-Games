#ifndef Random_h
#define Random_h

#include <stdlib.h>
#include <time.h>

long random_seed = 0;
long random_count = 0;

inline 
void random_init()
{
  random_seed = time(0);
  srand(random_seed);
  random_count = 0;
}

inline
int random_next()
{
  random_count++;
  return rand();
}

inline
int random_next(int max)
{
  return random_next()%max;
}

inline
int random_next(int min, int max)
{
  return random_next(max-min)+min;
}

inline
void random_init(long seed, long count)
{
  random_seed = seed;
  srand(random_seed);
  while (random_count < count)
  {
    random_next();
  }
}


#endif