#include "Wizard.h"
#include "StringTokenizer.h"

Wizard::Wizard(IniFile& ini, string name)
{
  string dialogs = ini[name]["Dialogs"];
  StringTokenizer st(dialogs, " ,\r\n");
  IniBasedDialog* db = 0;
  while (st.hasMoreTokens())
  {
    db = new IniBasedDialog(ini, st.nextToken());
    m_dialogs.push_back(db);
  }
}

Wizard::~Wizard()
{
 list<IniBasedDialog*>::iterator i;
  for (i=m_dialogs.begin(); i!=m_dialogs.end(); i++)
  {
    IniBasedDialog* db = (*i);
    delete db;
  }
}

  
int Wizard::doModal(Delegate* loop)
{
  list<IniBasedDialog*>::iterator i;
  for (i=m_dialogs.begin(); i!=m_dialogs.end(); i++)
  {
    IniBasedDialog* db = (*i);
    if (db->doModal() != 1)
    {
      return 0;
    }
  }
}
