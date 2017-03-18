#pragma warning (disable : 4530 4503 4786)

#include "BR_Game.h"
#include "UI/ConsoleCommand.h"
#include "SDL_gfxPrimitives.h"
#include "Misc/AssetManager.h"
#include "Tasking/GameScheduler.h"

#include "Timer.h"
#include "Link.h"
#include "Coroutine.h"
#include "StdString.h"

#include <iostream>

//UISystem theUI;

BR_Game* BR_Game::s_instance = 0;

BR_Game& BR_Game::instance()
{
  return *s_instance;
}

bool BR_Game::initialize(int w, int h, int bpp, DisplayType type, Uint32 flags)
{
  logScope("BR_Game::initialize");

  int old = MaintLog::get().setFilter(All);
  if ( (old & All) == All)
  {
    MaintLog::get().setFilter(old);
  }

  logError(Inform, "Width: %d, Height: %d, Bpp: %d, Type: %s, Flags: 0x%08x",
    w, h, bpp, (char*)(type==SDL?"SDL":"OPENGL"), flags);

  char buf[255];
  if (type == SDL || type == OPENGL)
  {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) == -1)
    {
      sprintf(buf, "SDL not inited: SDL_GetError() returns: %d", SDL_GetError());
      logError(buf, Fatal);
      return false;
    }
    atexit(SDL_Quit);
  }

  srand(time(0));
  
  Display* disp=0;

  disp = Display::create(w, h, bpp, type, flags);
  
  SDL_EnableKeyRepeat(250, SDL_DEFAULT_REPEAT_INTERVAL);

  new BR_Game(disp);
  return true;
}

BR_Game::BR_Game(Display* disp):
//uiSystem(theUI),
screen(disp),
m_drawListener(0),
m_appListener(0),
m_showFPS(false),
m_throttle(false),
m_capture(false),
m_frameNum(0),
m_grabTimer(0),
m_co_gameTick(*this, BR_Game::co_tickGameFrame, "GameTick")
{
  logScope("BR_Game::BR_Game");
  
  assetManager = 0;
  m_fpsStringBuf[0] = '\0';

  s_instance = this;
  initializeInput();
  uiSystem.initialize();

  uiSystem.setPosition(Rect(0, 0, disp->getWidth(), disp->getHeight()));

  SDL_ShowCursor(false);

  m_co_gameTick.spawn();

//  m_grabTimer = Timer::create("ScreenGrabber", -1, 1000/15, this, 0, true);
}

BR_Game::~BR_Game()
{
  delete screen;
  if (m_grabTimer != 0)
  {
    Timer::destroy(m_grabTimer);
  }
}

void BR_Game::setWindowInfo(SDL_Surface* icon, string text)
{
  m_windowText = text;
  m_icon = icon;
  setWindowInfo();
}

void BR_Game::setWindowInfo()
{
  if (m_windowText != "")
  {
    SDL_WM_SetCaption(m_windowText.c_str(), m_windowText.c_str());
  }
  if (m_icon != 0)
  {
    SDL_WM_SetIcon(m_icon, 0);
  }
}
////////////////////////
/// INPUT //////////////
////////////////////////
void BR_Game::initializeInput()
{
  m_keyboard = SDL_GetKeyState(&m_numKeys);
  for (int x=0; x<8; x++)
  {
    m_buttonState[x]=FREE;
  }
}

void BR_Game::pumpInput()
{
  SDL_PumpEvents();
  m_keyboard = SDL_GetKeyState(&m_numKeys);
  int x, y;
  SDL_GetMouseState(&x, &y);
  m_mouse.x = x;
  m_mouse.y = y;
}
  
bool BR_Game::isKey(int keySym)
{
  return (m_keyboard[keySym] != 0);
}

bool BR_Game::grabInput(bool grab)
{
  SDL_GrabMode mode=(grab?SDL_GRAB_ON:SDL_GRAB_OFF);
  return (mode == SDL_WM_GrabInput(mode));
}

bool BR_Game::warpMouse(Uint16 x, Uint16 y)
{
  SDL_WarpMouse(x, y);
  return true;
}

bool BR_Game::showCursor(bool show)
{
//  bool old = m_mouseShowing;
//  m_mouseShowing = show;
//  return old;
  return uiSystem.showCursor(show);
}

void BR_Game::drawMouse()
{
  if (m_mouseStack.empty()) 
    return;
  
  MouseCursor& mc = m_mouseStack.front();
  int realX = m_mouse.x - mc.hotX;
  int realY = m_mouse.y - mc.hotY;
  
  mc.skin->blit(theGame.screen, realX, realY, false);
}


