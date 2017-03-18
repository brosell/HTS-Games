#pragma warning (disable : 4786 4503 4530)

#include "Board.h"
#include "Block.h"
#include "Convert.h"
#include "Globals.h"
#include "GameUI.h"

#include "StdString.h"

#include <list>


Board::Board():
Thing(14, -1, false, true, 1),
m_shape(Shape::instance()),
m_tickTimeout(0),
d_levelBonus(*this, Board::doLevelBonus, "LevelBonus"),
d_clearBlocks(*this, Board::co_clearDoneBlocks, "ClearBlocks"),
d_gameOver(*this, Board::co_gameOver, "GameOver", this),
d_levelText(*this, Board::co_levelText, "LevelText"),
m_currentMove(0)
{
  logError(Inform, "Initializing Board");
  m_disappearSound = Globals::am->getSoundEffect("snd_Blocks_Disappearing");
  m_levelSound = Globals::am->getSoundEffect("snd_New_Level");
  m_multiSound = Globals::am->getSoundEffect("snd_Bonus_Multi_1");
  m_wildSound = Globals::am->getSoundEffect("snd_Wild_Block_Effect");
  m_clearBoardSound = Globals::am->getSoundEffect("snd_Clear_Board");
  m_levelBonusSound = Globals::am->getSoundEffect("snd_Level_Bonus");

  m_lbl_score = (Label*)dia_gameScreen->getControlByName("ScoreDisplay");
  m_lbl_level = (Label*)dia_gameScreen->getControlByName("LevelDisplay");

  m_boardStubSkin = Globals::am->getRotateSkin("skn_Board480x480");


  setSkin(m_boardStubSkin);

  m_levelBonusSkin = Globals::am->getSkin("gfx_Level_Bonus_Barrel");
  m_calcLevelBonusSkin = Globals::am->getSkin("skn_Calc_Level_Bonus");
  m_calcLevelBonusLocation = Point(Globals::am->getAttribute("skn_Calc_Level_Bonus", "Location"));

  m_bigBarrel = Globals::am->getSkin("skn_Big_Barrel");

  for(int x=0; x<WIDTH; x++)
  {
    for (int y=0; y<HEIGHT; y++)
    {
      m_blocks[x][y] = 0; // empty
    }
  }

  m_shape.setBoard(this);
  m_shape.reset();
  m_shape.reset();

  Score::addListener(this);

  m_state = BS_STOPPED;
  d_clearBlocks.spawn();

  string fontName = Globals::am->getText("txt_PauseFont");
  if (fontName != "")
  {
    m_pauseFont = Globals::am->getFont(fontName);
    m_pausePoint = Point(Globals::am->getText("txt_PauseFontPoint"));
  }
}

void Board::start()
{
  Shape::instance().newGame();
  char buf[16];
  sprintf(buf, "%d", Score::getCurrentScore());
  m_lbl_score->setText(buf);

  sprintf(buf, "%d", Score::getCurrentLevel());
  m_lbl_level->setText(buf);

  
  preLevel();
  m_state = BS_PLAYING;
  m_shape.reset();
}

void Board::co_levelText()
{
  CStdString lt;
  lt.Format("txt_Level_%d", Score::getCurrentLevel());

  CStdString text = Globals::am->getText(lt);
  if (text != "")
  {
    IniFile ini("ui\\dialogs.ini");
    ini.read();
    IniBasedDialog mes(ini, "dlg_LevelMessage");
    TextArea* txt = (TextArea*)mes.getControlByName("txt_MessageText");
    txt->setText(text);
    txt->setParent(&mes);
    mes.show();
    Coroutine::pause(1000);
    mes.hide();
  }
}


void Board::stop()
{
  m_state = BS_STOPPED;
}

void Board::pause(bool p) 
{ 
  switch(m_state)
  {
  case BS_PAUSED:
    if (p == false)
    {
      m_state = BS_PLAYING;
    }
    break;
  case BS_PLAYING:
    if (p == true)
    {
      m_state = BS_PAUSED;
    }
    break;
  default:
    break;
  }
}

Board::~Board()
{
  Score::removeListener(this);

  for(int x=0; x<WIDTH; x++)
  {
    for (int y=0; y<HEIGHT; y++)
    {
      delete m_blocks[x][y];
    }
  }

  m_shape.setBoard(0);
}

int Board::getBlockCount()
{
  if (Score::getCurrentLevel() < 4)
    return 3;

  int n = 3 + Score::getCurrentLevel() / 4;

  if (n > BLOCK_COUNT)
    n = BLOCK_COUNT;

  return n;
}

void Board::timeout(TimerEvent* ev)
{
  if ((ev->id == 101) && (m_state == BS_PLAYING))
  {
    tick();
  }
}

