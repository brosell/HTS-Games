#ifndef HSlider_h
#define HSlider_h

#include "UIThing.h"
#include "BR_Game.h"
#include "AM.h"

class HSlider: public UIThing, public TimerListener, public SkinListener
{
public:
  HSlider();
  ~HSlider();

  void setUnitsPerTick(int unitsPerTick) { m_unitsPerTick = unitsPerTick; setDirty(true);}
  void setBounds(int low, int high) { lassert(low <= high); m_lowBound = low; m_highBound = high; setDirty(true);}
  void setScrollPosition(int p);
  int getScrollPosition() { return m_position; }
  bool acceptsFocus() { return true; }

  void tickUp();
  void tickDown();

  void setSliderSkin(string assetName);
  void setHotSliderSkin(string assetName);

  void setUseMouse(bool m) { m_useMouse = m; }

  void paint(Display* surface);

  void addAdjustmentListener(AdjustmentListener* listener) { m_adjustmentListeners.insert(listener); }
  void removeAdjustmentListener(AdjustmentListener* listener) { m_adjustmentListeners.erase(listener); }

  virtual void onMouseClick(MouseClickEvent* event);
  virtual void onMouseMove(MouseMoveEvent* event);

  virtual void frameChanged(SkinFrameChangeEvent*) { setDirty(true); }

  virtual void timeout(TimerEvent* event);
protected:
  void adjust(int x);
  void updateListeners();
private:
  bool m_useMouse;
  int m_lowBound;
  int m_highBound;
  int m_position;
  int m_unitsPerTick;

  int m_width;
  int m_buttonHeight;
  int m_height;

  bool m_pressed;

  SharedSkinHandle m_slider;
  // hotSlider is a slider that is being or has just moved
  SharedSkinHandle m_hotSlider;

  HTimer m_adjustTimer;

  AdjustmentEvent ae;
  set<AdjustmentListener*> m_adjustmentListeners;

};

//////////////////////////
/// inlines
////////////////////////////

inline void HSlider::setScrollPosition(int p) 
{ 
  lassert(p >= m_lowBound); 
  lassert(p <= m_highBound); 
  m_position = p; 
  setDirty(true);
}

#endif