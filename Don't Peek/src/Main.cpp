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
	AESysInit(instanceH, show, 1000, 700, 1, 60, false, NULL);
	AESysSetWindowTitle("Don't Peek");
	AEGfxSetBackgroundColor(100.0f, 100.0f, 100.0f);

	//MISSING GAME TIME LOOP----

	GameStateMgrInit(GS_MENU); //for now its level one, once menu is done change it
	
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

		GameStateFree();

		if (gGameStateNext != GS_RESTART)
			GameStateUnload();

		gGameStatePrev = gGameStateCurr;
		gGameStateCurr = gGameStateNext;
	}

	//freeing the system
	AESysExit();
}
