#include "GameStateMgr.h"
#include "Menu.h"
#include "Tutorial.h"
#include  "Win.h"
#include "Lose.h"
#include "Pause.h"
#include "Credits.h"

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
	case GS_MENU:
		GameStateLoad = MenuLoad;
		GameStateInit = MenuInit;
		GameStateUpdate = MenuUpdate;
		GameStateDraw = MenuDraw;
		GameStateFree = MenuFree;
		GameStateUnload = MenuUnload;
		break;

	case GS_TUTORIAL:
		GameStateLoad = Tutorial_Load;
		GameStateInit = Tutorial_Init;
		GameStateUpdate = Tutorial_Update;
		GameStateDraw = Tutorial_Draw;
		GameStateFree = Tutorial_Free;
		GameStateUnload = Tutorial_Unload;
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


		//case GS_RESTART:
			//GameStateInit = GameStateDontPeekInit;
	default:
		AE_FATAL_ERROR("invalid state!!");
	}


}