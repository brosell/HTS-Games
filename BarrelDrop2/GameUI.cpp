#pragma warning (disable : 4786 4503 4530)
#include "GameUI.h"
#include "Convert.h"
#include "Wizard.h"
#include "IniFile.h"
#include "ToggleButton.h"
#include "HighScoresDialog.h"

GameListener gameListener;
GameConsoleListener consoleListener;
EnterHighScoreListener enterHighScoreListener;
OptionsListener optionsListener;
MenuListener menuListener;


IniBasedDialog* dia_gameScreen = 0;
WorldCanvas* wc_worldCanvas = 0;
SpecialTextCanvas* scvs_specialNotices = 0;
ProgressBar* prg_progress = 0;

IniBasedDialog* dia_mainScreen = 0;

GameModeDialog* dia_chooseGameModeScreen = 0;

IniBasedDialog* dia_creditsScreen = 0;
IniBasedDialog* dia_highScoresScreen = 0;
OptionsDialog* dia_options = 0;

IniBasedDialog* dia_enterHighScoreScreen = 0;
TextBox* txt_highScoreName = 0;
Label* txt_highScoreScore = 0;
Label* txt_highScoreLevel = 0;

IniBasedDialog* dia_gameOverScreen = 0;
Label* txt_gameOverScore = 0;
Label* txt_gameOverLevel = 0;

IniBasedDialog* dia_areYouSure = 0;

IniBasedDialog* dia_demoOverScreen = 0;

NextShapeCanvas* cvs_nextShape = 0;

IniBasedDialog* dia_current = 0;

void initConsoleCommands();

void initUI()
{
  UIThing::s_ocheck = false;

//  theGame.setMouse("mouse_Default", 7, 7);
  theGame.uiSystem.setMouseCursor("mouse_Default");
  theGame.showCursor(true);

  Globals::console = new Console;
  initConsoleCommands();

  IniFile dialogs("UI\\Dialogs.ini");
  dialogs.read();
  
  //////////////// GAME SCREEN
  dia_gameScreen = new GameDialog(dialogs, "Game");
  cvs_nextShape = new NextShapeCanvas;
  UIThing* placeholder = dia_gameScreen->getControlByName("NextPiecePlaceHolder");
  cvs_nextShape->setPosition(placeholder->getPosition());

  dia_gameScreen->addUIThing(cvs_nextShape);
  wc_worldCanvas = (WorldCanvas*)dia_gameScreen->getControlByName("PlayField");

  prg_progress = (ProgressBar*)dia_gameScreen->getControlByName("Progress");

  scvs_specialNotices = new SpecialTextCanvas();
  scvs_specialNotices->setPosition(Rect(100, 15, 360, 360));
  dia_gameScreen->addUIThing(scvs_specialNotices);
  
  //////////////// MAIN MENU
  dia_mainScreen = new IniBasedDialog(dialogs, "Main");
  Button* start = (Button*)dia_mainScreen->getControlByName("StartButton");
  start->addActionListener(&menuListener);

  Button* quit = (Button*)dia_mainScreen->getControlByName("QuitButton");
  quit->addActionListener(&menuListener);

  Button* credits = (Button*)dia_mainScreen->getControlByName("CreditsButton");
  credits->addActionListener(&menuListener);

  Button* instruction = (Button*)dia_mainScreen->getControlByName("InstructionButton");
  instruction->addActionListener(&menuListener);

  Button* highScores = (Button*)dia_mainScreen->getControlByName("HighScoresButton");
  highScores->addActionListener(&menuListener);

  Button* options = (Button*)dia_mainScreen->getControlByName("OptionsButton");
  options->addActionListener(&menuListener);

  Label* version = (Label*)dia_mainScreen->getControlByName("Version");
  version->setText(Globals::versionString);

  dia_chooseGameModeScreen = new GameModeDialog(dialogs, "ChooseGameMode");
  
  //////////// CREDITS
  dia_creditsScreen = new IniBasedDialog(dialogs, "Credits");

  //////////// INSTRUCTIONS
//  dia_instructionScreen = new Wizard(dialogs, "InstructionsWizard");

  //////////// HIGHSCORES
  dia_highScoresScreen = new HighScoresDialog(dialogs, "HighScores");

  //////////// ENTER HIGHSCORE
  dia_enterHighScoreScreen = new FireworksDialog(dialogs, "EnterHighScore");
  Button* OK = (Button*)dia_enterHighScoreScreen->getControlByName("OkButton");
  OK->addActionListener(&enterHighScoreListener);
  TextBox* name = dynamic_cast<TextBox*>(dia_enterHighScoreScreen->getControlByName("TxtName"));
  name->addKeyListener(&enterHighScoreListener);

  txt_highScoreName = (TextBox*)dia_enterHighScoreScreen->getControlByName("TxtName");
  txt_highScoreScore = (Label*)dia_enterHighScoreScreen->getControlByName("TxtScore");
  txt_highScoreLevel = (Label*)dia_enterHighScoreScreen->getControlByName("TxtLevel");

  //////////// GAMEOVER
  dia_gameOverScreen = new IniBasedDialog(dialogs, "GameOver");
  OK = (Button*)dia_gameOverScreen->getControlByName("OkButton");
  OK->addActionListener(&menuListener);

  txt_gameOverScore = (Label*)dia_gameOverScreen->getControlByName("TxtScore");
  txt_gameOverLevel = (Label*)dia_gameOverScreen->getControlByName("TxtLevel");

  dia_demoOverScreen = new IniBasedDialog(dialogs, "dlg_DemoOver");


  /////////////// ARE YOU SURE
  dia_areYouSure = new IniBasedDialog(dialogs, "dlg_AreYouSure");

  /////////////// OPTIONS
  dia_options = new OptionsDialog(dialogs, "dlg_Options");
  dia_options->addListener(&optionsListener);

  theGame.uiSystem.addKeyListener(&consoleListener);
}

