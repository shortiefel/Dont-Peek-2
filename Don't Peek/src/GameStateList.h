#pragma once
///----------GAME STATE LIST---------------

enum 
{
	///list of all game states
	GS_DONT_PEEK = 0,
	GS_MENU,
	GS_TUTORIAL,

	GS_LEVEL,
	GS_CREDITS,
	GS_WIN,
	GS_LOSE,
	GS_PAUSE,
	//Special Game State. DONT CHANGE HOR
	GS_RESTART,
	GS_QUIT,
	GS_NONE
};


