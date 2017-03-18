#include "PakFile.h"
#include "stdlib.h"
//#include <unistd.h>
#include <iostream>

PakFile::PakFile(string pn, bool l)
{
  packName=pn;
  
  if(l)
  {
    load();
  }
}

void PakFile::load()
{
//  cout << "Loading" << endl;

  FILE* fd=fopen(packName.c_str(), "rb");
  if (!fd)
  {
    return;
  }

  char id[5]="xxxx";
  fread(id, 1, 4, fd);
  if (strcmp(id, "skpk") != 0)
  {
    fclose(fd);
    return;
  }

  unsigned long tmp;
  fread(&tmp, 1, 4, fd); // dir loc;
  dirLoc=NBULong::fromNetwork(tmp);

  fread(&tmp, 1, 4, fd); // dir size
  dirSize=NBULong::fromNetwork(tmp);

  fseek(fd, dirLoc, SEEK_SET);

  // FIXME: it is important to read the dir here!!!

  for(int x=0; x<dirSize/(128+4+4); x++)
  {
//    cout << "Loading # " << x << endl;
    char name[128];
    memset(name, 0, 128);
    
    unsigned long offset;//=i->getOffset().getNetworkVal();
    unsigned long length;//=i->getSize().getNetworkVal();

    fread(name, 1, 128, fd);
    fread(&offset, 1, 4, fd);
    fread(&length, 1, 4, fd);

    PakFileElement pfe;
    pfe.setName(name);
    pfe.setOffset(NBULong::fromNetwork(offset));
    pfe.setSize(NBULong::fromNetwork(length));

    m_filenames.push_back(name);

    //push_back(pfe);
    (*this)[name]=pfe;
  }

  fclose(fd);

}

#include <time.h>
int tmpnamii(char* temp);
int tmpnamii(char* temp)
{
  char* start=strstr(temp, "XXXXXX");
  if (!start)
    {
      return 0;
    }
  sprintf(start, "%x.tmp", clock());
  return 1;
}

bool PakFile::commit()
{
//  cout << "Committing" << endl;
  char tmpName[256]="pkXXXXXX";
  if (!tmpnamii(tmpName))
  {
//   cout << "tmp name no good" << endl;
   return false;
  }
  
//  cout << tmpName << endl;

  unsigned long curOffset=0;

  FILE* fd=fopen(tmpName, "wb");

    
  curOffset+=fwrite("skpk        ", 1, 12, fd); // header
  
  PakFile::iterator pair;

  for(pair=begin(); pair!=end(); pair++)
  {
    unsigned long startOffset=curOffset;
    curOffset+=copy(pair->second.getName().c_str(), fd);

    pair->second.setOffset(startOffset);
    pair->second.setSize(curOffset-startOffset);
  }

  // at this point diroffset = curOffset
  // and size = size() * (128+4+4)

  unsigned long dirOffset=NBULong::fromHost(curOffset).getNetworkVal();
  unsigned long dirSize=NBULong::fromHost(size()*(128+4+4)).getNetworkVal();

  // write directory
  for(pair=begin(); pair!=end(); pair++)
  {
    PakFileElement pfe = pair->second;
//    cout << " dir entry: " << pair->first << endl;
    char name[128];
    memset(name, 0, 128);
    if (pair->second.getLocation() == "")
    {
      strcpy(name, pfe.getName().c_str());
    }
    else
    {
      strcpy(name, pfe.getLocation().c_str());
    }

    unsigned long offset=pfe.getOffset().getNetworkVal();
    unsigned long length=pfe.getSize().getNetworkVal();

    fwrite(name, 1, 128, fd);
    fwrite(&offset, 1, 4, fd);
    fwrite(&length, 1, 4, fd);
  }

  // seek to begining and write out size and lkenght of directory
  fseek(fd, 4, SEEK_SET);

  fwrite(&dirOffset, 1, 4, fd);
  fwrite(&dirSize, 1, 4, fd);
  
  fclose(fd);

  unlink(packName.c_str());
//  cout << "trying to raname " << tmpName << " to " << packName << " ";
  int res = rename(tmpName, packName.c_str());
  return true;
}

