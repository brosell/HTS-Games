//#include "FilePackage.h"
#include <iostream.h>
#include <unistd.h>
//using namespace std;

//int main(int argc, char** argv)
//{
//  FilePackageWriter fp("c:\\daPack.skpck");
//  fp.addFile("c:\\test1.txt");
//  fp.addFile("c:\\test2.txt");
//
//  if (fp.compile())
//  {
//    cout << "YEAH!" << endl;
//  }
//  else
//  {
//    cout << "BOO" << endl;
//  }
//
//  FilePackageReader fr("c:\\daPack.skpck");
//  fr.listFiles();
//
//  return 0;
//}

#include "PakFile.h"

int main(int argc, char** argv)
{
  NBULong ul1=NBULong::fromHost(0x1234abcd);

  cout << hex << ul1.getHostVal() << " = " << ul1.getNetworkVal() << endl;

  NBULong ul2=NBULong::fromNetwork(ul1.getNetworkVal());
  
  cout << hex << ul2.getHostVal() << " = " << ul2.getNetworkVal() << endl;

  cout << hex << ul1 << endl << endl;



  PakFile pf("./testdir/test.pak", false);
  PakFileElement pfe;
  pfe.setLocation("./testdir/test1.txt");
  pfe.setName("test1.txt");
  pf.push_back(pfe);

  pfe.setLocation("./testdir/test2.txt");
  pfe.setName("test2.txt");
  pf.push_back(pfe);

  pfe.setLocation("./testdir/test3.txt");
  pfe.setName("test3.txt");
  pf.push_back(pfe);

  pfe.setLocation("./testdir/Beyond.zip");
  pfe.setName("beyond.zip");
  pf.push_back(pfe);

  cout << "Number added: " << pf.size() << endl;

  pf.commit();

  PakFile pfRead("./testdir/test.pak", true);
  pfRead.dump();
  pfe.setLocation("./testdir/test4.txt");
  pfe.setName("test4.txt");

  pfRead.push_back(pfe);

  pfRead.commit();

  pfRead.dump();
  
  pfRead.extractAll();

  unlink("test1.txt");
  unlink("test2.txt");
  unlink("test3.txt");
  unlink("test4.txt");
  unlink("Beyond.zip");

  for (Element i=pfRead.begin(); i!=pfRead.end(); i++)
  {
    if( strcmp(i->getName(), "test3.txt")==0)
    {
      cout << "********\nerasing " << i->getName() << endl;
      pfRead.erase(i);
      break;
    }
  }

  pfRead.dump();
  pfRead.extractAll();
  return 0;
}
