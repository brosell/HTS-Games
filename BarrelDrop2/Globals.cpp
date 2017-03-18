#pragma warning (disable : 4786 4503 4530)

#include "Globals.h"
#include "IniFile.h"
#include "FileManager.h"

CStdString Globals::versionString;

bool Globals::isDemo = true;
bool Globals::endGame = false;
bool Globals::run = true;
bool Globals::survivorMode = false;
int Globals::pointsForLandingBlock = 0;
int Globals::minimumMatch = 0;
int Globals::baseScore = 0;
float Globals::scoreMultipier = 0;
int Globals::wildBlockPoints = 0;
int Globals::clearBoardBonus = 0;
float Globals::multiMatchBonusMultiplier = 0;
int Globals::levelBonus = 0;

int Globals::blocksPerLevel = 0;
bool Globals::clearBlocksAtLevelUp = 0;
int Globals::straightBlockProbability = 0;

int Globals::introduceWildBlocks = 0;
int Globals::wildBlockMinimumProbability = 0;
int Globals::wildBlockMaximumProbability = 0;

int Globals::introduceBlackBlocks = 0;
int Globals::blackBlockMinimumProbability = 0;
int Globals::blackBlockMaximumProbability = 0;

int Globals::introducePrimedRows = 0;
int Globals::levelsPerPrimedRow = 0;
int Globals::primedRowsMaximum = 0;


int Globals::initialSpeed = 0;
int Globals::speedIncreaseUsePercentage = 0;
int Globals::speedIncreasePerLevel = 0;
int Globals::minimumSpeed = 0;

AssetManager* Globals::assetManager = 0;
AM* Globals::am = 0;
Console* Globals::console = 0;

string Globals::skill = "";

void Globals::init(string fn)
{
//  IniFile ini_scoring(fn);
//
//  ini_scoring.read();
//  pointsForLandingBlock = ini_scoring.getInt("Scoring", "PointsForLandingBlock");
//  minimumMatch = ini_scoring.getInt("Scoring", "MinimumMatch");
//  baseScore = ini_scoring.getInt("Scoring", "BaseScore");
//  scoreMultipier = ini_scoring.getFloat("Scoring", "Multiply");
//  wildBlockPoints = ini_scoring.getInt("Scoring", "WildBlockPoints");
//  clearBoardBonus = ini_scoring.getInt("Scoring", "ClearBoardBonus");
//  multiMatchBonusMultiplier = ini_scoring.getFloat("Scoring", "MultiMatchBonusMultiplier");
//  levelBonus = ini_scoring.getInt("Scoring", "LevelBonus");
//
////  blocksPerLevel = ini_scoring.getFloat("GameDetails", "BlocksPerLevel");
//  clearBlocksAtLevelUp = (ini_scoring.getInt("GameDetails", "ClearBlocksAtLevelUp")==1?true:false);
//  straightBlockProbability = ini_scoring.getInt("GameDetails", "StraightBlockProbability");
//  
//  introduceWildBlocks = ini_scoring.getInt("GameDetails", "IntroduceWildBlocks");
//  wildBlockMinimumProbability = ini_scoring.getInt("GameDetails", "WildBlockMinimumProbability");
//  wildBlockMaximumProbability = ini_scoring.getInt("GameDetails", "WildBlockMaximumProbability");
//  
//  introduceBlackBlocks = ini_scoring.getInt("GameDetails", "IntroduceBlackBlocks");
//  blackBlockMinimumProbability = ini_scoring.getInt("GameDetails", "BlackBlockMinimumProbability");
//  blackBlockMaximumProbability = ini_scoring.getInt("GameDetails", "BlackBlockMaximumProbability");
//
//  introducePrimedRows = ini_scoring.getInt("GameDetails", "IntroducePrimedRows");;
//  levelsPerPrimedRow = ini_scoring.getInt("GameDetails", "LevelsPerPrimedRow");;
//  primedRowsMaximum = ini_scoring.getInt("GameDetails", "PrimedRowMaximum");;;
//
//
////  initialSpeed = ini_scoring.getFloat("GameDetails", "InitialSpeed");
//  speedIncreaseUsePercentage = ini_scoring.getFloat("GameDetails", "SpeedIncreaseUsePercentage");
//  speedIncreasePerLevel = ini_scoring.getFloat("GameDetails", "SpeedIncreasePerLevel");
//  minimumSpeed = ini_scoring.getFloat("GameDetails", "MinimumSpeed");

  IniFile version("Version.ini");
  version.read();

  int major = version.getInt("Version", "Major");
  int minor = version.getInt("Version", "Minor");
  int build = version.getInt("Version", "Build");

  isDemo = !FileManager::fileExists("Unlocker.txt");

  if (!isDemo)
  {
    versionString.Format("%d.%d.%d", major, minor, build);
  }
  else
  {
    versionString.Format("%d.%d.%d DEMO", major, minor, build);
  }

  logError(Inform, "BarrelDrop! version %s", Globals::versionString.c_str());
  string datetime = version["Version"]["Timestamp"];
  if (datetime != "")
  logError(Inform, "Built %s", datetime.c_str());
}
