/*
AutoBuffer:
  a linked list of arrays og typename Kind buffers.  Acts as a FIFO. When data is appended, and if it would 
  overun the final buffer, a new bufer will be alloc'd and added to the list.
  When data is read, An offset ptr will move to the next byte to be read.  If it moves
  past the boundry of the first buffer, that buffer will be removed and added to the end.
  This buffer will grow but never shrink (unless told to in a controlled manner or at some threshhold), 
  it will only grow as big as the largest ever unread chuck of data.  If at some point there is 40k of
  data, even when all is read, there will be 40k alloc'd.
  */


#ifndef _AutoBuffer_h_
#define _AutoBuffer_h_

#pragma warning (disable:4786)

#include <list>
using namespace std;
#include <assert.h>
#include <iostream>
#include <algorithm>

#define MIN(x, y) ((x<y)?x:y)
#define MAX(x, y) ((x>y)?x:y)
//#define assert(x) 
template <typename Kind>
class AutoBuffer
{
public:
  typedef Kind kind;
  /* Input:
        blockSize - the size of the arrays of Kind's to use.  
          large values mean less calls to "new" but more memory allocated (faster)
          small values will use less memory but will spend more time calling "new" (smaller)
        hardLimit - the maximum number of blocks allowed.  When this value is exceded, calls 
          to write will sstart to fail (gracefully)
  */
  AutoBuffer(size_t blockSize=256, size_t hardLimit=-1);
  ~AutoBuffer();

  bool hasDataAvailable()
  {
    return !(m_readBlock == m_writeBlock && m_readOffset >= m_writeOffset);
  }

  /*
  write(Kind* aBuffer, size_t aCount)
    Writes up to aCount Kind's to the buffer.
  
    Input:
      aBuffer - a pointer to an array of Kind.
      aCount - the maximum number of Kind's to write

    Returns the number of Kind's written
  */
  int write(const Kind* aBuffer, size_t aCount);
  
  /*
    read(Kind* aBuffer, size_t aCount)
      Reads from buffer up to aCount to an array poited to by aBuffer.
      Once data if read, it is gone and the memory will to be reused
      when appropriate.

    Input:
      aBuffer - a pointer to an array of Kind.  If NULL, then buffer is
                read, but thrown away.
      aCount - the maximum number of Kind's to read

    Returns the number of Kind's read
  */
  int read(Kind* aBuffer, size_t aCount);
  
  void push_back(const Kind& aKind)
  {
/*    if (m_writeOffset >= m_blockSize)
    {
      if(!newWriteBlock())
      {
        return;
      }
    }
    (*m_writeBlock)[m_writeOffset]=aKind;
    m_count++;
    m_writeOffset++;
*/
    write(&aKind, 1);
  }
  
  void pop_front()
  {
    read((Kind*)0, 1);
  }

  Kind& front()
  {
    Kind* pK = (*m_readBlock);
    return pK[m_readOffset];
  }

  Kind& back()
  {
    Kind* pK = (*m_writeBlock);
    return pK[m_writeOffset-1];
  }

  void setShrinkTo(size_t sz) {m_shrinkTo = sz; }  
  void shrink();
  
  void report(const char* title);
  int size() { return m_count; } /* returns the the number of Kind's currently stored */
  int capacity() { return m_list.size()*m_blockSize;}/* returns the current capacity */

  size_t getAverage()
  {
    if (m_averageCounter == 0) return 0;
    return (m_averageSize/m_averageCounter);
  }

  void setAutoShrinkTo(bool s) { m_autoShrinkTo=s;}

protected:
  void doStats()
  {
    m_averageSize+=m_list.size();
    m_averageCounter++;
    m_recordSize=MAX(m_recordSize, size());
    m_recordCapacity=MAX(m_recordCapacity, capacity());
    m_recordListSize=MAX(m_recordListSize, m_list.size());

    if (m_autoShrinkTo)
    {
      setShrinkTo(getAverage());
    }

  }

  void init()
  {
    m_list.push_back(makeBlock());
    m_writeBlock=m_readBlock=m_list.begin();
  }

  void moveFirstToLast()
  {
    assert(m_readBlock != m_writeBlock); // hmmmm.  we should never have been able to read past this block
    if (m_shrinkTo >= 0 && m_list.size() > m_shrinkTo)
    {
      delete [] *m_readBlock;
    }
    else
    {
      m_list.push_back( *m_readBlock );      
    }
    m_list.pop_front();
    m_readBlock = m_list.begin();
    m_readOffset = 0;
  }

  bool newWriteBlock();
  
  Kind* makeBlock()
  {
    return (new Kind[m_blockSize]);
  }


private:
  unsigned long m_averageSize;
  unsigned long m_averageCounter;
  size_t m_recordCapacity;
  size_t m_recordSize;
  size_t m_recordListSize;

  size_t m_shrinkTo;
  bool m_autoShrinkTo;
  const size_t m_blockSize;
  const size_t m_hardLimit;
  list<Kind*>::iterator m_readBlock;
  list<Kind*>::iterator m_writeBlock;
  size_t m_readOffset;
  size_t m_writeOffset;
  size_t m_count;
  list<Kind*> m_list;
};


template <typename Kind>
AutoBuffer<Kind>::AutoBuffer(size_t blockSize, size_t hardLimit): 
m_blockSize(blockSize), m_hardLimit(hardLimit), m_shrinkTo(-1),
m_readOffset(0), m_writeOffset(0), m_readBlock(0), m_writeBlock(0),
m_count(0), m_averageSize(0), m_averageCounter(0), m_autoShrinkTo(false),
m_recordCapacity(0), m_recordSize(0), m_recordListSize(0)
{
  init();
}


