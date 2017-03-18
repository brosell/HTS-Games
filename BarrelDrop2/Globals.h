
#ifndef Globals_h
#define Globals_h

#include "AssetManager.h"
#include "StdString.h"

#include <string>
using namespace std;
////////////////////////////
// SCORING INI INFO
////////////////////////////
class Console;

#define DEMO_LEVELS 8

class Globals
{
public:
  static void init(string fn);

  static CStdString versionString;

  static bool endGame;
  static bool run;
  static bool survivorMode;
  static int pointsForLandingBlock;
  static int minimumMatch;
  static int baseScore;
  static float scoreMultipier;
  static int wildBlockPoints;
  static int clearBoardBonus;
  static float multiMatchBonusMultiplier;
  static int levelBonus;

  static int blocksPerLevel;
  static bool clearBlocksAtLevelUp;
  static int straightBlockProbability;
  
  static int wildBlockMinimumProbability;
  static int wildBlockMaximumProbability;
  static int introduceWildBlocks;
  
  static int introduceBlackBlocks;
  static int blackBlockMinimumProbability;
  static int blackBlockMaximumProbability;

  static int introducePrimedRows;
  static int levelsPerPrimedRow;
  static int primedRowsMaximum;


  static int initialSpeed;
  static int speedIncreaseUsePercentage;
  static int speedIncreasePerLevel;
  static int minimumSpeed;

  static bool isDemo;


  static string skill;

  static AssetManager* assetManager;
  static AM* am;
  static Console* console;
};

#endif
