#ifndef IGMapperChooseTileDlg_h
#define IGMapperChooseTileDlg_h

#include "BR_Game.h"
#include "List.h"
#include <string>
using namespace std;

class IGMapperChooseTileDlg: public IniBasedDialog
{
public:
  IGMapperChooseTileDlg(IniFile& ini, string name, list<string> listItems);
  ~IGMapperChooseTileDlg();

  string getChosedTile();

private:
  List* m_tileList;
};

#endif