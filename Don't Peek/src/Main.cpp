#include "Main.h"


//--------GLOBAL-------

float g_dt;
double g_appTime;

/******************************************************************************/
/*!
	Starting point of the application
*/
/******************************************************************************/

int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
	UNREFERENCED_PARAMETER(prevInstanceH);
	UNREFERENCED_PARAMETER(command_line);

	//Initilization 
	AESysInit(instanceH, show, 1080, 1920, 1, 60, false, NULL);
	AESysSetWindowTitle("Don't Peek");
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);


}