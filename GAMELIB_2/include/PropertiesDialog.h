#ifndef PropertiesDialog_h
#define PropertiesDialog_h
#include <map>
#include <list>
#include <string>
using namespace std;

#include "BR_Game.h"

class PropertiesDialog: public DialogBox
{
public:
  PropertiesDialog(map<string, string>& theProperties);
  ~PropertiesDialog();

  virtual void onOK();

private:
  map<string, string>& m_properties;

  list<TextBox*> m_texts;
  list<Label*> m_labels;
};

#endif