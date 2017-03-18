#pragma warning (disable : 4786 4530 4503)
#include "IGMapperChooseTileDlg.h"
#include "Tile.h"

IGMapperChooseTileDlg::IGMapperChooseTileDlg(IniFile& ini, string name, list<string> listItems):
IniBasedDialog(ini, name)
{
  m_tileList = (List*)getControlByName("lst_List");
  
  list<string>::iterator i;

  int c= 0;
  for (c=0, i=listItems.begin(); i!=listItems.end(); c++, i++)
  {
    m_tileList->addItem(c, *i);
  }
  if (m_tileList->countItems() > 0)
  {
    m_tileList->setSelected(0);
  }
}

IGMapperChooseTileDlg::~IGMapperChooseTileDlg()
{

}

string IGMapperChooseTileDlg::getChosedTile()
{
  string ret = m_tileList->getSelectedString();
  if (ret == "")
  {
    ret = "None";
  }
  return ret;
}

