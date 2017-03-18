#ifndef Wizard_h
#define Wizard_h
#include "UI/DialogBox.h"
#include "UI/IniBasedDialog.h"

class Wizard: public DialogBox
{
public:
  Wizard(IniFile& ini, string name);
  ~Wizard();
  
  /**
  cycles though each dialog using doModal
  */
  
  virtual int doModal(Delegate* loop = 0);

private:
  list<IniBasedDialog*> m_dialogs;
};

#endif