unsigned long PakFile::copy(const char* filename, FILE* fd)
{
  FILE* in=fopen(filename, "rb");
  if (!in)
  {
    return 0;
  }

  unsigned long retSize=0;
  char buf[255];
  int count=0;

  while ( count=fread(buf, 1, 255, in) )
  {
    int c=fwrite(buf, 1, count, fd);
    retSize+=c;  // use c instead of count because there might be an error writing that we have to catch
  }

  fclose(in);
  return retSize;
}

bool PakFile::extract(PakFileElement elem) //, const char* whereTo)
{
  return extract(elem, elem.getLocation().c_str());
}

bool PakFile::extract(PakFileElement elem, const char* to)
{
  if (elem.getOffset()==0)
  {
    // never made to the pak file so we can't extract it
    return true;
  }

  // it is posable to get a zero size file

  FILE* pack=fopen(packName.c_str(), "rb");
  if (!pack)
  {
    return false;
  }

  FILE* out=fopen(to, "wb");
  if (!out)
  {
    fclose(pack);
    return false;
  }

  fseek(pack, elem.getOffset(), SEEK_SET);

  char buf[1];

  for (int x=0; x<elem.getSize(); x++)
  {
    // FIXME: one byte at a time is not very efficiant but I'll optimize later :)
    fread(buf, 1, 1, pack);
    fwrite(buf, 1, 1, out);
  }

  fclose(pack);
  fclose(out);
  return true;
}

bool PakFile::contains(string name)
{
  return (find(name) != end());
}

size_t PakFile::getSize(string name)
{
  if (contains(name))
  {
    return (*this)[name].getSize();
  }
  return 0;
}

FILE* PakFile::toFP(string name)
{
  if (!contains(name))
  {
    return 0;
  }

  PakFileElement elem = (*this)[name];  

  // it is posable to get a zero size file

  FILE* pack=fopen(packName.c_str(), "rb");
  if (!pack)
  {
    return 0;
  }

  fseek(pack, elem.getOffset(), SEEK_SET);

  return pack;
}

bool PakFile::toMemory(string name, void* destination)
{
  char* start = (char*)destination;
  char* to=(char*)destination;

  if (!contains(name))
  {
//    cout << "not found" << endl;
    return false;
  }

  PakFileElement elem = (*this)[name];  

  // it is posable to get a zero size file

  FILE* pack=fopen(packName.c_str(), "rb");
  if (!pack)
  {
    return false;
  }

  fseek(pack, elem.getOffset(), SEEK_SET);

  //char buf[1024];

  int read = 0;
  //while (read < elem.getSize())
  while (to < start+elem.getSize())
  {
    int leftToRead = elem.getSize()-read;
    int toRead = min(1024, elem.getSize()-read);
    int justRead = fread(to, 1, toRead, pack);
    if (justRead <= 0)
    {
      return false;
    }
    to+=justRead;
    read+=justRead;
  }

  fclose(pack);
  return true;
}
    

//using namespace std;
void PakFile::dump()
{
  PakFile::iterator pair;
  int count=0;
  for (pair=begin(); pair!=end(); pair++, count++)
  {
    PakFileElement pfe = pair->second;
//    cout << dec << count << ": " << pfe.getName() << " Offset: " << 
//      pfe.getOffset() << " Size: " << pfe.getSize() << endl;
  }
}

//void PakFile::extractAll()
//{
//  map<string, PakleFileElement>::iterator pair;
//  for (pair=begin(); pair!=end(); pair++)
//  {
//    PakFileElement pfe = pair->second;
//    pfe.setLocation(pfe.getName());
//    cout << "Extracting: " << pfe.getLocation() << endl;
//    extract(i);
//  }
//  
//}
