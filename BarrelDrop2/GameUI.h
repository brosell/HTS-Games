#ifndef GameUI_h
#define GameUI_h

#include "NextShapeCanvas.h"
#include "SpecialTextCanvas.h"
#include "OptionsDialog.h"
#include "FireworksDialog.h"
#include "GameModeDialog.h"
#include "GameDialog.h"

#include "Listeners.h"

extern GameListener gameListener;
extern GameConsoleListener consoleListener;
extern EnterHighScoreListener enterHighScoreListener;
extern OptionsListener optionsListener;
extern MenuListener menuListener;

extern IniBasedDialog* dia_gameScreen;
extern WorldCanvas* wc_worldCanvas;
extern SpecialTextCanvas* scvs_specialNotices;
extern ProgressBar* prg_progress;

extern GameModeDialog* dia_chooseGameModeScreen;

extern IniBasedDialog* dia_mainScreen;

extern IniBasedDialog* dia_creditsScreen;
//extern DialogBox* dia_instructionScreen;
extern IniBasedDialog* dia_highScoresScreen;
extern OptionsDialog* dia_options;

extern IniBasedDialog* dia_enterHighScoreScreen;
extern TextBox* txt_highScoreName;
extern Label* txt_highScoreScore;
extern Label* txt_highScoreLevel;

extern IniBasedDialog* dia_gameOverScreen;
extern Label* txt_gameOverScore;
extern Label* txt_gameOverLevel;

extern IniBasedDialog* dia_areYouSure;


extern NextShapeCanvas* cvs_nextShape;

extern IniBasedDialog* dia_current;

void initUI();
void cleanupUI();
void showMainScreen();
void showChooseMode();
void showEnterHighScoreScreen();
void showGameOver();
void showDemoOver();


#endif