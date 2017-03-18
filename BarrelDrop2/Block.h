#ifndef Block_h
#define Block_h

#include "BR_Game.h"
#include "Timer.h"

#include "SharedSkin.h"

#include "CoroutineDelegates.h"

#include "ParticleSystem.h"
#include "ParticleTraits.h"


class Board;
class ConvergeTraits;
enum BLOCK_STATE
{
  IDLE,
  DISAPPEARING,
  PRE_CONVERGING,
  CONVERGING,
  DONE
};

enum
{
  RED = 0,
  GREEN = 1,
  BLUE = 2,
  BLACK = 997,
  WILD_UP_DOWN = 999,
  WILD_LEFT_RIGHT = 998
};


class Block: public ParticleListener
{
public:
  Block(Board* board, int color);
  ~Block();

  // sets state to idle; causes idle animation to be drawn
  void idle();

  // starts the disappear animation
  void disappear();

  void doDisappear();

  // this block is done for :)
  void done(); 

  // draws the block. If disappearing it draws the disappearing animation
  void draw(Display* display, int x, int y); // board pos, not screen
  void drawToScreen(Display* display, int x, int y);
  void drawSpecial(Display* display);

  int getColor() { return m_color; }

  BLOCK_STATE getState() { return m_state; }

  
  virtual void particlesDone(ParticleEvent* event);
private:
  void explode();
  int m_x;
  int m_y;
  SharedSkinHandle m_skinIdle;

  SharedSkinHandle m_verticalEffect;
  SharedSkinHandle m_horizontalEffect;

  BLOCK_STATE m_state;

  int m_color;
  Board* m_board;

  SpawnableCoroutineTypeDelegate<Block> d_co_disappear;
  static ExplodingBlockParticleTraits* s_traits[3];
  static ExplodingBlockParticleTraits* s_blackTraits;
};
#endif