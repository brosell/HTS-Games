#include "RotateSkin.h"
#include "SDL_rotozoom.h"

RotateSkin::RotateSkin(int numOfRotations): 
m_numberRotations(numOfRotations),
m_currentRotation(0),
m_currentFrame(0),
m_numFrames(0),
m_fps(15)
{
  m_frameTimer = Timer::create("RotateSkin", 0, 1000/m_fps, this, 0, true);
}

RotateSkin::~RotateSkin()
{
  Display* display = Display::getInstance();
  for (int c=0; c<m_numFrames; c++)
  {
    for (int r=0; r<m_numberRotations; r++)
    {
      display->release(m_skins[c][r]);
      delete m_bitMasks[c][r];
    }
  }
  Timer::destroy(m_frameTimer);
}

void RotateSkin::addImage(const char* filename, int count)
{
  SDL_Surface* orig = loadSDLSurface(filename);
  addImage(orig, count);
  SDL_FreeSurface(orig);
  m_numFrames+=count;
}

void RotateSkin::addImage(SDL_Surface* orig, int count)
{
  Display* display = Display::getInstance();
  for (int r=0; r<m_numberRotations; r++)
  {
    double angle = r * ((360/m_numberRotations));
    SDL_Surface* rotated = rotozoomSurface(orig, -angle, 1, 0);
    m_manipulated.insert(rotated);
    for (int c=0; c<count; c++)
    {
      m_skins[m_numFrames+c][r] = display->prepare(rotated); //->pixels, rotated->w, rotated->h);
      m_bitMasks[m_numFrames+c][r] = new CollisionBitMask(rotated->pixels, rotated->w, rotated->h);
    }
    SDL_FreeSurface(rotated);
  }
  
}

void RotateSkin::timeout(TimerEvent* event)
{
  m_currentFrame++;
  if (m_currentFrame >= m_numFrames)
  {
    m_currentFrame = 0;
  }
}