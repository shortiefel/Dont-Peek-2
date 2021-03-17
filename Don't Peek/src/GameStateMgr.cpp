#include "GameStateMgr.h"


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
	case GS_DONT_PEEK:
		GameStateLoad = GameStateDontPeekLoad;
		GameStateInit = GameStateDontPeekInit;
		GameStateUpdate = GameStateDontPeekUpdate;
		GameStateDraw = GameStateDontPeekDraw;
		GameStateFree = GameStateDontPeekFree;
		GameStateUnload = GameStateDontPeekUnload;
		break;
	case GS_MENU:
		//to fill in

	case GS_TUTORIAL:
		//to fill in

		//case GS_RESTART:
			//GameStateInit = GameStateDontPeekInit;
	default:
		AE_FATAL_ERROR("invalid state!!");
	}


}