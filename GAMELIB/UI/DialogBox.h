#ifndef _DialogBox_h
#define _DialogBox_h

#include "Container.h"
#include "Button.h"
#include "Label.h"

#include "Log.h"
#include <algorithm>

#ifdef DialogBox
#undef DialogBox
#endif

class DialogBox;

class DialogEvent
{
public:
  DialogBox* dialog;
};

class DialogListener
{
public:
  virtual void onOk(DialogEvent* event) { }
  virtual void onCancel(DialogEvent* event) { }
};

class DialogBox: public Container, public DialogListener, public ActionListener
{
public:
  /**
  @param background asset name of background. Must be a skin.
  */
  DialogBox(const char* background);

  virtual ~DialogBox();

  virtual string getName() { return "DialogBox"; }

  virtual void setText(const string& s){ Container::setText(s); m_title.setText(s); }

  virtual void show() { Container::show(); }

  virtual void setPosition(Rect& pos) 
  { 
    m_title.setPosition(Rect(0, 0, pos.w, 20)); 
    Container::setPosition(pos); 
  }

  /**
    * cause this dialog to be shown. Also this dialog is the only one
    * that can accept input.
    * If loop is non-NULL, then that delegate will be called
    * once per game tick while modal.
    */
  virtual int doModal(Delegate* loop = 0);

  virtual void terminateModal(int retValue);

  /**
    * called when the default button is pressed
    */
  virtual void onOK();
  
  /**
    * called when the cancel button is pressed
    */
  virtual void onCancel();

  /** from DialogListener used in modal processing */
  virtual void onOk(DialogEvent* event);
  /** from DialogListener used in modal processing */
  virtual void onCancel(DialogEvent* event);

  /** from ActionListener. */
  virtual void actionPerformed(ActionEvent* event);

  /**
    * set the onButtonNClick delegate for the button whose id is passed
    */
  void setButtonHandler(int buttonID, ActionListener* listener);

  void onKeyPress(KeyPressEvent* event);
  
  virtual void paint(Display* surface);

  /**
    * set the default button. The Default button responds to the enter key.
    * when the default button is pressed, the onOk() method is called
    */
  void setDefault(Button* def)
  {
    def->addActionListener(this);
    m_defaultButton = def;
    def->setId(1);
  }

  /**
    * set the cancel button. The cancel button responds to the ESC key.
    * when the cancel button is pressed, the onCancel() method is called
    */
  void setCancel(Button* cancel)
  {
    cancel->addActionListener(this);
    m_cancelButton = cancel;
    cancel->setId(0);
  }

  

  void addListener(DialogListener* listener)
  {
    m_listeners.insert(listener);
  }
  void removeListener(DialogListener* listener)
  {
    m_listeners.erase(listener);
  }

  void setUseKeys(bool useKeys) { m_useKeys = useKeys; }

protected:
  /**
    * called during modalness once per game tick.
    * overrridden version would return false to end the modal dialog
    */
  virtual bool modalLoop() { return true; }

   
  /**
    * the return value for doModal. it is set however you want. MsgBoxes set it
    * to the value of the button pressed (OK or Cancel)
    */
  int m_modalReturn;

  // these are used by the IniDialog
  DialogBox():
  Container(), 
  m_defaultButton(0), 
  m_cancelButton(0),
  m_background(0),
  m_isModal(false)
  {    
//    m_title.setHorizJust(JUST_CENTER);
//    m_title.setVertJust(JUST_MIDDLE);
//    m_title.setDrawBorder(true);
//    addUIThing(&m_title);
    m_event.dialog = this;
  }

  /**
  @param background name of the background asset. Asset must be a Skin
  */
  void setBackground(string background);
  
  Skin* getBackground() { return m_background; }

private:
  DialogEvent m_event;
  Button* m_defaultButton;
  Button* m_cancelButton;

  bool m_useKeys;
  
  set<DialogListener*> m_listeners;
  
  

  Label m_title;
  bool m_isModal;

  Skin* m_background;

};



#endif