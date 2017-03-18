#ifndef ShipManager_h
#define ShipManager_h

class Ship;
#include "Game/Thing.h"
#include <set>

#include "UI/NewEventModel.h"

enum CommandMode
{
  CMD_NONE,
  CMD_MOVE,
  CMD_ATTACK,
  CMD_ADJUST_ANGLE,
  CMD_SET_WAYPOINT,
  CMD_HOLD_POSITION,
  CMD_PATROL
};


class ShipManager: public KeyListener, public MouseListener //, public TimerListener
{
public:
  ShipManager();
  ~ShipManager() { }

  void addThing(Ship* thing);

  /* MouseListener */
  virtual void mouseClicked(MouseClickEvent* event);

  /* KeyListener */
  virtual void keyPressed(KeyPressEvent* event);

protected:
  void select(Thing* thing);

  void doButton1(MouseClickEvent* event);
  void doButton2(MouseClickEvent* event);

private:
  set<Ship*> m_things;

  Ship* m_selected;

  CommandMode m_mode;
};

#endif