template <typename Kind>
AutoBuffer<Kind>::~AutoBuffer()
{
  list<Kind*>::iterator k;
  for (k=m_list.begin(); k!=m_list.end(); k++)
  {
    delete [] (*k);
  }
  m_list.clear();
}

inline
char* copy(char* begin, char* end, char* dest)
{
  memcpy(dest, begin, (end - begin));
  return (dest+(end - begin)); 
}


/* returns number written which may be smaller but never bigger 
than aCount (unless hardLimit is -1, then alway return aCount

  two scenarios:
  1) aCount is same size or smaller than ((m_blockSize) - m_writeOffset) - copy buffer and move the m_writeOffset+=aCount
  2) aCount is larger than ((m_blockSize) - m_writeOffset) - copy what will fit, create new block recurse
  */

template <typename Kind>
int AutoBuffer<Kind>::write(const Kind* aBuffer, size_t aCount)
{
  assert(aCount > 0);
  assert(aBuffer != 0);
  
  size_t added = 0;

  size_t toBeWritten=aCount;
  const Kind* pBuffer=aBuffer;

  while (toBeWritten > 0)
  {
    Kind* pK= *m_writeBlock;
    if (m_writeOffset+toBeWritten > m_blockSize)
    {
      size_t maxNum=((m_blockSize) - m_writeOffset);
      copy(pBuffer, pBuffer+maxNum, &(pK[m_writeOffset]));
      m_writeOffset+=maxNum;
      pBuffer+=maxNum;
      toBeWritten-=maxNum;
      if(!newWriteBlock())
      {
        break;
      }
    }
    else
    {
      // fits;
      copy(pBuffer, pBuffer+toBeWritten, &(pK[m_writeOffset]));
      m_writeOffset+=toBeWritten;
      pBuffer+=toBeWritten;
      break; // quicker
    } // if
  } //while
//  doStats();
  m_count+=(pBuffer - aBuffer);
  return (pBuffer - aBuffer);
}


template <typename Kind>
int AutoBuffer<Kind>::read(Kind* aBuffer, size_t aCount)
{
/* returns number actually read which may be smaller but never bigger than aCount

  senarios:
  1) aCount < ((m_blockSize) - m_readOffset) - copy data to aBuffer
  2) aCount == ((m_blockSize) - m_readOffset) - copy data and move block to end of list
  3) aCount > ((m_blockSize) - m_readOffset) - copy available data, move block to end, recurse the remainder
  4) aCount > amount of available data - copy available.
  5) there is no data
  */
  if (m_readBlock == m_writeBlock && m_readOffset >= m_writeOffset) // this takes care of (5)
  {
    return 0;
  }

  doStats();
  
  size_t wanted=aCount;
  size_t bufferOffset=0;
  size_t numRead=0;
  
  bool dataAvailable = !(m_readBlock == m_writeBlock && m_readOffset >= m_writeOffset);
  while (dataAvailable && wanted>0)
  {
    if (m_readOffset == m_blockSize)
    {
      moveFirstToLast();
    }
    
    size_t dataInCurrentBlock;
    if (m_readBlock == m_writeBlock)
    {
      dataInCurrentBlock = m_writeOffset - m_readOffset;
    }
    else
    {
      dataInCurrentBlock = m_blockSize - m_readOffset;
    }
    size_t toRead = MIN(dataInCurrentBlock, wanted);
    
    Kind* pK = (*m_readBlock);
    
    if (aBuffer != 0)
    {
      copy(&(pK[m_readOffset]), &(pK[m_readOffset+toRead]), &(aBuffer[bufferOffset]));
    }
    
    wanted-=toRead;
    //m_count-=toRead;
    m_readOffset+=toRead;
    numRead+=toRead;
    bufferOffset+=toRead;
    
    dataAvailable = !(m_readBlock == m_writeBlock && m_readOffset >= m_writeOffset);
  } // while
  m_count-=numRead;
  return numRead;
}

template <typename Kind>
bool AutoBuffer<Kind>::newWriteBlock()
{
  if (m_hardLimit != -1 && m_list.size() >= m_hardLimit)
  {
    return false;
  }
  list<Kind*>::iterator tmp=m_writeBlock;
  tmp++;
  if ( (tmp) == m_list.end())
  {
    //need a block
    Kind* pK=makeBlock();
    m_list.push_back(pK);
    m_writeBlock++;
    m_writeOffset=0;
    
    /* the following assert makes sure that the current iterator 
    equals the just new'd block.  If it doesn't then m_list was
    changed out from under us.  perhaps another thread?
    */
    assert( (*m_writeBlock) == pK); 
  }
  else
  {
    // we have an unused block
    m_writeBlock++;
    m_writeOffset=0;
  }
  return true;
}

template <typename Kind>
void AutoBuffer<Kind>::shrink()
{
  while(true)
  {
    list<Kind*>::iterator tmp=m_writeBlock;
    tmp++;
    if (tmp != m_list.end())
    {
      delete [] (m_list.back());
      m_list.pop_back();
    }
    else
    {
      break;
    }
  }
  
}

template <typename Kind>
void AutoBuffer<Kind>::report(const char* title)
{
  cout << endl << title << endl << "--------------------" << endl;
  cout << "m_blockSize    : " << m_blockSize << endl;
  cout << "m_hardLimit    : " << (long)m_hardLimit << endl;
  cout << "m_list.size()/record/average : " << m_list.size() << "/" << m_recordListSize << "/" << getAverage() << endl;
  cout << "size/record    : " << size() << "/" << m_recordSize << endl;
  cout << "ShrinkToValue   : " << (long)m_shrinkTo << endl;
  cout << "capacity/record: " << capacity() << "/" << m_recordCapacity << endl;
  cout  << "--------------------" << endl << endl;
}

#endif