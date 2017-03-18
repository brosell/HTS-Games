/* ****************************************************************************
 *
 *  RadioButton.h
 *  Created by Bert Rosell, on Mon Nov 24 2003, 14:07:36 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the RadioButton component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__RADIOBUTTON_H
#define ATC__RADIOBUTTON_H
 


#include "Button.h"

class RadioButtonGroup;

/** Purpose: TODO: Describe the purpose of the class.
 *  (Everything that you write here will show up in the
 *  doc++ generated documentation.)
 */

class RadioButton: public Button
{
public:
  RadioButton();
  RadioButton(StringMap& attributes);
  ~RadioButton();
  virtual void paint(Display* surface);

  bool isChecked() { return m_isChecked; }

  virtual void onMouseClick(MouseClickEvent* event);

  void setCheckedTexture(string assetName);
  void setUncheckedTexture(string assetName);
  void setDisabledTexture(string assetName);

  RadioButtonGroup* getGroup() { return m_group; }

private:
  friend class RadioButtonGroup;
  void check() { m_isChecked = true; setDirty(true); }
  void uncheck() { m_isChecked = false; setDirty(true); }

  bool m_isChecked;
  SharedSkinHandle m_unchecked;
  SharedSkinHandle m_checked;
  SharedSkinHandle m_disabled;

  RadioButtonGroup* m_group;
};

class RadioButtonGroup;
class RadioButtonEvent: public UIEvent
{
public:
  RadioButtonGroup* group;
};

class RadioButtonGroupListener
{
public:
  virtual void radioEvent(RadioButtonEvent* event) { }
};

class RadioButtonGroup
{
public:
  /** returns the group of this name, creating if need be */
  static RadioButtonGroup* get(string name);
  static void release(string name);

  void addRadioButton(RadioButton* button);

  void setChecked(RadioButton* button);
  void setChecked(int id);

  int getCheckedId();
  bool isChecked(int id);

  void addRadioButtonGroupListener(RadioButtonGroupListener* listener);
  void removeRadioButtonGroupListener(RadioButtonGroupListener* listener);

private:
  void update();
  vector<RadioButton*> m_buttons;
  set<RadioButtonGroupListener*> m_listeners;
  static map<string, RadioButtonGroup*> s_groups;
  
  RadioButtonGroup() {};
  ~RadioButtonGroup() {};
};


#endif#endif // #ifndef ATC__RADIOBUTTON_H
 