void BR_Game::setButtonState(int b, int s)
{
  m_buttonState[b] = s;
}
int BR_Game::getButtonState(int b)
{
  return m_buttonState[b];
}

Point BR_Game::getMousePos()
{
  return m_mouse;
}

//////////////////////////
/// GAME //////////////////
///////////////////////////

unsigned short BR_Game::translate(unsigned short keySym)
{
  switch(keySym)
  {
  case SDLK_KP0:
  case SDLK_KP1:
  case SDLK_KP2:
  case SDLK_KP3:
  case SDLK_KP4:
  case SDLK_KP5:
  case SDLK_KP6:
  case SDLK_KP7:
  case SDLK_KP8:
  case SDLK_KP9: return keySym - 208;
  case SDLK_KP_ENTER: return SDLK_RETURN;
  }

  return keySym;
}

int BR_Game::pollEvents()
{
  // possably optimize by using static maessages or message cache
  
  SDL_Event revent;
  SDL_Event* event=&revent;
  int c;

  while ((c = SDL_PollEvent(event)) > 0)
  {
    switch (event->type) 
    {
    case SDL_KEYDOWN:
      {
        m_sdlMetaKeyState = event->key.keysym.mod;
        KeyPressEvent keyPress;
        keyPress.real=event->key.keysym.sym;
        keyPress.keySym = translate(keyPress.real);
        keyPress.metaKeyState = m_sdlMetaKeyState;
        uiSystem.onKeyPress(&keyPress);
      }
      break;
    case SDL_KEYUP:
      {
        m_sdlMetaKeyState = event->key.keysym.mod;
        KeyReleaseEvent keyRelease;
        keyRelease.real=event->key.keysym.sym;
        keyRelease.keySym = translate(keyRelease.real);
        keyRelease.metaKeyState = m_sdlMetaKeyState;
        uiSystem.onKeyRelease(&keyRelease);
      }
      break;
    case SDL_MOUSEMOTION:
      {
        MouseMoveEvent mouseMove;
        mouseMove.x = event->motion.x;
        mouseMove.y = event->motion.y;
        mouseMove.relx = event->motion.xrel;
        mouseMove.rely = event->motion.yrel;
        mouseMove.metaKeyState = m_sdlMetaKeyState;
        uiSystem.onMouseMove(&mouseMove);
      }
      break;
      
    case SDL_MOUSEBUTTONUP:
      {
        MouseReleaseEvent up;
        up.x = (event->button.x);
        up.y = (event->button.y);
        up.button = (event->button.button);
        up.metaKeyState = m_sdlMetaKeyState;
        uiSystem.onMouseRelease(&up);

        int prevState=getButtonState(event->button.button);
        if (prevState == DOWN)
        {
          MouseClickEvent click;
          click.x = (event->button.x);
          click.y = (event->button.y);
          click.button = event->button.button;
          uiSystem.onMouseClick(&click);
        }
        setButtonState(event->button.button, FREE);
      }
      break;
      
    case SDL_MOUSEBUTTONDOWN:
      {
        MousePressEvent down;
        down.x = (event->button.x);
        down.y = (event->button.y);
        down.button = (event->button.button);
        down.metaKeyState = m_sdlMetaKeyState;
        setButtonState(event->button.button, DOWN);
        uiSystem.onMousePress(&down);
      }
      break;
    case SDL_ACTIVEEVENT:
      {
        if (m_appListener != 0)
        {
          if (event->active.state & SDL_APPINPUTFOCUS)
          {
            if (event->active.gain == 1)
            {
              m_appListener->appGainedFocus();
            }
            else
            {
              m_appListener->appLostFocus();
            }
          }
        }
//        logError(Inform, "App %s focus.", event->active.gain?"Gained":"Lost");
      }
      break;
    case SDL_QUIT:
      {
        if (m_appListener != 0)
        {
          m_appListener->appQuitRequest();
        }
      }
      break;
    default:
      {
        //logError(Inform, "Unknown event: event->type = %d", event->type);
      }
      break;
    }
  }
  return c;
}

clock_t start = clock();
clock_t now;

