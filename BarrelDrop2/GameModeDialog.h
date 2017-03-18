#ifndef GameModeDialog_h
#define GameModeDialog_h

#include "UI.h"
#include "ToggleButton.h"
class GameModeDialog: public IniBasedDialog, public MouseListener
{
public:
  GameModeDialog(IniFile& ini, string name);
  
  virtual void actionPerformed(ActionEvent* event);
  virtual void mouseEntered(MouseEnterEvent* event);
  virtual void mouseExited(MouseExitEvent* event);

  virtual void mouseClicked(MouseClickEvent* event);

private:
  TextArea* m_textArea;
  ToggleButton* m_survivorToggle;
};


#endif