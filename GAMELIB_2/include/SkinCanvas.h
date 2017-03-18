#ifndef SkinCanvas_h
#define SkinCanvas_h

#include "Canvas.h"
#include "Skin.h"

class SkinCanvas: public Canvas, public SkinListener
{
public:
  SkinCanvas(): Canvas() { }
  ~SkinCanvas();

  void setSkin(string assetName);
  virtual void paint(Display* display);

  virtual void frameChanged(SkinFrameChangeEvent* event)
  {
    setDirty(true);
  }

private:
  SharedSkinHandle m_skin;
};
#endif