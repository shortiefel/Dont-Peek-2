/* Start Header ************************************************************************/
/*!
\file Main.h
\team name Don't Peak
\software name I don't want to do homework
\authors

Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief This file is done by Felicia. In this file, it contains the function which enable the
the windows to appear and the states of how the gamestate will run.


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/



#include "Main.h"
#include "GameState_DontPeek.h"
#include "GameStateMgr.h"
#include "Music.h"
#include <memory>

//-----------GLOBALs-----------
float g_dt;
double g_appTime;
bool CheckPause;


/******************************************************************************/
/*!
	STARTING POINT OF THE APPLICATION
*/
/******************************************************************************/
int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
	UNREFERENCED_PARAMETER(prevInstanceH);
	UNREFERENCED_PARAMETER(command_line);

	// Enable run-time memory check for debug builds.
	  #if defined(DEBUG) | defined(_DEBUG)
	  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	  #endif
	 // int* pi = new int;

	//------------INITILIZATION----------------
	AESysInit(instanceH, show, 1000, 700, 1, 60, false, NULL);
	AESysSetWindowTitle("Don't Peek");
	AEGfxSetBackgroundColor(100.0f, 100.0f, 100.0f);
	Fonts = AEGfxCreateFont("Resources/Arial Italic.ttf", 25);
	//SoundSystem_Init();

	//MISSING GAME TIME LOOP----


	GameStateMgrInit(GS_SPLASH); //for now its level one, once menu is done change it

	//GameStateMgrInit(GS_PAUSE); //for now its level one, once menu is done change it

		//Fonts = AEGfxCreateFont("Resources/Arial Italic.ttf", 25);
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
			if ((AESysDoesWindowExist() == false))
			{
				gGameStateNext = GS_QUIT;
			}

			g_dt = (f32)AEFrameRateControllerGetFrameTime();
			g_appTime += g_dt;
		}

		//SoundSystem_Destroy();
		GameStateFree();

		if (gGameStateNext != GS_RESTART)
			GameStateUnload();

		gGameStatePrev = gGameStateCurr;
		gGameStateCurr = gGameStateNext;
	}
	
	//freeing the system
	AESysExit();
}