void cleanupUI()
{
  delete dia_creditsScreen;
  delete dia_enterHighScoreScreen;
  delete dia_gameOverScreen;
  delete dia_gameScreen;
  delete dia_highScoresScreen;
//  delete dia_instructionScreen;
  delete dia_mainScreen;
  delete dia_options;
  delete dia_areYouSure;
  delete dia_chooseGameModeScreen;
  delete cvs_nextShape;
  delete scvs_specialNotices;

}


void showCredits()
{
  bool mouse = theGame.showCursor(true);
  dia_mainScreen->hide();
  dia_creditsScreen->doModal();
  dia_mainScreen->show();
  theGame.showCursor(mouse);
}

//void showInstruction()
//{
//  bool mouse = theGame.showCursor(true);
//  dia_instructionScreen->doModal();
//  theGame.showCursor(mouse);
//}

void showOptions()
{
  bool mouse = theGame.showCursor(true);
  dia_mainScreen->hide();
  dia_options->doModal();
  dia_mainScreen->show();
  theGame.showCursor(mouse);
}


void showHighScores()
{
  bool mouse = theGame.showCursor(true);
  dia_mainScreen->hide();
  dia_highScoresScreen->doModal();
  dia_mainScreen->show();
  theGame.showCursor(mouse);
}


void showEnterHighScoreScreen()
{
  bool mouse = theGame.showCursor(true);
  txt_highScoreName->setText("");
  txt_highScoreScore->setText(toString(g_lastScore).c_str());
  txt_highScoreLevel->setText(toString(g_lastLevel).c_str());
  dia_enterHighScoreScreen->setFocus(txt_highScoreName);

  dia_mainScreen->hide();
  dia_enterHighScoreScreen->doModal();
  dia_mainScreen->show();
  
  showHighScores();
//showMainScreen();
  theGame.showCursor(mouse);
}

void showGameOver()
{
  bool mouse = theGame.showCursor(true);
  
  txt_gameOverScore->setText(toString(g_lastScore).c_str());
  txt_gameOverLevel->setText(toString(g_lastLevel).c_str());
  
  dia_mainScreen->hide();
  dia_gameOverScreen->doModal();
  dia_mainScreen->show();
  theGame.showCursor(mouse);
}

void showDemoOver()
{
  bool mouse = theGame.showCursor(true);
  dia_mainScreen->hide();
  dia_demoOverScreen->doModal();
  dia_mainScreen->show();
  theGame.showCursor(mouse);
}

void showMainScreen()
{
}
void prepareGame(string fn);
void showQuickStart();