void Board::preLevel()
{
  if (Globals::clearBlocksAtLevelUp)
  {
    for (int x=0; x<WIDTH; x++)
    {
      for (int y=0; y<HEIGHT; y++)
      {
        if (m_blocks[x][y] != 0)
        {
          delete m_blocks[x][y];
          m_blocks[x][y] = 0;
        }
      }
    }
  }

  int primedRows = Score::getNumRowsToPrimeBoardWith();
  static int nextColor = 0;
  for (int y=HEIGHT-primedRows; y<HEIGHT; y++)
  {
    // fill row with aternating colors
    for (int x=0; x<WIDTH; x++)
    {
      if (m_blocks[x][y] == 0)
      {
        m_blocks[x][y] = new Block(this, nextColor);
        nextColor++;
        if (nextColor >= getBlockCount())
        {
          nextColor = 0;
        }
      }
    }
  }

  m_currentMove = 0;
  prg_progress->setUpperBound(Score::getBlocksPerLevel());
  
//  co_levelText();
  
  Shape::instance().reset();
  Shape::instance().reset();
  Shape::instance().reset();
  Shape::instance().reset();
  
  tick();
}

void Board::scoreChanged(ScoreChangeEvent* ev)
{
  char buf[16];
  sprintf(buf, "+%d", ev->changeAmmount);

  if (m_state != BS_LEVEL_BONUS)
  {
    if (m_lastScorePoint.x != -1)
    {
      int x=(m_lastScorePoint.x*BLOCK_SIZE) + getX();
      int y=(m_lastScorePoint.y*BLOCK_SIZE) + getY();

      scvs_specialNotices->showText(buf, x, y-100, "fnt_Groovy_Blue_Giant");
    }
  }

  sprintf(buf, "%d", ev->currentScore);
  m_lbl_score->setText(buf);
}

void Board::levelChanged(LevelChangeEvent* ev)
{
  char buf[16];
  sprintf(buf, "%d", ev->currentLevel);
  m_lbl_level->setText(buf);

  if (ev->currentLevel != 1)
  {
    d_levelBonus.spawn();
  }

}

void Board::doLevelBonus()
{
  Coroutine::pause(1000);

  m_state = BS_LEVEL_BONUS;
  startLevelBonus();
  
  while (continueLevelBonus())
  {
    Coroutine::waitUntilFromStart(25);
  }
  endLevelBonus();
  Coroutine::pause(500);
  if (Score::getCurrentLevel() > DEMO_LEVELS && Globals::isDemo)
  {
    demoOver();
  }
  else
  {
    
    preLevel();
    m_state = BS_PRE_LEVEL;
    CStdString s;
    s.Format("Level %d!", Score::getCurrentLevel());
    scvs_specialNotices->showText(s, 280, 300, "fnt_Groovy_Blue_Giant");
    Coroutine::pause(1000);
    scvs_specialNotices->showText("Ready?", 280, 300, "fnt_Groovy_Blue_Giant");
    Coroutine::pause(1000);
    scvs_specialNotices->showText("Go!", 280, 300, "fnt_Groovy_Blue_Giant");
    Coroutine::pause(1000);
    m_state = BS_PLAYING;
  }
}

void Board::startLevelBonus()
{
  m_levelBonusEmptySpots.clear();
  m_levelBonusCX = 0;
  m_levelBonusCY = 0;

  m_levelBonusSound->play();
}
bool Board::continueLevelBonus()
{
  /* check current block
  adjust cx and cy
  if both cx and cy are bigger than board, were done
  */
  
  if (m_levelBonusCY >= HEIGHT)
  {
    return false;
  }

  bool foundOne = false;

  if (m_blocks[m_levelBonusCX][m_levelBonusCY] == 0 || m_blocks[m_levelBonusCX][m_levelBonusCY]->getState() != IDLE)
  {
    m_levelBonusEmptySpots.push_back(Point(m_levelBonusCX, m_levelBonusCY));
    m_lastScorePoint = Point(m_levelBonusCX, m_levelBonusCY);
    foundOne = true;
    Score::addBonusPts(Globals::levelBonus);
  }

  m_levelBonusCX++;
  if (m_levelBonusCX>=WIDTH)
  {
    m_levelBonusCX = 0;
    m_levelBonusCY++;
  }

  if (!foundOne)
  {
    return continueLevelBonus();
  }
  return foundOne;
}

void Board::endLevelBonus()
{
  m_levelBonusSound->fadeOut(1000);
}

