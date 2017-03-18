#pragma warning (disable : 4786 4503 4530)

#include "Shape.h"
#include "Block.h"
#include "Board.h"
#include "AssetManager.h"
#include "StdString.h"

#include "Globals.h"

auto_ptr<Shape> Shape::s_instance;
bool ShapePrimitive::s_lastWasSpecial = true;

void endGame();

ShapePrimitive::ShapePrimitive(Board* board):
m_board(board)
{
  int blackProb = 0;
  
  if (board->moveNum() < 3)
  {
    blackProb = 0;
  }
  else
  {
    blackProb = Score::getBlackProbability();
  }

  int wildProb = 0;

  if (board->isEmpty() || board->moveNum() < 5 || (s_lastWasSpecial == true))
  {
    wildProb = 0;
  }
  else
  {
    wildProb = Score::getWildProbability();
  }

  m_isSpecial = ((rand() % 100) < wildProb);
  s_lastWasSpecial = m_isSpecial;

  if (m_isSpecial)
  {
    m_orientation = 0;
    m_isStraight = true;
    m_blocks[0] = new Block(m_board, 998 + (rand()%2)); // FIXME:
    m_blocks[1] = 0;
    m_blocks[2] = 0;
  }
  else
  {
    m_orientation = rand() % 4;
    m_isStraight = ((rand() % 100) < Globals::straightBlockProbability);
    if (m_isStraight)
    {
      m_orientation = 0;
    }
    
    for (int c=0; c<3; c++)
    {
      if ( (rand() % 100) < blackProb)
      {
        m_blocks[c] = new Block(m_board, BLACK);
      }
      else
      {
        m_blocks[c] = new Block(m_board, rand() % m_board->getBlockCount());
      }
    }
  }
}

ShapePrimitive::~ShapePrimitive()
{
  for (int c=0; c<3; c++)
  {
    if (m_blocks[c] != 0)
      delete m_blocks[c];
  }
}

void ShapePrimitive::rotateLeft()
{
  if (isSpecial())
    return;

  int o = m_orientation - 1;
  if (o < 0) o = 3;

  if (Shape::instance().isMoveSafe(o) )
  {
    m_orientation = o;
  }
}

void ShapePrimitive::rotateRight()
{
  if (isSpecial())
    return;

  int o = m_orientation + 1;
  if (o > 3) o = 0;

  if (Shape::instance().isMoveSafe(o) )
  {
    m_orientation = o;
  }
}


Point ShapePrimitive::getBlock1Pos(Point p, int orientation)
{
  Point ret;
  if (isStraight())
  {
    switch(orientation)
    {
    case 0:
      //  123
      ret = Point(p.x, p.y);
      break;
    case 1:
      // 1
      // 2
      // 3
      ret = Point(p.x+1, p.y-1);
      break;
    case 2:
      // 321
      ret = Point(p.x+2, p.y);
      break;
    case 3:
      // 3
      // 2
      // 1
      ret = Point(p.x+1, p.y+1);
      break;
    default:
      lassert(false);
      break;
    }
  }
  else
  {
    switch(orientation)
    {
    case 0:
      //  1
      // 32
      ret = Point(p.x+1, p.y);
      break;
    case 1:
      // 3
      // 21
      ret = Point(p.x+1, p.y+1);
      break;
    case 2:
      // 23
      // 1
      ret = Point(p.x, p.y+1);
      break;
    case 3:
      // 12
      //  3
      ret = Point(p.x, p.y);
      break;
    default:
      lassert(false);
      break;

    }
  }
  return ret;
}

Point ShapePrimitive::getBlock2Pos(Point p, int orientation)
{
  if (isSpecial())
  {
    return getBlock1Pos(p, orientation);
  }

  Point ret;
  if (isStraight())
  {
    switch(orientation)
    {
    case 0:
      //  123
      ret = Point(p.x+1, p.y);
      break;
    case 1:
      // 1
      // 2
      // 3
      ret = Point(p.x+1, p.y);
      break;
    case 2:
      // 321
      ret = Point(p.x+1, p.y);
      break;
    case 3:
      // 3
      // 2
      // 1
      ret = Point(p.x+1, p.y);
      break;
    default:
      lassert(false);
      break;
    }
  }
  else
  {
    switch(orientation)
    {
    case 0:
      //  1
      // 32
      ret = Point(p.x+1, p.y+1);
      break;
    case 1:
      // 3
      // 21
      ret = Point(p.x, p.y+1);
      break;
    case 2:
      // 23
      // 1
      ret = Point(p.x, p.y);
      break;
    case 3:
      // 12
      //  3
      ret = Point(p.x+1, p.y);
      break;
    default:
      lassert(false);
      break;

    }
  }
  return ret;
}

