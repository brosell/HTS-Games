#pragma warning (disable : 4786 4503 4530)

#include "Score.h"
#include "Globals.h"
#include "GameUI.h"

int Score::m_score;
int Score::m_lastPoints;
int Score::m_scoresPerShape;
int Score::m_blocksRemoved;
  
set<ScoreListener*> Score::m_listeners;
ScoreChangeEvent Score::m_scoreChangeEvent;
LevelChangeEvent Score::m_levelChangeEvent;

SoundEffectHandle Score::m_snd_multiBonus = 0;
SoundEffectHandle Score::m_snd_levelChange = 0;


void Score::addListener(ScoreListener* listener)
{
  m_listeners.insert(listener);
}

void Score::removeListener(ScoreListener* listener)
{
  m_listeners.erase(listener);
}

void Score::reset(int level)
{
  logError(Inform, "Score reset, starting on level %d", level);
  m_score = Globals::baseScore * (level) * Globals::blocksPerLevel;
  m_scoresPerShape = 0;
  m_blocksRemoved = (level) * Globals::blocksPerLevel;
  m_lastPoints = 0;

  if (!m_snd_levelChange.isValid())
  {
    m_snd_multiBonus = Globals::am->getSoundEffect("snd_Bonus_Multi_1");
    m_snd_levelChange = Globals::am->getSoundEffect("snd_New_Level");
  }

}

int Score::getCurrentScore()
{
  return m_score;
}
int Score::getCurrentLevel()
{
  return ((float)m_blocksRemoved / Globals::blocksPerLevel) + 1;
}

void Score::addScore(int points)
{
  m_score += points;
  m_lastPoints = points;

  dispatchScoreChange();
}

void Score::addBlocksRemoved(int blocks)
{
  
  int prevLevel = getCurrentLevel();
  m_blocksRemoved += blocks;

  int newLevel = getCurrentLevel();

  if (newLevel != prevLevel)
  {
    levelUp();
  }

  prg_progress->setValue(blocksForLevel());
}

void Score::levelUp()
{
  logError(Inform, "Level Up %d", getCurrentLevel());
  dispatchLevelChange();
  m_snd_levelChange->play();
  m_blocksRemoved = (getCurrentLevel()-1) * Globals::blocksPerLevel;
}

int Score::blocksForLevel() 
{ 
  return m_blocksRemoved - ((getCurrentLevel()-1)*Globals::blocksPerLevel); 
}

void Score::shapeSettle()
{
  m_scoresPerShape = 0;

}

void Score::blocksDisappear(int count)
{
  if (count < 1) return;

  m_scoresPerShape++;
  
  if (m_scoresPerShape > 1)
  {
    m_snd_multiBonus->play();
  }

  float multiplier = 1;
  if (count > Globals::minimumMatch)
  {
    multiplier = (count - Globals::minimumMatch) * Globals::scoreMultipier;
  }

  int pointsPerBlock = (int)((float)Globals::baseScore * multiplier);

  int points = count * pointsPerBlock;

  multiplier = 1;
  if (m_scoresPerShape > 1)
  {
    multiplier = (m_scoresPerShape - 1) * Globals::multiMatchBonusMultiplier;
  }
  points = (int)((float)points * multiplier);
  
  addBlocksRemoved(count);
  addScore(points);
}

void Score::clearBoard()
{
  addScore(Globals::clearBoardBonus);
}

void Score::levelBonus(int emptyCells)
{
  addScore(Globals::levelBonus * emptyCells);
}

void Score::dispatchScoreChange()
{
  m_scoreChangeEvent.currentScore = m_score;
  m_scoreChangeEvent.changeAmmount = m_lastPoints;

  set<ScoreListener*>::iterator i;
  for (i=m_listeners.begin(); i!=m_listeners.end(); i++)
  {
    (*i)->scoreChanged(&m_scoreChangeEvent);
  }
}

void Score::dispatchLevelChange()
{
  m_levelChangeEvent.currentLevel = getCurrentLevel();
  set<ScoreListener*>::iterator i;
  for (i=m_listeners.begin(); i!=m_listeners.end(); i++)
  {
    (*i)->levelChanged(&m_levelChangeEvent);
  }

//  Globals::console->println("Level %d", getCurrentLevel());
//  Globals::console->println("Black Barrel Probability = %02d%%", getBlackProbability());
//  Globals::console->println("Wild Barrel Probability = %02d%%", getWildProbability());
//  Globals::console->println("Start Rows = %02d", getNumRowsToPrimeBoardWith());
}

  

int Score::getWildProbability()
{
  int wildProb = 0;
  if (Score::getCurrentLevel() >= Globals::introduceWildBlocks)
  {
    int levelsPast = Score::getCurrentLevel() - Globals::introduceWildBlocks;
    wildProb = Globals::wildBlockMaximumProbability - levelsPast;
    if (wildProb < Globals::wildBlockMinimumProbability)
    {
      wildProb = Globals::wildBlockMinimumProbability;
    }
  }
  return wildProb;
}

int Score::getBlackProbability()
{
  int blackProb = 0;
  if (getCurrentLevel() >= Globals::introduceBlackBlocks)
  {
    
    int levelsPast = Score::getCurrentLevel() - Globals::introduceBlackBlocks;
    blackProb = Globals::blackBlockMinimumProbability + levelsPast;
    if (blackProb > Globals::blackBlockMaximumProbability)
    {
      blackProb = Globals::blackBlockMaximumProbability;
    }
  }    
  return blackProb;
}

int Score::getNumRowsToPrimeBoardWith()
{
  int numRows = 0;
  if (getCurrentLevel() >= Globals::introducePrimedRows)
  {
    int levelsPast = getCurrentLevel() - Globals::introducePrimedRows;
    numRows = 1 + (levelsPast/Globals::levelsPerPrimedRow);
    if (numRows > Globals::primedRowsMaximum)
    {
      numRows = Globals::primedRowsMaximum;
    }
  }
  return numRows;
}

int Score::getBlocksPerLevel()
{
  int blocks = Globals::blocksPerLevel;
  return blocks;
}