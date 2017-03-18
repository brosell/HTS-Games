#ifndef Score_h
#define Score_h

#include "SoundEffect.h"
#include "ProgressBar.h"

#include <set>
using namespace std;

extern ProgressBar* prg_progress;

class ScoreChangeEvent
{
public:
  int currentScore;
  int changeAmmount;
};

class LevelChangeEvent
{
public:
  int currentLevel;
};

class ScoreListener
{
public:
  virtual void scoreChanged(ScoreChangeEvent* ev) { }
  virtual void levelChanged(LevelChangeEvent* ev) { }
};

class Score
{
public:
//  Score();
  static void reset(int level = 1);
  static int getCurrentScore();
  static int getCurrentLevel();

  static void shapeSettle();
  static void blocksDisappear(int count);
  static void levelBonus(int emptyCells);

  static void clearBoard();

  static void addListener(ScoreListener* listener);
  static void removeListener(ScoreListener* listener);

  static void addBonusPts(int pts) { addScore(pts); }

  static int getWildProbability();
  static int getBlackProbability();

  static int getNumRowsToPrimeBoardWith();
  static int getBlocksPerLevel();

private:
  static void levelUp();
  static int blocksForLevel();
  static void addScore(int points);
  static void addBlocksRemoved(int blocks);
  static void dispatchScoreChange();
  static void dispatchLevelChange();

  static int m_score;
  static int m_lastPoints;
  static int m_scoresPerShape;
  static int m_blocksRemoved;
  
  Score(const Score& other);

  static set<ScoreListener*> m_listeners;
  static ScoreChangeEvent m_scoreChangeEvent;
  static LevelChangeEvent m_levelChangeEvent;

  static SoundEffectHandle m_snd_multiBonus;
  static SoundEffectHandle m_snd_levelChange;
};

#endif