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
	//SoundSystem_Init();

	//MISSING GAME TIME LOOP----


	GameStateMgrInit(GS_PAUSE); //for now its level one, once menu is done change it

	//GameStateMgrInit(GS_PAUSE); //for now its level one, once menu is done change it

	
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
