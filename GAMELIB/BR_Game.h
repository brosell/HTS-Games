#ifndef BR_Game_h
#define BR_Game_h

#pragma warning (disable: 4786)

#include "UI.h"
#include "Graphics/Skin.h"
#include "Graphics/Display.h"

#include "Log.h"
#include "Timer.h"

#include "Utils.h"

#include "CoroutineDelegates.h"


const int BR_OK = 0x0001;
const int BR_CANCEL = 0x0002;
const int BR_OK_CANCEL = BR_OK | BR_CANCEL;

class AssetManager;

/**
The user subclasses this and registers to 
recieve notifications about screen drawing
  */
class DrawListener
{
public:
  /**
  preDraw is called just before the UISystem draws the screen
  */
  virtual void preDraw() { }

  /**
  postDraw is called just after the UISystem draws the screen
  */
  virtual void postDraw() { }
};



/**
The main interface to the engine
  */
class BR_Game: public TimerListener
{
public:
  ~BR_Game();

  /** the instance of the display */
  Display* screen;
  /** the instance of the User Interface system */
  UISystem uiSystem;
  /**
  user supplied AssetManager containing several required 
  assets (so far fnt_Default is the only required asset)
  */
  AssetManager* assetManager;

  StopWatch glFlipTimer;
  StopWatch frameTimer;

  /** returns the instance of the BR_Game object. Also the macro theGame does this. */
  static BR_Game& instance();

  /**
  Initializes the game engine. 
  This includes the console, display, UI, MaintenanceLog
  @param  w pixel width of screen
  @param  h pixel height of screen
  @param  bpp bits per pixel (0 means desktop bpp)
  @param  type  either OPENGL or SDL
  @param  flags SDL_DOUBLEBUF | SDL_FULLSCREEN

  @return true on success or false
  */
  static bool initialize(int w, int h, int bpp, DisplayType type, Uint32 flags);

  bool setWindowed(bool w) 
  { 
    bool ret = screen->setWindowed(w);
    setWindowInfo();
    return ret;
  }
  bool isWindowed() { return screen->isWindowed(); }
  void setWindowInfo(SDL_Surface* icon, string text);
  /////////////////////////
  // General //////////////
  /////////////////////////
  
  /**
  Polls and dispatches any event in the UI event queue.
  @returns  the number of events processed
  */
  int pollEvents();

  /**
  Pumps UI input, network links, the Timer, draws the screen
  */
  void pump();

  void draw();

  void capture(bool c) { m_capture = c; if (m_capture) m_frameNum = 0;} 
  virtual void timeout(TimerEvent* event);

  /////////////////////////
  // Input ////////////////
  /////////////////////////

  /**
  determines whether a key is currently pressed
  @param keySym the keysym to test
  @return true if the key is pressed, false otherwise
  */
  bool isKey(int keySym);

  /** sets the mouse position. */
  bool warpMouse(Uint16 x, Uint16 y);

  /** gets the mouse position */
  Point getMousePos();

  /**
  sets the mouse grabbed state
  @param grab true to grab the mouse, false to free it
  @return the previous grab state
  */
  bool grabInput(bool grab);

  /**
  sets the mouse graphics
  @param texture - a texture
  @param hotX,hotY the hot spot of the texture
  */
  //void setMouse(string assetName, int hotX, int hotY);

//  void pushMouse(Skin* skin, int hotX, int hotY) {
//    m_mouseStack.push_front(MouseCursor(skin, hotX, hotY));
//  }
//  void pushMouse(MouseCursor& mc){
//    m_mouseStack.push_front(mc);
//  }
//  void popMouse(){
//    lassert(!m_mouseStack.empty());
//    m_mouseStack.pop_front();
//  }

  
  /**
  shows or hide the mouse cursor
  @param show true to show or false to hide
  @return previous show state
  */
  bool showCursor(bool show);
  bool isCursorShowing() { return m_mouseShowing; }

  /**
  gets a mouse button state
  @param b the button number
  @return the state
  */
  int getButtonState(int b);

  ////////////////////////
  // INTERACTION////////
  ///////////////////////

  /**
  Shows a Modal Message Box on the display
  @param str the message
  @param title the string for the title bar
  @flags options for the message box
  @return the id of the control used to dispatch the msgbox
  */
  int msgBox(string str, string title, int flags = BR_OK);

  /**
  sets the draw listener for the game
  @param listener
  */
  void setDrawListener(DrawListener* listener) { m_drawListener = listener; }

  /**
  set the handler for app focus changes
  */
  void setAppListener(AppListener* listener) { m_appListener = listener; }

  void showFPS(bool b) { m_showFPS = b; }
  void setThrottle(bool b) { m_throttle = b; }

  void timeReport();

private:
  bool m_capture;
  int m_frameNum;
  int m_numKeys;
  Uint8* m_keyboard;
  int m_buttonState[8];
  Point m_mouse;

  Uint16 m_sdlMetaKeyState;
  
  DialogBox* m_msgBox;
  Button* m_msgBoxOk;
  Button* m_msgBoxCancel;
  Label* m_msgBoxLabel;

  list<MouseCursor> m_mouseStack;

  bool m_mouseShowing;
  bool m_throttle;

protected:
  void initializeInput();
  void pumpInput();
  unsigned short translate(unsigned short keySym);
  void drawMouse();
  void setButtonState(int b, int s);

  void co_tickGameFrame();
  SpawnableCoroutineTypeDelegate<BR_Game> m_co_gameTick;

public:
  void setWorldDraw(int i) { m_sw_worldDraw = i; }
private:
  BR_Game(Display* disp); // enforce singleton
  BR_Game(const BR_Game& other); // unimplemented

  void setWindowInfo();
  
  //static auto_ptr<BR_Game> s_instance;
  static BR_Game* s_instance;
  
  DrawListener* m_drawListener;
  AppListener* m_appListener;

  bool m_showFPS;
  char m_fpsStringBuf[255];

  HTimer m_grabTimer;

  string m_windowText;
  SDL_Surface* m_icon;

  int m_sw_draw;
  int m_sw_input;
  int m_sw_network;
  int m_sw_timer;
  int m_sw_coroutine;
  int m_sw_pump;
  int m_sw_worldDraw;
};


#define theGame BR_Game::instance()

const int LEFT_BUTTON = 1;
const int RIGHT_BUTTON = 3;
const int MIDDLE_BUTTON = 2;
const int MWHEEL_UP = 4;
const int MWHEEL_DOWN = 5;

const int FREE=0;
const int DOWN=1;

/** simulates a mouse click */
inline void press(int x, int y)
{
  MousePressEvent event;
  event.button = LEFT_BUTTON;
  event.x = x;
  event.y = y;
  theGame.uiSystem.onMousePress(&event);
}

inline void release(int x, int y)
{
  MouseReleaseEvent event;
  event.button = LEFT_BUTTON;
  event.x = x;
  event.y = y;
  theGame.uiSystem.onMouseRelease(&event);
}

inline void click(int x, int y)
{
  press(x, y);
  release(x, y);
  
  MouseClickEvent event;
  event.button = LEFT_BUTTON;
  event.x = x;
  event.y = y;
  theGame.uiSystem.onMouseClick(&event);
}


inline void move(int x, int y, int rx, int ry)
{
  MouseMoveEvent event;
  event.x = x;
  event.y = y;
  event.relx = rx;
  event.rely = ry;
  theGame.uiSystem.onMouseMove(&event);
}


#endif