void Board::doWild()
{
  int x, y;
  
  for (y=0; y<HEIGHT; y++)
  {
    for (x=0; x<WIDTH; x++)
    {
      if (m_blocks[x][y] != 0 && m_blocks[x][y]->getState() == IDLE)
      {
        if (m_blocks[x][y]->getColor() == WILD_UP_DOWN)
        {
          verticalWild(x, y);
        }
        else if (m_blocks[x][y]->getColor() == WILD_LEFT_RIGHT)
        {
          horizontalWild(x, y);
        }
      }
    }
  }
}


void Board::findMatchingBlocks()
{
  int x, y;

  list<Point> matches;

  for (y=0; y<HEIGHT; y++)
  {
    for (x=0; x<WIDTH; x++)
    {
      if (m_blocks[x][y] != 0 && m_blocks[x][y]->getState() == IDLE && m_blocks[x][y]->getColor() != BLACK)
      {
        checkTile(x, y, matches, true);
        if (matches.size() >= Globals::minimumMatch)
        {
          removeTiles(matches);
          return;
        }
        matches.clear();
      }
    }
  }
}

void Board::removeTiles(list<Point>& matches)
{
  m_disappearSound->play();
  setScoreLocation(matches);
  
  Score::blocksDisappear(matches.size());
  
  list<Point>::iterator i;
  for (i=matches.begin(); i!=matches.end(); i++)
  {
    Point p = (*i);
    m_blocks[p.x][p.y]->disappear();
  }
}

void Board::setScoreLocation(list<Point>& points)
{
  int xtotal = 0;
  int ytotal = 0;

  list<Point>::iterator i;
  for (i=points.begin(); i!=points.end(); i++)
  {
    xtotal+= (1+ (*i).x);
  }
  m_lastScorePoint = Point(xtotal/points.size(), 8);
}

int Board::clearDoneBlocks()
{
  int count = 0;
  int x, y;
  // now, any blocks that are "DONE" need to be eliminated and
  // everything else needs to be shifted down.
  for (y=HEIGHT-1; y>=0; y--)
  {
    for (x=0; x<WIDTH; x++)
    {
      if (m_blocks[x][y] == 0)
      {
        continue;
      }

      if (m_blocks[x][y]->getState() == DONE)
      {
        count++;
        delete m_blocks[x][y];
        m_blocks[x][y] = 0;

        for (int yy=y; yy>=0; yy--)
        {
          m_blocks[x][yy] = m_blocks[x][yy-1];
        }
        m_blocks[x][0] = 0;

        y=HEIGHT;
        x=-1;
      }
    }
  }
  return count;
}

void Board::checkClearBoard()
{
  int x, y;
  for (y=0; y<HEIGHT; y++)
  {
    for (x=0; x<WIDTH; x++)
    {
      if (m_blocks[x][y] != 0)
      {
        return;
      }
    }
  }
  // if we get here the board is clear
  m_clearBoardSound->play();
  Score::clearBoard();
}

void Board::tick()
{
  doWild();
  findMatchingBlocks();

  //m_shape.reset();
}


void Board::co_clearDoneBlocks()
{
  while(true)
  {
    if (clearDoneBlocks() > 0)
    {
      checkClearBoard();
      Coroutine::waitUntilFromStart(250);
      findMatchingBlocks();
    }
    Coroutine::waitUntilFromStart(250);
    if (!anyActivity())
    {
      if (!m_shape.isInPlay())
      {
        m_shape.reset();
      }
    }
  }
}


void Board::checkTile(int x, int y, list<Point>& toBeWacked, bool first)
{
  static int color = -1;

  if (first)
  {
    color = m_blocks[x][y]->getColor();
  }

  if (find(toBeWacked.begin(), toBeWacked.end(), Point(x, y)) != toBeWacked.end())
  {
    // allready in the wack list
    return;
  }

  if (m_blocks[x][y] == 0 || m_blocks[x][y]->getState() != IDLE)
  {
    // allready wacked or in process
    return;
  }

  
  int c = m_blocks[x][y]->getColor();
  if (m_blocks[x][y]->getColor() == color)
  {
    toBeWacked.push_back(Point(x, y));
    if (x>0)
    {
      checkTile(x-1, y, toBeWacked, false);
    }
    if (x<WIDTH - 1)
    {
      checkTile(x+1, y, toBeWacked, false);
    }
    if (y>0)
    {
      checkTile(x, y-1, toBeWacked, false);
    }
    if (y < HEIGHT - 1)
    {
      checkTile(x, y+1, toBeWacked, false);
    }
  }
}

