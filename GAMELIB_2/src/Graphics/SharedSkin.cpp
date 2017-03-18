#pragma warning (disable : 4786 4503 4530)
#include "SharedSkin.h"
#include "Utils.h"
#include "SDL_rotozoom.h"

SharableSkin::SharableSkin(bool generateCollisionMasks):
m_generateMasks(generateCollisionMasks),
m_fps(15),
m_references(0),
m_loaded(false),
m_forcedW(-1),
m_forcedH(-1)
{

}

SharableSkin::~SharableSkin()
{
  unload();
}

Skin* SharableSkin::acquire()
{
  if (!m_loaded)
  {
    load();
  }
  m_references++;
  SharedSkin* ret = new SharedSkin(this);
#ifdef HTS_DEBUG
  m_acquired.insert(ret);
#endif
  logError(Debug, "Skin %08x acquired.", ret);
  return ret;
//  return 0;
}

void SharableSkin::release(Skin* skin)
{
  logError(Debug, "Skin %08x released.", skin);
  lassert(m_references > 0);
#ifdef HTS_DEBUG
  lassert(m_acquired.find(skin) != m_acquired.end());
  m_acquired.erase(skin);
#endif
  if (skin){
    delete ((SharedSkin*)skin);
    skin = 0;
  }
  m_references--;
  if (m_references == 0)
  {
    unload();
  }
}

void SharableSkin::load()
{
  m_size = 0;
  lassert2(getNumFrames() == 0, "loading when loaded?");

  list<string>::iterator i;
  for (i=m_filenames.begin(); i!=m_filenames.end(); i++)
  {
    loadFile(*i);
  }
  m_loaded = true;
}

void SharableSkin::loadFile(string filename)
{
  Display* display = Display::getInstance();
  SDL_Surface* img;
  if (m_forcedW < 0 || m_forcedH < 0)
  {
    img = loadSDLSurface(filename);
  }
  else
  {
    img = loadSDLSurfaceResize(filename, m_forcedW, m_forcedH);
  }
  
  HTexture texture = 0;
  if (img != 0)
  {
    texture = display->prepare(img, filename);
    if (m_generateMasks)
    {
      CollisionBitMask* cbm = new CollisionBitMask(img->pixels, img->w, img->h);
      m_collisionMasks.push_back(cbm);
    }
    m_size += img->h * img->pitch;
    
    SDL_FreeSurface(img);
  }
  if (texture == 0)
  {
    error <<  "Unable to load texture " << filename << endl;
  }
  else
  {
    m_images.push_back(texture);
  }
  
}


void SharableSkin::unload()
{
  lassert2(getNumFrames() != 0, "already unloaded?");
  Display* display = Display::getInstance();
  vector<HTexture>::iterator i;
  for (i=m_images.begin(); i!=m_images.end(); i++)
  {
    display->release(*i);
  }
  m_images.clear();
  
  vector<CollisionBitMask*>::iterator ci;
  for (ci=m_collisionMasks.begin(); ci!=m_collisionMasks.end(); ci++)
  {
    delete (*ci);
  }
  m_collisionMasks.clear();
  
  m_loaded = false;
  m_size = 0;
}

HTexture SharableSkin::getFrame(int o)
{
  lassert(o < getNumFrames());
  return m_images[o];
}

CollisionBitMask* SharableSkin::getCollisionMask(int o)
{
  lassert(o < getNumFrames());
  lassert(m_generateMasks);
  return m_collisionMasks[o];
}

void SharableSkin::addImage(const char* filename, int count)
{
  lassert2(count>0, "adding 0 frames?");
  for(int c=0; c<count; c++)
  {
    m_filenames.push_back(filename);
  }
}

SharedSkin::SharedSkin(SharableSkin* parent):
m_parent(parent),
m_numFrames(0),
m_currentFrame(0),
m_frameTimer(0),
m_fps(15)
{
  m_fps = parent->getFPS();
  m_numFrames = parent->getNumFrames();
  setCurrentTexture(0);
  reset();
}

SharedSkin::~SharedSkin()
{
  if (m_frameTimer != 0)
  {
    Timer::destroy(m_frameTimer);
    m_frameTimer = 0;
  }
}

HTexture SharedSkin::currentFrame() 
{ 
  return m_parent->getFrame(m_currentFrame); 
}

CollisionBitMask* SharedSkin::currentCollisionMask()
{ 
  return m_parent->getCollisionMask(m_currentFrame); 
}

void SharedSkin::reset()
{
  m_currentFrame = 0;

  if (m_frameTimer != 0)
  {
    Timer::destroy(m_frameTimer);
    m_frameTimer = 0;
  }

  if (m_fps > 0)
  {
    m_frameTimer = Timer::create("SharedSkin", -1, 1000/m_fps, this, 0, true);
  }
  setCurrentTexture(m_parent->getFrame(m_currentFrame));
}

void SharedSkin::timeout(TimerEvent* ev)
{
  m_currentFrame++;
  if (m_currentFrame >= m_numFrames)
  {
    skinLooped();
    m_currentFrame = 0;
  }
  setCurrentTexture(m_currentFrame);
  frameChanged();
}


