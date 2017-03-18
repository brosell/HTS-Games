#ifndef VScrollBar_h
#define VScrollBar_h

#include "UIThing.h"
#include "BR_Game.h"

class VScrollBar: public UIThing 
{
public:
  VScrollBar();

  virtual ~VScrollBar();

  void setBounds(int low, int high) { lassert(low <= high); m_lowBound = low; m_highBound = high; /*m_position = low;*/ }
  void setScrollPosition(int p) { lassert(p >= m_lowBound); lassert(p <= m_highBound); m_position = p; }
  int getScrollPosition() { return m_position; }
  bool acceptsFocus() { return false; }

  void paint(Display* surface);

  void addAdjustmentListener(AdjustmentListener* listener) { m_adjustmentListeners.insert(listener); }
  void removeAdjustmentListener(AdjustmentListener* listener) { m_adjustmentListeners.erase(listener); }

  virtual void onMouseClick(MouseClickEvent* event);
protected:
  void updateListeners();
private:
  int m_lowBound;
  int m_highBound;
  int m_position;

  int m_width;
  int m_buttonHeight;
  int m_height;

  bool m_pressed;

  HTexture m_upArrow;
  HTexture m_downArrow;
  HTexture m_slider;

  AdjustmentEvent ae;
  set<AdjustmentListener*> m_adjustmentListeners;

};


#endif