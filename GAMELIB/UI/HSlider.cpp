#pragma warning (disable : 4786 4503 4530)
#include "HSlider.h"
#include "Misc/AssetManager.h"

HSlider::HSlider():
m_lowBound(0),
m_highBound(255),
m_position(0),
m_slider(0),
m_hotSlider(0),
m_adjustTimer(0),
m_useMouse(false),
m_unitsPerTick(1)
{
  ae.thing = this;
  ae.adjustmentType = ae.adjustmentType = AdjustmentEvent::ADJUSTMENT_VALUE_CHANGED;
}

HSlider::~HSlider()
{
  if (m_slider != 0)
  {
    theGame.assetManager->releaseSkin(m_slider);
  }
  if (m_hotSlider != 0)
  {
    theGame.assetManager->releaseSkin(m_hotSlider);
  }
}

void HSlider::setSliderSkin(string assetName)
{
  if (m_slider)
  {
    theGame.assetManager->releaseSkin(m_slider);
    m_slider = 0;
  }
  m_slider = theGame.assetManager->getSkin(assetName);
}

void HSlider::setHotSliderSkin(string assetName)
{
  if (m_hotSlider)
  {
    theGame.assetManager->releaseSkin(m_hotSlider);
    m_hotSlider = 0;
  }
  m_hotSlider = theGame.assetManager->getSkin(assetName);
}

void HSlider::paint(Display* surface)
{
  Rect r = getTranslatedPosition();

  // draw slider

  int sliderRelX = 0;
  if (m_highBound == 0 && m_lowBound == 0)
  {
    sliderRelX = 0;
  }
  else
  {
    sliderRelX = (((float)m_position/(float)(m_highBound - m_lowBound)) * (r.w));
  }

  m_slider->blit(surface, r.x + sliderRelX, r.y, false);

}

void HSlider::tickUp()
{
  if (m_position < m_highBound)
  {
    m_position+=m_unitsPerTick;
    if (m_position > m_highBound)
    {
      m_position = m_highBound;
    }
    updateListeners();
  }
}

void HSlider::tickDown()
{
  if (m_position > m_lowBound)
  {
    m_position-=m_unitsPerTick;
    if (m_position < m_lowBound)
    {
      m_position = m_lowBound;
    }
    updateListeners();
  }
}


void HSlider::onMouseClick(MouseClickEvent* event)
{
  if (!m_useMouse)
  {
    return;
  }
  // get rel X and use it to set m_position
  if (event->button != 1)
  {
    UIThing::onMouseClick(event);
    return;
  }
  
  adjust(event->x);
}

void HSlider::onMouseMove(MouseMoveEvent* event)
{
  if (!m_useMouse)
  {
    return;
  }
  if (theGame.getButtonState(1) == 0)
  {
    return;
  }
 
  adjust(event->x);
}

void HSlider::adjust(int x)
{
  Rect r = getTranslatedPosition();

  int mx = x - r.x;

  lassert(mx <= r.w);

  float dif = m_highBound - m_lowBound;
  int newPosition = (((float)mx/(float)r.w) * dif) + .5;

  if (newPosition == m_position)
  {
    return;
  }
  
  m_position = newPosition;
   
  
  //updateListeners();
  if (m_adjustTimer != 0)
  {
    Timer::destroy(m_adjustTimer);
  }
  m_adjustTimer = Timer::create("HSlider::AdjustTimer", -1, 100, this, 0, false);
}

void HSlider::timeout(TimerEvent* event)
{
  if(event->timer = m_adjustTimer)
  {
    updateListeners();
    m_adjustTimer = 0;
  }
}

void HSlider::updateListeners()
{
  ae.value = m_position;

  set<AdjustmentListener*> setCopy(m_adjustmentListeners);
  set<AdjustmentListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->adjustmentValueChanged(&ae);
  }

}