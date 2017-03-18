#pragma warning (disable : 4786 4530 4503)
#include "VScrollBar.h"

VScrollBar::VScrollBar():
m_lowBound(0),
m_highBound(255),
m_position(0)
{
  // FIXME: use assets and dialog ini
  m_upArrow = theGame.screen->acquire("images\\UI\\ScrollUp.png");
  m_downArrow = theGame.screen->acquire("images\\UI\\ScrollDown.png");
  m_slider = theGame.screen->acquire("images\\UI\\ScrollSlider.png");

  ae.thing = this;
  ae.adjustmentType = ae.adjustmentType = AdjustmentEvent::ADJUSTMENT_VALUE_CHANGED;
}

VScrollBar::~VScrollBar()
{
  if (m_upArrow > 0)
  {
    theGame.screen->release(m_upArrow);
  }
  if (m_downArrow > 0)
  {
    theGame.screen->release(m_downArrow);
  }
  if (m_slider > 0)
  {
    theGame.screen->release(m_slider);
  }
}

void VScrollBar::paint(Display* surface)
{
  Rect r = getTranslatedPosition();
  lassert(r.h > 20); // make sure at least the buttons fit
  
  bool drawSlider = (r.h >= 30);

  if (m_upArrow != 0)
  {
    surface->blit(m_upArrow, r.x, r.y);
  }
  if (m_downArrow)
  {
    surface->blit(m_downArrow, r.x, r.y + r.h - 10);
  }

  if (m_slider == 0)
  {
    return;
  }


  if (!drawSlider)
  {
    return;
  }

  int sliderRelY = 0;
  if (m_highBound == 0 && m_lowBound == 0)
  {
    sliderRelY = 10;
  }
  else
  {
    sliderRelY = (((float)m_position/(float)(m_highBound - m_lowBound)) * (r.h - 30)) + 10;
  }

  surface->blit(m_slider, r.x, r.y + sliderRelY);

}

void VScrollBar::onMouseClick(MouseClickEvent* event)
{
  if (event->button != 1)
  {
    UIThing::onMouseClick(event);
    return;
  }

  Rect r = getTranslatedPosition();

  int mx = event->x - r.x;
  int my = event->y - r.y;

  lassert(mx <= r.w);
  lassert(my <= r.h);

  if (my > 10 && my < (r.h - 10))
    return;

  if (my <= 10)
  {
    // pressed up
    if (m_position > m_lowBound)
    {
      m_position--;
    }
  }
  else
  {
    // pressed down;
    if (m_position < m_highBound)
    {
      m_position++;
    }
  }
  updateListeners();
 }

void VScrollBar::updateListeners()
{
  ae.value = m_position;

  set<AdjustmentListener*> setCopy(m_adjustmentListeners);
  set<AdjustmentListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->adjustmentValueChanged(&ae);
  }

}