void Board::horizontalWild(int column, int row)
{
  Point loc = getPixelPoint(column, row);
  int count = 0;
  /*set all block in row to disappearing*/
  for (int x=0; x<WIDTH; x++)
  {
    Block* block = m_blocks[x][row];
    if (block != 0 && block->getState() == IDLE)
    {
      block->disappear();
      if (block->getColor() < 900)
      {
        // don;t score the wild block itself
        count++;
      }
    }
  }
  m_wildSound->play();
  
  Score::blocksDisappear(count);

}

void Board::verticalWild(int column, int row)
{
  int count = 0;
  /*set all block in column to disappearing*/
  for (int y=0; y<HEIGHT; y++)
  {
    Block* block = m_blocks[column][y];
    if (block != 0 && block->getState() == IDLE)
    {
      block->disappear();
      if (block->getColor() < 900)
      {
        // don;t score the wild block itself
        count++;
      }
    }
  }
  
  m_wildSound->play();

  Score::blocksDisappear(count);

}



void Board::draw(Display* display, int xx, int yy)
{
  if (m_state == BS_PAUSED)
  {
    m_pauseFont->drawLine(display, "Paused", m_pausePoint.x, m_pausePoint.y, true);
    //Font::getDefault()->drawLine(display, "Paused", 220, 220);
  }
  else
  {
    for (int x=0; x<WIDTH; x++)
    {
      for (int y=0; y<HEIGHT; y++)
      {
        if (m_blocks[x][y] != 0)
        {
          //g_blockSkins[m_blocks[x][y]]->blit(display, x*60+30, y*60+30);
          m_blocks[x][y]->draw(display, x, y);
        }
      }
    }
    if (m_state == BS_LEVEL_BONUS)
    {
      Point pos = getPositioni();

      list<Point>::iterator i;
      for (i=m_levelBonusEmptySpots.begin(); i!=m_levelBonusEmptySpots.end(); i++)
      {
        Point p=(*i);
        Point dest(pos);
        dest.x += (p.x*BLOCK_SIZE + HALF_BLOCK_SIZE);
        dest.y += (p.y*BLOCK_SIZE + HALF_BLOCK_SIZE);
        m_levelBonusSkin->blit(display, dest.x, dest.y);
      }
      m_calcLevelBonusSkin->blit(display, m_calcLevelBonusLocation.x, m_calcLevelBonusLocation.y, true);
    }
    else if (m_state == BS_GAME_OVER)
    {
      m_bigBarrel->blit(display, m_gameOver.x, m_gameOver.y, false);
    }
    else if (m_state == BS_DEMO_OVER)
    {
      //m_bigBarrel->blit(display, m_gameOver.x, m_gameOver.y, false);
      m_pauseFont->drawLine(display, "Demo Over", m_pausePoint.x, m_pausePoint.y, true);
    }

    else if (m_state == BS_PRE_LEVEL)
    {

    }
    else
    {
      m_shape.draw(display);
    }
  }
}

bool Board::isBlockType(int x, int y, int c)
{
  return false;
}

int Board::getBlockType(int x, int y)
{
  if (m_blocks[x][y] != 0)
    return m_blocks[x][y]->getColor();

  return -1;
}

void Board::setBlockType(int x, int y, int t)
{
  lassert(m_blocks[x][y] == 0);

  m_blocks[x][y] = new Block(this, t);
  m_blocks[x][y]->idle();
}

bool Board::isEmpty()
{
  for (int x=0; x<WIDTH; x++)
  {
    for (int y=0; y<HEIGHT; y++)
    {
      if (m_blocks[x][y]==0)
      {
        continue;
      }
      if (m_blocks[x][y]->getState() == IDLE)
      {
        return false;
      }
    }
  }
  return true;
}

void Board::co_gameOver()
{
  SoundEffectHandle sound = Globals::am->getSoundEffect("snd_Game_Over");
  sound->play();
  for (int y=-435; y<=15; y+=15)
  {
    m_gameOver.x = 95;
    m_gameOver.y = y;
    Coroutine::pause(33);
  }
  Coroutine::pause(2000);
  
}

void Board::gameOver()
{
  m_state = BS_GAME_OVER;
  d_gameOver.spawn();
//  m_shape.endGame();
//  ::endGame();
}

void Board::demoOver()
{
  m_state = BS_DEMO_OVER;
  d_gameOver.spawn();
//  m_shape.endGame();
//  ::endGame();
}


void Board::coroutineFinished(CoroutineEvent* ev)
{
  stop();
  m_shape.endGame();
  Globals::endGame = true;
//  ::endGame();
}

bool Board::anyActivity()
{
  int x, y;
  for (y=0; y<HEIGHT; y++)
  {
    for (x=0; x<WIDTH; x++)
    {
      if (m_blocks[x][y] != 0)
      {
        if (m_blocks[x][y]->getState() != IDLE)
        {
          return true;
        }
      }
    }
  }
  return false;
}