Point ShapePrimitive::getBlock3Pos(Point p, int orientation)
{
  if (isSpecial())
  {
    return getBlock1Pos(p, orientation);
  }

  Point ret;
  if (isStraight())
  {
    switch(orientation)
    {
    case 0:
      //  123
      ret = Point(p.x+2, p.y);
      break;
    case 1:
      // 1
      // 2
      // 3
      ret = Point(p.x+1, p.y+1);
      break;
    case 2:
      // 321
      ret = Point(p.x, p.y);
      break;
    case 3:
      // 3
      // 2
      // 1
      ret = Point(p.x+1, p.y-1);
      break;
    default:
      lassert(false);
      break;
    }
  }
  else
  {
    switch(orientation)
    {
    case 0:
      //  1
      // 32
      ret = Point(p.x, p.y+1);
      break;
    case 1:
      // 3
      // 21
      ret = Point(p.x, p.y);
      break;
    case 2:
      // 23
      // 1
      ret = Point(p.x+1, p.y);
      break;
    case 3:
      // 12
      //  3
      ret = Point(p.x+1, p.y+1);
      break;
    default:
      lassert(false);
      break;

    }
  }
  return ret;
}



Shape::Shape(): 
m_moveTimer(0), 
m_run(true), 
m_millis(Globals::initialSpeed),
m_nextShape(0),
m_currentShape(0),
m_inPlay(false)
{
  m_moveSound = Globals::am->getSoundEffect("snd_Shape_Move");
  m_settleSound = Globals::am->getSoundEffect("snd_Shape_Appears");

  Score::addListener(this);
}

void Shape::newGame()
{
  reset();
  reset();
  reset();

  setSpeed(1);
}
/* sets the location to top of screen and creates 3 random colored blocks */
void Shape::reset()
{
  m_inPlay = true;
  m_doingSpecial = false;
  m_run = true;

  if (m_board == 0)
  {
    return;
  }

  if (m_nextShape == 0)
  {
    m_nextShape = createShape();
  }

  if (m_currentShape != 0)
  {
    delete m_currentShape;
  }

  m_currentShape = m_nextShape;
  m_nextShape = createShape();


  
  if (m_currentShape->isSpecial())
  {
    
    m_blockPosition = Point(3, 0);
  }
  else
  {
    if (m_currentShape->isStraight())
    {
      m_blockPosition = Point(2, 0);
    }
    else
    {
      m_blockPosition = Point(3, 0);
    }
  }

  if (!isMoveSafe(m_blockPosition, m_currentShape->getOrientation()))
  {
    //this->endGame();
    m_board->gameOver();
  }

}

void Shape::endGame()
{
//  m_board->stop();
  m_run=false;
//  ::endGame();
}

ShapePrimitive* Shape::createShape()
{
  ShapePrimitive* sp = new ShapePrimitive(m_board);
  return sp;
}

/* if the shape hasn;t settled to the bottom yet, the isInPlay == true */
bool Shape::isInPlay()
{
  return m_inPlay;
}
  
/* checks timeout and moves block */
void Shape::tick()
{
  if (!m_inPlay)
  {
    return;
  }

  if (m_doingSpecial)
    return;

  if (!m_run)
    return;

  if (!m_board->isRunning())
  {
    return;
  }

  if (isBelowClear())
  {
    m_blockPosition.y += 1;
    m_moveSound->play();
  }
  else
  {
    Score::shapeSettle();
    m_settleSound->play();
    m_board->setBlockType(getBlock1Pos().x, getBlock1Pos().y, m_currentShape->getBlock(0)->getColor());
    if (!m_currentShape->isSpecial())
    {
      m_board->setBlockType(getBlock2Pos().x, getBlock2Pos().y, m_currentShape->getBlock(1)->getColor());
      m_board->setBlockType(getBlock3Pos().x, getBlock3Pos().y, m_currentShape->getBlock(2)->getColor());
    }
    m_board->incMoveNum();
    m_board->tick();
    m_inPlay = false;
  }
}

void Shape::doSpecial()
{
  m_doingSpecial = true;
  switch(m_currentShape->getBlock(0)->getColor())
  {
  case WILD_UP_DOWN:
    doUpDownWild();
    break;
  case WILD_LEFT_RIGHT:
    doLeftRightWild();
    break;
  default:
    lassert2(false, "Unknown Special Block");
    break;
  }
}

void Shape::doUpDownWild()
{
  m_board->verticalWild(getBlock1Pos().x, getBlock1Pos().y);
}

