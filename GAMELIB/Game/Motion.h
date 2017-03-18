#ifndef _Motion_h
#define _Motion_h


class Motion
{
public:
  Motion(float x, float y, int w, int h): m_x(x), m_y(y), m_w(w), m_h(h)
  {
    m_moved=true;
  }

  void setPostion(float x, float y)
  {
    m_x=x;
    m_y=y;
    m_moved=true;
  }

  virtual void tickAndMove(int& retX, int& retY) { return; }

  bool moved()  { return m_moved; }
  void setMoved(bool m) { m_moved=m; }





protected:
  float m_x;
  float m_y;

  int m_w;
  int m_h;
  bool m_moved;
};


#endif
