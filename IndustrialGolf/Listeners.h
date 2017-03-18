#ifndef Listeners_h
#define Listeners_h


#ifndef IGMapperListeners_h
#define IGMapperListeners_h

#include "BR_Game.h"
#include "IGMapperTile.h"
#include "IGMapperEntity.h"
#include <set>
using namespace std;

class IGConsoleListener: public ConsoleListener, public KeyListener, public MouseListener
{
public:
  IGConsoleListener();
  ~IGConsoleListener();

  virtual void consoleCommand(ConsoleEvent* event);
  virtual void keyPressed(KeyPressEvent* event);

protected:
  void loadMap(ConsoleEvent* event);
};

#endif

#endif