void showChooseMode()
{
  bool acceptableAnswer = false;
  while ( !acceptableAnswer )
  {
    dia_mainScreen->hide();
    int res = dia_chooseGameModeScreen->doModal();
    dia_mainScreen->show();
    ToggleButton* survivor = dynamic_cast<ToggleButton*>(dia_chooseGameModeScreen->getControlByName("SurvivorToggle_Survivor"));
    Globals::clearBlocksAtLevelUp = !(survivor->isChecked());
    switch(res)
    {
    case 10:
      prepareGame("Easy.ini");
      showQuickStart();
      startGame();
      acceptableAnswer = true;
      break;
    case 11:
      if (!Globals::isDemo)
      {
        prepareGame("Medium.ini");
        showQuickStart();
        startGame();
        acceptableAnswer = true;
      }
      break;
    case 12:
      if (!Globals::isDemo)
      {
        prepareGame("Hard.ini");
        showQuickStart();
        startGame();
        acceptableAnswer = true;
      }
      break;
    case -1:
      {
        acceptableAnswer = true;
      }
      break;
    }
  }
}

void showQuickStart()
{
  IniFile ini("ui\\dialogs.ini");
  ini.read();
  IniBasedDialog qs(ini, "dlg_QuickStart");
  dia_mainScreen->hide();
  qs.doModal();
  dia_mainScreen->show();
}

void prepareGame(string fn)
{
  IniFile ini_scoring(fn);

  ini_scoring.read();
  Globals::pointsForLandingBlock = ini_scoring.getInt("Scoring", "PointsForLandingBlock");
  Globals::minimumMatch = ini_scoring.getInt("Scoring", "MinimumMatch");
  Globals::baseScore = ini_scoring.getInt("Scoring", "BaseScore");
  Globals::scoreMultipier = ini_scoring.getFloat("Scoring", "Multiply");
  Globals::wildBlockPoints = ini_scoring.getInt("Scoring", "WildBlockPoints");
  Globals::clearBoardBonus = ini_scoring.getInt("Scoring", "ClearBoardBonus");
  Globals::multiMatchBonusMultiplier = ini_scoring.getFloat("Scoring", "MultiMatchBonusMultiplier");
  Globals::levelBonus = ini_scoring.getInt("Scoring", "LevelBonus");

  Globals::blocksPerLevel = ini_scoring.getFloat("GameDetails", "BlocksPerLevel");
//  Globals::clearBlocksAtLevelUp = (ini_scoring.getInt("GameDetails", "ClearBlocksAtLevelUp")==1?true:false);

  Globals::straightBlockProbability = ini_scoring.getInt("GameDetails", "StraightBlockProbability");
  
  Globals::introduceWildBlocks = ini_scoring.getInt("GameDetails", "IntroduceWildBlocks");
  Globals::wildBlockMinimumProbability = ini_scoring.getInt("GameDetails", "WildBlockMinimumProbability");
  Globals::wildBlockMaximumProbability = ini_scoring.getInt("GameDetails", "WildBlockMaximumProbability");
  
  Globals::introduceBlackBlocks = ini_scoring.getInt("GameDetails", "IntroduceBlackBlocks");
  Globals::blackBlockMinimumProbability = ini_scoring.getInt("GameDetails", "BlackBlockMinimumProbability");
  Globals::blackBlockMaximumProbability = ini_scoring.getInt("GameDetails", "BlackBlockMaximumProbability");

  Globals::introducePrimedRows = ini_scoring.getInt("GameDetails", "IntroducePrimedRows");;
  Globals::levelsPerPrimedRow = ini_scoring.getInt("GameDetails", "LevelsPerPrimedRow");;
  Globals::primedRowsMaximum = ini_scoring.getInt("GameDetails", "PrimedRowMaximum");;;

  Globals::initialSpeed = ini_scoring.getFloat("GameDetails", "InitialSpeed");
  Globals::speedIncreaseUsePercentage = ini_scoring.getFloat("GameDetails", "SpeedIncreaseUsePercentage");
  Globals::speedIncreasePerLevel = ini_scoring.getFloat("GameDetails", "SpeedIncreasePerLevel");
  Globals::minimumSpeed = ini_scoring.getFloat("GameDetails", "MinimumSpeed");

  Score::reset(ini_scoring.getInt("GameDetails", "StartLevel") - 1);

  Globals::skill = ini_scoring["Scoring"]["Skill"];

  logError(Inform, "Preparing Game (%s)", fn.c_str());
}