#ifndef SkinCanvas_h
#define SkinCanvas_h

#include "UI/Canvas.h"
#include "Graphics/Skin.h"

class SkinCanvas: public Canvas
{
public:
  SkinCanvas(): Canvas(), m_skin(0) { }
  ~SkinCanvas();

  void setSkin(string assetName);
  virtual void paint(Display* display);

private:
  Skin* m_skin;
};
#endif