void Shape::doLeftRightWild()
{
  m_board->horizontalWild(getBlock1Pos().x, getBlock1Pos().y);
}


/* called by the timer */
void Shape::timeout(TimerEvent* ev)
{
  if (ev->id == 201)
  {
    tick();
  }
}

void Shape::setSpeed(int level)
{
  if (Globals::speedIncreaseUsePercentage)
  {
    m_millis = Globals::initialSpeed;
    for (int l=1; l<level; l++)
    {
      m_millis = m_millis - ((float)m_millis * ((float)Globals::speedIncreasePerLevel/100));
    }
  }
  else
  {
    m_millis = Globals::initialSpeed - (level * Globals::speedIncreasePerLevel);
  }

  if (m_millis < Globals::minimumSpeed)
  {
    m_millis = Globals::minimumSpeed;
  }

  if (m_moveTimer != 0)
  {
    Timer::destroy(m_moveTimer);
  }
  m_moveTimer = Timer::create("Shape:MoveTimer", 201, m_millis, this, 0, true);
  
  CStdString cs;
  cs.Format("Speed decreased to %d millis", m_millis);
  Globals::console->println(cs);

}


void Shape::levelChanged(LevelChangeEvent* ev)
{
  setSpeed(ev->currentLevel);
}

bool Shape::isBelowClear()
{
  Point dst = m_blockPosition;
  dst.y++;

  if (isMoveSafe(dst, m_currentShape->getOrientation()))
  {
    return true;
  }

  return false;
}

void Shape::rotateLeft()
{
  if (m_board->isRunning())
  {
    m_currentShape->rotateLeft();
  }
}

void Shape::rotateRight()
{
  if (m_board->isRunning())
  {
    m_currentShape->rotateRight();
  }
}

void Shape::moveLeft()
{
  if (!m_board->isRunning())
  {
    return;
  }

  Point dst = m_blockPosition;
  dst.x--;

  if (isMoveSafe(dst, m_currentShape->getOrientation()))
  {
    m_blockPosition = dst;
    m_moveSound->play();
  }
}

void Shape::moveRight()
{
  if (!m_board->isRunning())
  {
    return;
  }

  Point dst = m_blockPosition;
  dst.x++;

  if (isMoveSafe(dst, m_currentShape->getOrientation()))
  {
    m_blockPosition = dst;
    m_moveSound->play();
  }
}



void Shape::nudgeDown()
{
  if (!m_board->isRunning())
  {
    return;
  }

  tick();

  // since now the block has been moved, The current timer should be reset
  // so the block doesn;t jerk down again;
  Timer::destroy(m_moveTimer);
  m_moveTimer = Timer::create("Shape:MoveTimer", 201, m_millis, this, 0, true);
  m_moveSound->play();
}

bool Shape::isMoveSafe(Point p, int orientation)
{

  Point pb1 = m_currentShape->getBlock1Pos(p, orientation);
  Point pb2 = m_currentShape->getBlock2Pos(p, orientation);
  Point pb3 = m_currentShape->getBlock3Pos(p, orientation);

  if ( pb1.x < 0 || pb1.x > (WIDTH - 1) ||
       pb2.x < 0 || pb2.x > (WIDTH - 1) ||
       pb3.x < 0 || pb3.x > (WIDTH - 1) ||
       pb1.y < 0 || pb1.y > (HEIGHT - 1) ||
       pb2.y < 0 || pb2.y > (HEIGHT - 1) ||
       pb3.y < 0 || pb3.y > (HEIGHT - 1) )
  {
    return false;
  }
       
  if (m_board->getBlockType(pb1.x, pb1.y) != -1)
  {
    return false;
  }
  if (m_board->getBlockType(pb2.x, pb2.y) != -1)
  {
    return false;
  }
  if (m_board->getBlockType(pb3.x, pb3.y) != -1)
  {
    return false;
  }

  return true;
}



void Shape::draw(Display* display)
{
  if (!m_board->isRunning())
  {
    return;
  }
  if (!m_inPlay)
  {
    return;
  }

  Point pos = m_board->getPositioni();

  Point pb1 = getBlock1Pos();
  Point pb2 = getBlock2Pos();
  Point pb3 = getBlock3Pos();

  m_currentShape->getBlock(0)->draw(display, pb1.x, pb1.y);
  if (!m_currentShape->isSpecial())
  {
    m_currentShape->getBlock(1)->draw(display, pb2.x, pb2.y);
    m_currentShape->getBlock(2)->draw(display, pb3.x, pb3.y);
  }
  else
  {
  }
}