void BR_Game::pump()
{
#ifdef _DEBUG
  StopWatch pump;
  pump.start();

  StopWatch sw;
  sw.reset();
  
  sw.start();
  draw();
  sw.stop();
  m_sw_draw = sw.getElapsedTime();
  sw.reset();

  sw.start();
  Link::processLinks();
  sw.stop();
  m_sw_network = sw.getElapsedTime();
  sw.reset();

  sw.start();
  pumpInput();
  pollEvents();
  sw.stop();
  m_sw_input = sw.getElapsedTime();
  sw.reset();

  sw.start();
  Timer::tick();
  sw.stop();
  m_sw_timer = sw.getElapsedTime();
  sw.reset();

  sw.start();
  Coroutine::schedule();
  sw.stop();
  m_sw_coroutine = sw.getElapsedTime();

  pump.stop();
  m_sw_pump = pump.getElapsedTime();
#else
  draw();
  Link::processLinks();
  pumpInput();
  pollEvents();
  Timer::tick();
  Coroutine::schedule();
#endif
}

void BR_Game::timeReport()
{
  logError(Inform, "");
  logError(Inform, "Time Report");
  logError(Inform, "-----------------------");
  logError(Inform, "drawing    : %03d", m_sw_draw);
  logError(Inform, "network    : %03d", m_sw_network);
  logError(Inform, "input      : %03d", m_sw_input);
  logError(Inform, "timer      : %03d", m_sw_timer);
  logError(Inform, "coroutine  : %03d", m_sw_coroutine);
  logError(Inform, "worldDraw  : %03d", m_sw_worldDraw);
  logError(Inform, "-----------------------");
  logError(Inform, "TOTAL      :%04d", m_sw_pump);
}

void BR_Game::timeout(TimerEvent* event)
{
  if (!m_capture)
  {
    return;
  }

  CStdString fn;
  fn.Format("framegrab%d.bmp", m_frameNum);
  logError(Inform, "Screengrab: %d", m_frameNum);
  screen->screenshot(fn);
  m_frameNum++;
}

void BR_Game::draw()
{
  static frames = 0;
  static DWORD start = timeGetTime();

  if (m_drawListener != 0)
  {
    m_drawListener->preDraw();
  }
  
  uiSystem.draw(screen);
  
  if (m_drawListener != 0)
  {
    m_drawListener->postDraw();
  }
  if (m_showFPS)
  {
    DWORD elap = timeGetTime() - start;
    float FPS = (float)frames/(elap/1000);
    if (elap > 10000)
    {
      start = elap;
      frames = 0;
    }

    Font* font=Font::getDefault();
    sprintf(m_fpsStringBuf, "FPS: %f", FPS);
    font->drawLine(screen, m_fpsStringBuf, 20, 20);
  }
//  if (m_mouseShowing)
//  {
//    drawMouse();
//  }
  
  screen->flip();
}


////////////////////////
  // INTERACTION////////
  ///////////////////////
  
int BR_Game::msgBox(string str, string title, int flags)
{
  int width=Font::getDefault()->getTextWidth(str) + 40;
  width = 400;
  int x = (640/2) - (width/2);
  int y = 100;
  int h = 90;

  bool useBoth = false;;
  Button* bOne = 0;
  Button* bTwo = 0;
  int oc=BR_OK_CANCEL;

  if ((flags & BR_OK_CANCEL) == BR_OK_CANCEL)
  {
    useBoth = true;
    bOne = m_msgBoxOk;
    bTwo = m_msgBoxCancel;
  }
  else if ((flags & BR_OK) == BR_OK)
  {
    bOne = m_msgBoxOk;
  }
  else if ((flags & BR_CANCEL) == BR_CANCEL)
  {
    bOne = m_msgBoxCancel;
  }

  if (width < 200)
  {
    width = 200;
  }

  m_msgBox->setPosition(Rect(x, y, width, h));
  m_msgBox->setText(title.c_str());
  m_msgBoxLabel->setText(str.c_str());
  m_msgBoxLabel->setPosition(Rect(0, 15, width, 30));

  m_msgBoxOk->hide();
  m_msgBoxCancel->hide();

  
  if (useBoth)
  {
    bOne->setPosition(Rect( (width/2) - 90, 50, 80, 30));
    bTwo->setPosition(Rect( (width/2) + 10, 50, 80, 30));
    bOne->show();
    bTwo->show();
  }
  else
  {
    bOne->setPosition(Rect( (width/2) - 40, 50, 80, 30));
    bOne->show();
  }

  return m_msgBox->doModal();
}

void BR_Game::co_tickGameFrame()
{
  while(true)
  {
    GameScheduler::newFrame();
    Coroutine::waitUntilFromStart(33);
  }
}
