#ifndef HSlider_h
#define HSlider_h

#include "UIThing.h"
#include "BR_Game.h"

class HSlider: public UIThing, public TimerListener
{
public:
  HSlider();
  ~HSlider();

  void setUnitsPerTick(int unitsPerTick) { m_unitsPerTick = unitsPerTick; }
  void setBounds(int low, int high) { lassert(low <= high); m_lowBound = low; m_highBound = high; /*m_position = low;*/ }
  void setScrollPosition(int p) { lassert(p >= m_lowBound); lassert(p <= m_highBound); m_position = p; }
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

  Skin* m_slider;
  // hotSlider is a slider that is being or has just moved
  Skin* m_hotSlider;

  HTimer m_adjustTimer;

  AdjustmentEvent ae;
  set<AdjustmentListener*> m_adjustmentListeners;

};


#endif