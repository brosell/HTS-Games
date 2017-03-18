#pragma warning (disable:4786 4530 4503)
#include "BR_Game.h"
#include "UIThing.h"
#include "AssetManager.h"

#include "SoundEffect.h"

#include "StringTokenizer.h"

bool UIThing::s_ocheck=true;
UIThing* UIThing::s_mouseOver = 0;
int UIThing::s_drawCount = 0;
bool UIThing::s_smartDraw = true;

UIThing::UIThing(): 
m_haveFocus(false), 
m_visible(true), 
m_parent(0),
m_id(-1),
m_haveMouse(false),
m_controlName("Unnamed"),
m_red(0),
m_green(0),
m_blue(0),
m_alpha(0),
m_dred(0),
m_dgreen(0),
m_dblue(0),
m_dalpha(0),
m_enabled(true),
m_dirty(true),
m_under(0),
m_inited(false)
{

}

UIThing::UIThing(StringMap& attributes): 
m_haveFocus(false), 
m_visible(true), 
m_parent(0),
m_id(-1),
m_haveMouse(false),
m_controlName("Unnamed"),
m_red(0),
m_green(0),
m_blue(0),
m_alpha(0),
m_dred(0),
m_dgreen(0),
m_dblue(0),
m_dalpha(0),
m_enabled(true),
m_dirty(true),
m_under(0),
m_inited(false)
{
  init(attributes);
}

void UIThing::init(StringMap& attributes)
{
  m_inited = true;
    string font = attributes["Font"];
    if (font != "")
    {
      setFont(theGame.am->getFont(font));
    }

    // should be automatic, right?
//    else if (m_defaultFontName != "")
//    {
//      setFont(theGame.am->getFont(m_defaultFontName));
//    }
    
    string mouse = attributes["Mouse"];
    if (mouse != "")
    {
      setMouseCursor(mouse);
    }

    if(attributes["BackgroundColor"] != "")
    {
      int r, g, b, a;
      parseColor(attributes["BackgroundColor"], r, g, b, a);
      setBackgroundColor(r, g, b, a);
    }
    setPosition(Rect::parseRect(attributes["Position"]));
    setId(atoi(attributes["Id"].c_str()));
    string text = attributes["Text"];
    if (text != "")
    {
      setText(text.c_str());
    }
    string assetName = attributes["TextAsset"];
    if (assetName != "")
    {
      setText(theGame.am->getText(assetName).c_str());
    }

    doSFX(attributes);

//    thing->setEnabled(m_ini.getInt(name, "Enabled")!=0);
//    thing->setVisible(m_ini.getInt(name, "Visible")!=0);
}

void UIThing::doSFX(StringMap& attributes)
{
  string asset = "";
  
  asset = attributes["SFX_MousePress"];
  if (asset != "")
  {
    setOnMousePressSFX(asset);
  }

  asset = attributes["SFX_MouseRelease"];
  if (asset != "")
  {
    setOnMouseReleaseSFX(asset);
  }

  asset = attributes["SFX_MouseClick"];
  if (asset != "")
  {
    setOnMouseClickSFX(asset);
  }
  
  asset = attributes["SFX_MouseDblClick"];
  if (asset != "")
  {
    setOnMouseDblClickSFX(asset);
  }
  
  asset = attributes["SFX_MouseEnter"];
  if (asset != "")
  {
    setOnMouseEnterSFX(asset);
  }

  asset = attributes["SFX_MouseExit"];
  if (asset != "")
  {
    setOnMouseExitSFX(asset);
  }
  
  asset = attributes["SFX_MouseOver"];
  if (asset != "")
  {
    StringTokenizer st(asset, ", ");
    string a = st.nextToken();
    bool loop = false;
    if (st.countTokens() > 0)
    {
      loop = atoi(st.nextToken())==0?false:true;
    }
    setMouseOverSFX(a, loop);
  }
  
  asset = attributes["SFX_KeyPress"];
  if (asset != "")
  {
    setOnKeyPressSFX(asset);
  }
  
  asset = attributes["SFX_KeyRelease"];
  if (asset != "")
  {
    setOnKeyReleaseSFX(asset);
  }

}


UIThing::~UIThing()
{
  if (s_mouseOver == this)
  {
    s_mouseOver = 0;
  }

  setMouseCursor("");

  if (m_under != 0)
  {
    SDL_FreeSurface(m_under);
  }
}


