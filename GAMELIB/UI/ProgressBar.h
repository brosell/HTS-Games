#ifndef ProgressBar_h
#define ProgressBar_h

#include "BR_Game.h"
#include "Timer.h"

class ProgressBar: public Canvas, public TimerListener
{
public:
  ProgressBar(bool vertical, int r, int g, int b, int a);
  virtual ~ProgressBar();

  void setValue(int v);
  void setUpperBound(int b) { m_upperBound = b; }
  void setMargin(int m) { m_margin = m; }
  void setLabelName(string name) { m_labelName = name; }

  virtual void paint(Display* surface);

  virtual void timeout(TimerEvent* ev);
private:
  float ticksPerUnit() 
  { 
    Rect r = getPosition();
    if (m_vertical)
    {
      return (float)(r.h-(2*m_margin))/(float)m_upperBound;
    }
    return (float)(r.w-(2*m_margin))/(float)m_upperBound;
  }

  int m_red;
  int m_green;
  int m_blue;
  int m_alpha;

  int m_margin;

  HTimer m_timer;

  int m_value;
  int m_currentValue;

  int m_upperBound;
  bool m_vertical;

  string m_labelName;
  Label* m_label;
};



#endif