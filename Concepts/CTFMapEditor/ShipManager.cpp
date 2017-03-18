#pragma warning (disable : 4503)

#include "ShipManager.h"
#include "Ship.h"

#include "UI/WorldCanvas.h"
#include "Engine.h"

extern WorldCanvas* worldCanvas;

ShipManager::ShipManager()
{
//  worldCanvas->addMouseListener(this);
}

void ShipManager::addThing(Ship* thing)
{
  m_things.insert(thing);
}

void ShipManager::select(Thing* thing)
{
  if (m_selected != 0)
  {
    m_selected->setSelected(false);
    m_selected = 0;
  }
  if (thing != 0)
  {
    m_selected=(Ship*)thing;
    m_selected->setSelected(true);
  }
  m_mode = CMD_NONE;
}

void ShipManager::mouseClicked(MouseClickEvent* event)
{
  switch(event->button)
  {
  case 1:
    {
      doButton1(event);
    }
    break;
  case 3:
    {
      doButton2(event);
    }
    break;
  default:
    {
      // it is OK to hit another button
    }
  }
}
    
void ShipManager::doButton1(MouseClickEvent* event)
{
  Thing* thing = Engine::instance->theWorld->movingThingAt(event->x, event->y);
  Point trans = Engine::instance->theWorld->translateScreenPoint(Point(event->x, event->y));
  if (m_selected == 0)
  {
    select(thing);
  }
  else
  {
    switch (m_mode)
    {
    case CMD_NONE:
      {
        select(thing);
      }
      break;
    case CMD_MOVE:
      {
        if (thing == 0)
        {
          m_selected->setDestination(trans.x, trans.y);
          m_mode = CMD_NONE;
        }
        else
        {
          // can't MOVE on a thing, so select other thing
          select(thing);
        }
      }
      break;
//    case CMD_ADJUST_ANGLE:
//      {
//        if (thing == 0)
//        {
//          m_selected->setDestinationAngle(trans.x, trans.y);
//          m_mode = CMD_NONE;
//        }
//        else
//        {
//          select(thing);
//        }
//      }
//      break;
    case CMD_HOLD_POSITION:
      {
        m_mode = CMD_NONE;
        logError(Debug, "HoldPosition");
        m_selected->holdPosition(Engine::instance->theMap->getCoord(trans.x, trans.y));
      }
      break;
    case CMD_PATROL:
      {
        m_mode = CMD_NONE;
        logError(Debug, "Patrol");
        m_selected->patrol(Engine::instance->theMap->getCoord(trans.x, trans.y));
      }
      break;
    case CMD_ATTACK:
      {
        m_mode = CMD_NONE; // reset the clicker
        
        logError(Debug, "Attacking!!");
        SpaceTile* tile = Engine::instance->theMap->getTileAt(trans.x, trans.y);
        
        if (thing == 0)
        {
          // attacking point
          GameThing* occupant = tile->getOccupant();
          if (occupant != 0 && occupant->getId() == ID_SHIP)
          {
            m_selected->attack((Ship*)occupant);
          }
          else
          {
            m_selected->attack(tile->getCoords());
          }
        }
        else
        {
          if (thing->getId() != ID_SHIP)
          {
            // attacking point
            m_selected->attack(tile->getCoords());
          }
          else
          {
            Ship* ship = (Ship*)thing;
            m_selected->attack(ship);
          }
        }

      }
      break;
    case CMD_SET_WAYPOINT:
      {
        // add to list of waypoints
        if (thing == 0)
        {
          m_selected->addWaypoint(Engine::instance->theWorld->translateScreenPoint(Point(event->x, event->y)));
        }
        else
        {
          select(thing);
        }
      }
      break;
    default:
      {
        logError(Debug, "Unknown mode!");
      }
      break;
    }
  }
}

void ShipManager::doButton2(MouseClickEvent* event)
{
  // this is a move command if clicked == 0
  // this i an attack command is clicked != 0

  Thing* thing = Engine::instance->theWorld->movingThingAt(event->x, event->y);
  if (thing == 0)
  {
    logError(Debug, "Moving");
  }
  else
  {
    logError(Debug, "Attacking");
  }
}

void ShipManager::keyPressed(KeyPressEvent* event)
{
  switch(event->keySym)
  {
  case SDLK_m:
    {
      m_mode = CMD_MOVE;
    }
    break;
  case SDLK_a:
    {
      m_mode = CMD_ATTACK;
    }
    break;
  case SDLK_w:
    {
      m_mode = CMD_SET_WAYPOINT;
    }
    break;
  case SDLK_h:
    {
      m_mode = CMD_HOLD_POSITION;
    }
    break;
  case SDLK_p:
    {
      m_mode = CMD_PATROL;
    }
    break;
  default:
    {
    }
    break;
  }
}
