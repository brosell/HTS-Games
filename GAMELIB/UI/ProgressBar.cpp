#pragma warning (disable : 4786 4503 4530)
#include "ProgressBar.h"

ProgressBar::ProgressBar(bool vertical, int r, int g, int b, int a):
m_vertical(vertical), 
m_red(r), 
m_green(g), 
m_blue(b), 
m_alpha(a), 
m_margin(0),
m_value(0), 
m_currentValue(0), 
m_upperBound(0),
m_label(0)
{
  m_timer = Timer::create("ProgressBarCreaper", -1, 25, this, 0, true);
}

ProgressBar::~ProgressBar()
{
  Timer::destroy(m_timer);
}

void ProgressBar::timeout(TimerEvent* ev)
{
  if (m_currentValue < m_value*ticksPerUnit())
  {
    m_currentValue++;
  }
}

void ProgressBar::setValue(int v) 
{ 
  if (v < m_value)
  {
    m_currentValue = 0;
  }
  m_value = v; 
}

void ProgressBar::paint(Display* surface)
{
  if (m_label == 0 && getParent() != 0 && m_labelName != "")
  {
    UIThing* pthing = getParent();
    DialogBox* parent = dynamic_cast<DialogBox*>(pthing);
    if (parent != 0)
    {
      m_label = dynamic_cast<Label*>(parent->getControlByName(m_labelName));
    }
  }

  Rect r = getTranslatedPosition();

  Font* font = getFont();
  char buf[255];
  sprintf(buf, "%d/%d", m_value, m_upperBound);
  string v(buf);


  //float percent = (float)m_currentValue/(float)m_upperBound;

  if (m_vertical)
  {
    // bottom to top
    //int barHeight = (float)r.h*percent;
    int barHeight = m_currentValue;
    int bary = (r.y + r.h - m_margin) - barHeight;

    if (m_value != 0)
    {
      surface->fillRect(r.x+m_margin, bary, r.w-(2*m_margin), barHeight, m_red, m_green, m_blue, m_alpha);
    }

    int centerY = r.h/2;
    int centerX = r.w/2;

    int tfy = centerY-(font->getTextWidth(v)/2);
    int tfx = centerX-(font->getFontHeight()/2);

    //font->drawLine(surface, v, tfx, tfy);
    if (m_label != 0)
    {
      m_label->setText(v.c_str());
    }
  }
  else
  {
    // left to right
    //int barWidth = (float)r.w*percent;
    int barWidth = m_currentValue;

    int barx = (r.x+r.w)-barWidth;

    if (m_value != 0)
    {
      surface->fillRect(barx, r.y, barWidth, r.h, m_red, m_green, m_blue, m_alpha);
    }

    int centerY = r.h/2;
    int centerX = r.w/2;

    int tfy = centerY-(font->getTextWidth(v)/2);
    int tfx = centerX-(font->getFontHeight()/2);

//    font->drawLine(surface, v, tfx, tfy);
    if (m_label != 0)
    {
      m_label->setText(v.c_str());
    }
  }
}
