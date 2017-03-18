#pragma warning (disable : 4786 4503 4530)
#include "Graphics/SharedRotateSkin.h"
#include "Utils.h"
#include "SDL_rotozoom.h"
#include "StdString.h"

SharableRotateSkin::SharableRotateSkin(int rotations, bool generateCollisionMask):
m_rotations(rotations),
m_generateMasks(generateCollisionMask),
m_fps(15),
m_references(0),
m_loaded(false),
m_forcedW(-1),
m_forcedH(-1)
{
  
}

SharableRotateSkin::~SharableRotateSkin()
{
#ifdef _DEBUG
  if (m_acquired.size())
  {
    logError(Error, "SharableRotateSkin deleted with outstanding children (%08x)", this);
    unload();
  }
#endif
}

SharedRotateSkin* SharableRotateSkin::acquire()
{
  if (!m_loaded)
  {
    load();
  }
  m_references++;
  SharedRotateSkin* ret = new SharedRotateSkin(this);
#ifdef _DEBUG
  m_acquired.insert(ret);
#endif
  logError(Debug, "Skin %08x acquired.", ret);
  return ret;
}

void SharableRotateSkin::release(SharedRotateSkin* skin)
{
  logError(Debug, "Skin %08x released.", skin);
  lassert(m_references > 0);
#ifdef _DEBUG
  lassert(m_acquired.find(skin) != m_acquired.end());
  m_acquired.erase(skin);
#endif
  if (skin){
    delete ((SharedRotateSkin*)skin);
    skin = 0;
  }
  m_references--;
  if (m_references == 0)
  {
    unload();
  }
}

void SharableRotateSkin::load()
{
  lassert2(getNumFrames() == 0, "loading when loaded?");

  Display* display = Display::getInstance();
  list<string>::iterator i;
  for (i=m_filenames.begin(); i!=m_filenames.end(); i++)
  {
    HTexture texture = 0;
    SDL_Surface* img;
    if (m_forcedW < 0 || m_forcedH < 0)
    {
      img = loadSDLSurface(*i);
    }
    else
    {
      img = loadSDLSurfaceResize((*i), m_forcedW, m_forcedH);
    }
    if (img != 0)
    {
      load(img, (*i));
      SDL_FreeSurface(img);
    }
  }
  m_loaded = true;
}

void SharableRotateSkin::load(SDL_Surface* orig, string fn)
{
  Display* display = Display::getInstance();
  for (int r=0; r<m_rotations; r++)
  {
    double angle = r * ((360/m_rotations));
    SDL_Surface* rotated = rotozoomSurface(orig, -angle, 1, 1);

    CStdString s;
    s.Format("%s (rot=%d)", fn.c_str(), r);
    
    m_images[r].push_back(display->prepare(rotated, s));
    if (m_generateMasks)
    {
      CollisionBitMask* cbm = new CollisionBitMask(rotated->pixels, rotated->w, rotated->h);
      m_collisionMasks[r].push_back(cbm);
    }

    SDL_FreeSurface(rotated);
  }
}

void SharableRotateSkin::unload()
{
  lassert2(getNumFrames() != 0, "already unloaded?");
  Display* display = Display::getInstance();
  vector<HTexture>::iterator i;
  int c=0;
  for (c=0; c<64; c++)
  {
    for (i=m_images[c].begin(); i!=m_images[c].end(); i++)
    {
      display->release(*i);
    }
    m_images[c].clear();
  }

  vector<CollisionBitMask*>::iterator ci;
  for (c=0; c<64; c++)
  {
    for (ci=m_collisionMasks[c].begin(); ci!=m_collisionMasks[c].end(); ci++)
    {
      delete (*ci);
    }
    m_collisionMasks[c].clear();
  }
  m_loaded = false;
}

HTexture SharableRotateSkin::getFrame(int r, int f)
{
  lassert(f < getNumFrames());
  lassert(r < m_rotations);
  return m_images[r][f];
}

void SharableRotateSkin::addImage(const char* filename, int count)
{
  lassert2(count>0, "adding 0 frames?");
  for(int c=0; c<count; c++)
  {
    m_filenames.push_back(filename);
  }
}

SharedRotateSkin::SharedRotateSkin(SharableRotateSkin* parent):
m_parent(parent),
m_numFrames(0),
m_currentFrame(0),
m_frameTimer(0),
m_fps(15),
m_currentRotation(0)
{
  m_fps = parent->getFPS();
  m_numFrames = parent->getNumFrames();

  setCurrentTexture(0);
  reset();
}

int SharedRotateSkin::getNumRotations()
{ 
  return m_parent->getNumRotations(); 
}

SharedRotateSkin::~SharedRotateSkin()
{
  if (m_frameTimer != 0)
  {
    Timer::destroy(m_frameTimer);
    m_frameTimer = 0;
  }
}

HTexture SharedRotateSkin::currentFrame() 
{ 
  return m_parent->getFrame(m_currentRotation, m_currentFrame); 
}

CollisionBitMask* SharedRotateSkin::currentCollisionMask()
{
  return m_parent->getCollisionMask(m_currentRotation, m_currentFrame);
}

void SharedRotateSkin::reset()
{
  m_currentFrame = 0;
  m_currentRotation = 0;
  
  if (m_frameTimer != 0)
  {
    Timer::destroy(m_frameTimer);
    m_frameTimer = 0;
  }
  
  if (m_fps > 0)
  {
    m_frameTimer = Timer::create("SharedRotateSkin", -1, 1000/m_fps, this, 0, true);
  }
  
  setCurrentTexture(m_parent->getFrame(m_currentRotation, m_currentFrame));
}

void SharedRotateSkin::timeout(TimerEvent* ev)
{
  m_currentFrame++;
  if (m_currentFrame >= m_numFrames)
  {
    skinLooped();
    m_currentFrame = 0;
  }
  setCurrentTexture(m_parent->getFrame(m_currentRotation, m_currentFrame));
}

void SharedRotateSkin::setAngle(int a) 
{ 
  m_currentRotation = ((float)a/360.0)*m_parent->getNumRotations(); 
  setCurrentTexture(m_parent->getFrame(m_currentRotation, m_currentFrame));
}

void SharedRotateSkin::setRotation(int r) 
{
  m_currentRotation = r; 
  setCurrentTexture(m_parent->getFrame(m_currentRotation, m_currentFrame));
}
  
void SharedRotateSkin::setFrame(int f) 
{ 
  m_currentFrame = f; 
  setCurrentTexture(m_parent->getFrame(m_currentRotation, m_currentFrame));
}
