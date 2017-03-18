#pragma warning (disable : 4786 4503 4530)

#include "Club.h"
#include "Globals.h"
#include "AssetManager.h"
#include "GolfBall.h"

Club::Club():
Thing(9),
m_dirToShoot(0, -1),
m_logic(*this, Club::logic),
m_power(0),
m_isSpace(false)
{
  m_skin = Globals::am->getRotateSkin("skn_Club");
  setSkin(m_skin);

  ThinkScheduler::doAt(ThinkScheduler::nextFrame(), &m_logic);

  m_ballSkin = Globals::am->getRotateSkin("skn_GolfBall");

  theGame.uiSystem.addKeyListener(this);
}

Club::~Club()
{
  theGame.uiSystem.removeKeyListener(this);
}

void Club::draw(Display* display, int x, int y)
{
  Thing::draw(display, x, y);
  Vector toShoot = m_dirToShoot.normalize().multiply(50+m_power);
  Vector ballPosV = m_dirToShoot.normalize().multiply(30);

  if (!Globals::theBall->isVisible())
  {
    m_ballSkin->blit(display, x+ballPosV.x, y+ballPosV.y, true);
  }
  display->drawLine(x, y, x+toShoot.x, y+toShoot.y, 255, 255, 0, 255);
  
}

void Club::keyPressed(KeyPressEvent* event)
{
  if (event->keySym == SDLK_SPACE && Globals::theBall->isVisible() == false)
  {
    if (!m_isSpace)
    {
      m_goingUp = true;
    }
    m_isSpace = true;
  }

}

void Club::keyReleased(KeyReleaseEvent* event)
{
  if (event->keySym == SDLK_SPACE)
  {
    m_isSpace = false;
    if (Globals::theBall->isVisible() == false)
    {
      shoot();
    }
    m_power = 0;
  }
}


void Club::logic()
{
  const int TICKSTOWAIT = 30;
  static int ticksBeforeMove = TICKSTOWAIT;
 // while(true)
  {
    /* if ball vel == 0 goto ball */
    //if (Globals::theBall->getSpeed() == 0)
    if (Globals::theBall->getGBState() == GBS_AT_REST)
    {
      ticksBeforeMove--;
      if (ticksBeforeMove <= 0)
      {
        FPoint moveTo = Globals::theBall->getPositionf();
        //moveTo.y+=20;
        setPosition(moveTo);
        ticksBeforeMove = TICKSTOWAIT;
        //Globals::theBall->setPosition(moveTo);
        Globals::theBall->setVisible(false);

      }
      
    }
    else
    {
      ticksBeforeMove = TICKSTOWAIT;
    }

    /* if space bar do fire logic */
    if (m_isSpace)
    {
      if (!Globals::world->isThingVisable(Globals::theBall))
      {
        Globals::lastViewChangeWasMouse = false;
      }
      if (m_goingUp)
        m_power++;
      else
        m_power--;
    }

    if (m_power > 50)
    {
      m_power--;
      m_goingUp = false;
    }
    else if (m_power < 1)
    {
      m_power++;
      m_goingUp = true;
    }

    /* if left or right is pressed, adjust launch vector */

    adjustAim();

//    Vector ballPosV = m_dirToShoot.normalize().multiply(60);
//
//    FPoint pos = getPositionf();
//    pos.x+=ballPosV.x;
//    pos.y+=ballPosV.y;
//    Globals::theBall->setPosition(pos);

    ThinkScheduler::doAt(ThinkScheduler::nextFrame(), &m_logic);
  }
}

void Club::shoot()
{
  Vector ballPosV = m_dirToShoot.normalize().multiply(30);
  
  FPoint pos = getPositionf();
  pos.x+=ballPosV.x;
  pos.y+=ballPosV.y;
  Globals::theBall->setPosition(pos);

  Globals::theBall->setVisible(true);
  Globals::theBall->applyForce(m_dirToShoot.normalize().multiply(m_power));
  Globals::lastViewChangeWasMouse = false;
}

void Club::adjustAim()
{
  Angle a = m_dirToShoot.anglei();

  if (theGame.isKey(SDLK_LEFT))
  {
    if (!Globals::world->isThingVisable(Globals::theBall))
      {
        Globals::lastViewChangeWasMouse = false;
      }
      
    a = a - 10;
    Vector v = Vector::createFromAngle(a, 100);
    m_dirToShoot = v;
  }
  else if (theGame.isKey(SDLK_RIGHT))
  {
    if (!Globals::world->isThingVisable(Globals::theBall))
      {
        Globals::lastViewChangeWasMouse = false;
      }
      
    a = a + 10;
    Vector v = Vector::createFromAngle(a, 100);
    m_dirToShoot = v;
  }
}
