/* Start Header ************************************************************************/
/*!
\file GameStateMgr.cpp
\team name Don't Peek
\software name I Don't Wanna Do My Homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/02/2021
\brief
This file contains all the functions that is required to manage our game state.


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/
#include "GameStateMgr.h"
#include "SplashScreen.h"
#include "Menu.h"
#include "HowToPlay2.h"
#include "Tutorial.h"
#include "Level 1.h"
#include  "Win.h"
#include "Lose.h"
#include "Pause.h"
#include "Credits.h"
#include "Level Select.h"
#include "Restart.h"
#include "Rules.h"


/******************************************************************************/
/*!
	GLOBALS

*/
/******************************************************************************/

// variables to keep track the current, previous and next game state
unsigned int	gGameStateInit;
unsigned int	gGameStateCurr;
unsigned int	gGameStatePrev;
unsigned int	gGameStateNext;


// pointer to functions for game state life cycles functions
void (*GameStateLoad)() = 0;
void (*GameStateInit)() = 0;
void (*GameStateUpdate)() = 0;
void (*GameStateDraw)() = 0;
void (*GameStateFree)() = 0;
void (*GameStateUnload)() = 0;

/******************************************************************************/
/*!
	GAME STATE MANAGER INIT
*/
/******************************************************************************/

void GameStateMgrInit(unsigned int gameStateInit)
{
	// set the initial game state
	gGameStateInit = gameStateInit;

	// reset the current, previoud and next game
	gGameStateCurr =
	gGameStatePrev =
	gGameStateNext = gGameStateInit;

	// call the update to set the function pointers
	GameStateMgrUpdate();
}

/******************************************************************************/
/*!
	GAME STATE MANAGER UPDATE
*/
/******************************************************************************/
void GameStateMgrUpdate()
{
	if ((gGameStateCurr == GS_RESTART) || (gGameStateCurr == GS_QUIT))
		return;

	switch (gGameStateCurr)
	{
	case GS_SPLASH:
		GameStateLoad = SSLoad;
		GameStateInit = SSInit;
		GameStateUpdate = SSUpdate;
		GameStateDraw = SSDraw;
		GameStateFree = SSFree;
		GameStateUnload = SSUnload;
		break;

	case GS_MENU:
		GameStateLoad = MenuLoad;
		GameStateInit = MenuInit;
		GameStateUpdate = MenuUpdate;
		GameStateDraw = MenuDraw;
		GameStateFree = MenuFree;
		GameStateUnload = MenuUnload;
		break;

	case GS_TUTORIAL:
		GameStateLoad = HowtoplayLoad;
		GameStateInit = HowtoplayInit;
		GameStateUpdate = HowtoplayUpdate;
		GameStateDraw = HowtoplayDraw;
		GameStateFree = HowtoplayFree;
		GameStateUnload = HowtoplayUnload;
		break;

	case GS_LEVEL_1:
		GameStateLoad = Level1_Load;
		GameStateInit = Level1_Init;
		GameStateUpdate = Level1_Update;
		GameStateDraw = Level1_Draw;
		GameStateFree = Level1_Free;
		GameStateUnload = Level1_Unload;
		break;

	case GS_DONT_PEEK:
		GameStateLoad = GameStateDontPeekLoad;
		GameStateInit = GameStateDontPeekInit;
		GameStateUpdate = GameStateDontPeekUpdate;
		GameStateDraw = GameStateDontPeekDraw;
		GameStateFree = GameStateDontPeekFree;
		GameStateUnload = GameStateDontPeekUnload;
		break;

	case GS_WIN:
		GameStateLoad = WinLoad;
		GameStateInit = WinInit;
		GameStateUpdate = WinUpdate;
		GameStateDraw = WinDraw;
		GameStateFree = WinFree;
		GameStateUnload = WinUnload;
		break;

	case GS_LOSE:
		GameStateLoad = LoseLoad;
		GameStateInit = LoseInit;
		GameStateUpdate = LoseUpdate;
		GameStateDraw = LoseDraw;
		GameStateFree = LoseFree;
		GameStateUnload = LoseUnload;
		break;

	case GS_PAUSE:
		GameStateLoad = PauseLoad;
		GameStateInit = PauseInit;
		GameStateUpdate = PauseUpdate;
		GameStateDraw = PauseDraw;
		GameStateFree = PauseFree;
		GameStateUnload = PauseUnload;
		break;

	case GS_CREDITS:
		GameStateLoad = CreditsLoad;
		GameStateInit = CreditsInit;
		GameStateUpdate = CreditsUpdate;
		GameStateDraw = CreditsDraw;
		GameStateFree = CreditsFree;
		GameStateUnload = CreditsUnload;
		break;

	case GS_LEVEL:
		GameStateLoad = LevelSelectLoad;
		GameStateInit = LevelSelectInit;
		GameStateUpdate = LevelSelectUpdate;
		GameStateDraw = LevelSelectDraw;
		GameStateFree = LevelSelectFree;
		GameStateUnload = LevelSelectUnload;
		break;


	case GS_RESTART:

		GameStateLoad = RestartLoad;
		GameStateInit = RestartInit;
		GameStateUpdate = RestartUpdate;
		GameStateDraw = RestartDraw;
		GameStateFree = RestartFree;
		GameStateUnload = RestartUnload;
		break;

	case GS_RULE:
		GameStateLoad = RulesLoad;
		GameStateInit = RulesInit;
		GameStateUpdate = RulesUpdate;
		GameStateDraw = RulesDraw;
		GameStateFree = RulesFree;
		GameStateUnload = RulesUnload;
		break;

	default:
		AE_FATAL_ERROR("invalid state!!");
	}
}