FontHandle UIThing::getFont() 
{ 
  if (!m_font.isValid())
  {
    if (m_parent)
    {
      if (!m_parent->getFont().isValid())
      {
        if (this != &(theGame.uiSystem))
        {
          return theGame.uiSystem.getFont();
        }
        return FontHandle();
      }
      return m_parent->getFont();
    }
    if (this != &(theGame.uiSystem))
    {
      return theGame.uiSystem.getFont();
    }
    
    return FontHandle();
  }
  return m_font; 
}

void UIThing::setMouseCursor(string assetName)
{
  if (assetName != "")
  {
    m_mouse = MouseCursor(assetName); 
  }
}

MouseCursor UIThing::getMouseCursor() 
{ 
  if (!m_mouse.isValid())
  {
    if (m_parent != 0)
    {
      return m_parent->getMouseCursor();
    }
    else
    {
      return theGame.uiSystem.getMouseCursor();
    }
  }
  return m_mouse; 
}

void UIThing::drawMouseCursor(Display* surface)
{
  MouseCursor mouse = getMouseCursor();
  if (!mouse.isValid())
  {
    return;
  }

  Point p = theGame.getMousePos();
  int realX = p.x - mouse.hotX;
  int realY = p.y - mouse.hotY;
  
  if (mouse.isValid())
  {
    // copy from screen to temp buf
    // blit mouse
    
    mouse.skin->blit(theGame.screen, realX, realY, false);
  }
}

void UIThing::saveUnder(Display* display)
{
  Rect r = getTranslatedPosition();
  SDL_Surface* surface = display->getSDLSurface();

  m_under = createSDLSurface(r.w, r.h);
  SDL_BlitSurface(surface, r, m_under, Rect(0, 0, r.w, r.h));
}

void UIThing::draw(Display* surface)
{
  if (!isContainer() && m_under == 0 && s_smartDraw)
  {
    saveUnder(surface);
  }
    
  
  if (isVisible() == false)
  {
    return;
  }
  
  if (isDirty() == true || !s_smartDraw)
  {
    s_drawCount++;
    Rect r = getTranslatedPosition();
    if (m_under != 0)
    {
      SDL_BlitSurface(m_under, Rect(0, 0, m_under->w, m_under->h), surface->getSDLSurface(), Rect(r.x, r.y, 0, 0));
    }
    if (m_alpha != 0)
    {
      surface->fillRect(r.x, r.y, r.w+1, r.h+1, m_red, m_green, m_blue, m_alpha);
    }      
    paint(surface);
    setDirty(false);
  }
}


Rect UIThing::getTranslatedPosition()
{
  Rect ret = getPosition();
  Rect p;
  if (m_parent != 0)
  {
    p=m_parent->getTranslatedPosition();
    ret.x += p.x;
    ret.y += p.y;
  }
  
  return ret;
}

bool UIThing::isObscured()
{
  // if we aren't part of a container, we assume we are not obscured
  if (m_parent)
  {
    return m_parent->isObscured(this);
  }
  return false;
}

bool UIThing::isObscuredBy(UIThing* thing)
{
  Rect me=getTranslatedPosition();
  Rect other=thing->getTranslatedPosition();

  Rect overlap=Rect::findOverlap(&me, &other);
  if (overlap.x == -1)
  {
    //there is no overlap, so we are not obscured by thing
    return false;
  }
  if (/*overlap.w == other.w && overlap.h == other.h) || */
       (overlap.w == me.w && overlap.h == me.h) )
  {
    return true;
  }
  // this is a partial overlap. Now we let Z order do the clipping :)
  return false;
}


void UIThing::show()
{
  setDirty();
  if (m_parent)
  {
    m_parent->addUIThing(this);
  }
  else
  {
    theGame.uiSystem.addUIThing(this);
  }
}

void UIThing::hide()
{
  setDirty();
  if (m_parent)
  {
    m_parent->removeUIThing(this);
  }
  else
  {
    theGame.uiSystem.removeUIThing(this);
  }
}

void UIThing::setOnMousePressSFX(string asset)
{
  m_snd_onMousePress = theGame.am->getSoundEffect(asset);
}

void UIThing::setOnMouseReleaseSFX(string asset)
{
  m_snd_onMouseRelease = theGame.am->getSoundEffect(asset);
}

void UIThing::setOnMouseClickSFX(string asset)
{
  m_snd_onMouseClick = theGame.am->getSoundEffect(asset);
}


void UIThing::setOnMouseDblClickSFX(string asset)
{
  m_snd_onMouseDblClick = theGame.am->getSoundEffect(asset);
}

void UIThing::setOnMouseMoveSFX(string asset)
{
  m_snd_onMouseMove = theGame.am->getSoundEffect(asset);
}

