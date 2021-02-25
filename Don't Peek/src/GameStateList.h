#pragma once

#ifndef GAME_STATE_LIST_H
#define GAME_STATE_LIST_H

///----------GAME STATE LIST---------------

enum 
{
	///list of all game states
	GS_DONT_PEEK = 0,

	//Special Game State. DONT CHANGE HOR
	GS_RESTART,
	GS_QUIT,
	GS_NONE
};
#endif // !GAME_STATE_LIST_H

