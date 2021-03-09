/* Start Header ************************************************************************/
/*!
\file Main.cpp
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
#include "Main.h"
#include "GameState_DontPeek.h"
#include "GameStateMgr.h"

//-----------GLOBALs-----------
float g_dt;
double g_appTime;

/******************************************************************************/
/*!
	STARTING POINT OF THE APPLICATION
*/
/******************************************************************************/
int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
	UNREFERENCED_PARAMETER(prevInstanceH);
	UNREFERENCED_PARAMETER(command_line);

	//------------INITILIZATION----------------
	AESysInit(instanceH, show, WINDOW_HEIGHT, WINDOW_WIDTH, 1, 60, false, NULL);
	AESysSetWindowTitle("Don't Peek");
	AEGfxSetBackgroundColor(100.0f, 100.0f, 100.0f);

	//MISSING GAME TIME LOOP----

	GameStateMgrInit(GS_DONT_PEEK);
	
	while (gGameStateCurr != GS_QUIT)
	{
		//reset system modules
		AESysReset();

		//if game is not restarting, load gamestate
		if (gGameStateCurr != GS_RESTART)
		{
			GameStateMgrUpdate();
			GameStateLoad();
		}
		else
			gGameStateNext = gGameStateCurr = gGameStatePrev;

		//Initialize gamestate
		GameStateInit();

		while (gGameStateCurr == gGameStateNext)
		{
			AESysFrameStart();
			AEInputUpdate();
			GameStateUpdate();
			GameStateDraw();
			AESysFrameEnd();

			//checking if application is being forced to quit
			if ((AESysDoesWindowExist() == false || AEInputCheckTriggered(AEVK_ESCAPE)))
			{
				g_dt = (f32)AEFrameRateControllerGetFrameTime();
				g_appTime += g_dt;
			}
		}

		GameStateFree();

		if (gGameStateNext != GS_RESTART)
			GameStateUnload();

		gGameStatePrev = gGameStateCurr;
		gGameStateCurr = gGameStateNext;
	}

	//freeing the system
	AESysExit();
}