void UIThing::setOnMouseEnterSFX(string asset)
{
  m_snd_onMouseEnter = theGame.am->getSoundEffect(asset);
}

void UIThing::setOnMouseExitSFX(string asset)
{
  m_snd_onMouseExit = theGame.am->getSoundEffect(asset);
}

void UIThing::setMouseOverSFX(string asset, bool loop)
{
  m_snd_mouseOver = theGame.am->getSoundEffect(asset);
  m_snd_mouseOverLoop = loop;
}

void UIThing::setOnKeyPressSFX(string asset)
{
  m_snd_onKeyPress = theGame.am->getSoundEffect(asset);
}

void UIThing::setOnKeyReleaseSFX(string asset)
{
  m_snd_onKeyRelease = theGame.am->getSoundEffect(asset);
}


void UIThing::onMousePress(MousePressEvent* event) 
{
  if (m_snd_onMousePress.isValid())
  {
    m_snd_onMousePress->play();
  }
  event->commandId = getId();
  event->thing = this;
  set<MouseListener*> setCopy(m_mouseListeners);
  set<MouseListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->mousePressed(event);
  }
}
void UIThing::onMouseRelease(MouseReleaseEvent* event)
{
  if (m_snd_onMouseRelease.isValid())
  {
    m_snd_onMouseRelease->play();
  }
  event->commandId = getId();
  event->thing = this;
  set<MouseListener*> setCopy(m_mouseListeners);
  set<MouseListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->mouseReleased(event);
  }
}

void UIThing::onMouseClick(MouseClickEvent* event)
{ 
  if (m_snd_onMouseClick.isValid())
  {
    m_snd_onMouseClick->play();
  }
  
  event->commandId = getId();
  event->thing = this;
  set<MouseListener*> setCopy(m_mouseListeners);
  set<MouseListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->mouseClicked(event);
  }
}

void UIThing::onMouseDblClick(MouseDblClickEvent* event)
{ 
  if (m_snd_onMouseDblClick.isValid())
  {
    m_snd_onMouseDblClick->play();
  }
  
  event->commandId = getId();
  event->thing = this;
  set<MouseListener*> setCopy(m_mouseListeners);
  set<MouseListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->mouseDblClicked(event);
  }
}


void UIThing::onMouseMove(MouseMoveEvent* event)
{ 
  if (m_snd_onMouseMove.isValid())
  {
    m_snd_onMouseMove->play();
  }
  
  event->commandId = getId();
  
  if (s_mouseOver != this)
  {
    if (s_mouseOver != 0)
    {
      MouseExitEvent exit;
      s_mouseOver->onMouseExit(&exit);
    }
    
    MouseEnterEvent enter;
    onMouseEnter(&enter);
    s_mouseOver = this;
  }
  event->thing = this;
  set<MouseListener*> setCopy(m_mouseListeners);
  set<MouseListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->mouseMoved(event);
  }
}

void UIThing::onMouseEnter(MouseEnterEvent* event)
{ 
  if (m_snd_onMouseEnter.isValid())
  {
    m_snd_onMouseEnter->play();
  }
  
  if (m_snd_mouseOver.isValid())
  {
    int loops = -1;
    if (m_snd_mouseOverLoop != true)
    {
      loops = 0;
    }
    m_snd_mouseOver->play(loops);
  }
  
  event->commandId = getId();
  event->thing = this;
  set<MouseListener*> setCopy(m_mouseListeners);
  set<MouseListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->mouseEntered(event);
  }
}

void UIThing::onMouseExit(MouseExitEvent* event)
{ 
  if (m_snd_onMouseExit.isValid())
  {
    m_snd_onMouseExit->play();
  }
  
  if (m_snd_mouseOver.isValid())
  {
    m_snd_mouseOver->fadeOut(250);
  }
  
  event->commandId = getId();
  event->thing = this;
  set<MouseListener*> setCopy(m_mouseListeners);
  set<MouseListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->mouseExited(event);
  }
}

void UIThing::onKeyPress(KeyPressEvent* event)
{
  if (m_snd_onKeyPress.isValid())
  {
    m_snd_onKeyPress->play();
  }
  
  event->commandId = getId();
  event->thing = this;
  set<KeyListener*> setCopy(m_keyListeners);
  set<KeyListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->keyPressed(event);
  }
}

void UIThing::onKeyRelease(KeyReleaseEvent* event)
{
  if (m_snd_onKeyRelease.isValid())
  {
    m_snd_onKeyRelease->play();
  }
  
  event->commandId = getId();
  event->thing = this;
  set<KeyListener*> setCopy(m_keyListeners);
  set<KeyListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->keyReleased(event);
  }
}
