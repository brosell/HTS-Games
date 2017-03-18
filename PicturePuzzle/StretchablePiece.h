#ifndef StretchablePiece_h
#define StretchablePiece_h

#include "Display.h"

class Sector;
class StretchablePiece
{
public:
  StretchablePiece(Sector* sector, SDL_Surface* image, bool rot);
  ~StretchablePiece();

  int getId() { return m_id; }
  void setId(int id) { m_id = id; }

  void draw(Display* display, Rect r);

  void rotate();
  bool isStraight() { return m_cRot==0; }

  Sector* getCorrectSector() { return m_correctSector; }
private:
  bool m_rot;
  int m_cRot;
  int m_id;
  HTexture m_textures[4]; // one for each rotation

  Sector* m_correctSector;
};

#endif