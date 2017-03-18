#pragma warning (disable:4786 4503 4530)
#include "BR_Game.h"
#include "DialogBox.h"
#include "SDL_gfxPrimitives.h"
#include "AssetManager.h"

DialogBox::DialogBox(const char* background): 
Container(), 
m_defaultButton(0), 
m_cancelButton(0),
m_useKeys(false),
m_isModal(false)
{
  m_background = theGame.am->getSkin(background);
  m_event.dialog = this;
}

DialogBox::~DialogBox()
{
}

void DialogBox::setBackground(string background)
{
  if (background != "")
    m_background = theGame.am->getSkin(background);
  else
    m_background = SharedSkinHandle();
}

void DialogBox::actionPerformed(ActionEvent* event)
{
  if (event->thing == m_defaultButton)
  {
    onOK();
  }
  else if (event->thing = m_cancelButton)
  {
    onCancel();
  }
}

void DialogBox::onOK() 
{ 
  set<DialogListener*>::iterator i;
  for (i=m_listeners.begin(); i!=m_listeners.end(); i++)
  {
    (*i)->onOk(&m_event);
  }
}

/**
* called when the cancel button is pressed
*/
void DialogBox::onCancel() 
{
  set<DialogListener*>::iterator i;
  for (i=m_listeners.begin(); i!=m_listeners.end(); i++)
  {
    (*i)->onCancel(&m_event);
  }
}

void DialogBox::onOk(DialogEvent* event)
{
  //m_modalReturn = m_defaultButton->getId();
  terminateModal(m_defaultButton->getId());
}

void DialogBox::onCancel(DialogEvent* event)
{
  //m_modalReturn = m_cancelButton->getId();
  terminateModal(m_cancelButton->getId());
}

void DialogBox::onKeyPress(KeyPressEvent* event)
{
  if (event->keySym == SDLK_ESCAPE && m_useKeys == true)
  {
    if (m_cancelButton != 0)
    {
      m_cancelButton->onMouseClick(0);
    }
  }
  else if (event->keySym == SDLK_RETURN && m_useKeys == true)
  {
    if (m_defaultButton != 0)
    {
      m_defaultButton->onMouseClick(0);
    }
  }
  Container::onKeyPress(event);
}

void DialogBox::paint(Display* surface)
{
  Rect r=getTranslatedPosition();
  
  if ( (UIThing::isDirty() && m_background.isValid()) || (!s_smartDraw) )
  {
    m_background->blit(surface, r.x, r.y, false);
  }
  Container::paint(surface);
}

int DialogBox::doModal(Delegate* loop)
{
  theGame.uiSystem.pushModal(this);
  addListener(this);
 
  m_modalReturn = -1;
  m_isModal = true;
 
  while(m_isModal)
  {
    theGame.pump();
    if (loop)
    {
      loop->invoke(0);
    }
    if (!modalLoop())
    {
      m_isModal=false;
    }
    Sleep(1);
  }
  theGame.uiSystem.popModal();
  removeListener(this);

  return m_modalReturn;
}

void DialogBox::terminateModal(int retValue)
{
  m_modalReturn = retValue;
  m_isModal = false;
}


void DialogBox::setButtonHandler(int buttonID, ActionListener* listener)
{
  Button* button = (Button*)getControl(buttonID);
  button->addActionListener(listener);
}

