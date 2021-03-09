/* Start Header ************************************************************************/
/*!
\file GameStateMgr.cpp
\team name Don't Peak
\software name I don't want to do homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief <give a brief description of this file>


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/
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

		//case GS_RESTART:
			//GameStateInit = GameStateDontPeekInit;
	default:
		AE_FATAL_ERROR("invalid state!!");
	}


}