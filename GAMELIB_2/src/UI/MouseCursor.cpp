#include "MouseCursor.h"
#include "BR_Game.h"

MouseCursor::MouseCursor(string name)
{
  skin = theGame.am->getSkin(name);
  Point hot = Point(theGame.am->getAttribute(name, "HotSpot"));
  hotX = hot.x;
  hotY = hot.y;
}
