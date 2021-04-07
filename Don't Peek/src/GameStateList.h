/* Start Header ************************************************************************/
/*!
\file GameStateList.h
\team name Don't Peak
\software name I don't want to do homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief This file is done by Felicia. In this file, it contains an enum of the different
gamestates that is available for usage


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#pragma once
///----------GAME STATE LIST---------------

enum 
{
	///list of all game states
	GS_DONT_PEEK = 0,
	GS_MENU,
	GS_TUTORIAL,
	GS_SPLASH,

	GS_LEVEL,
	GS_CREDITS,
	GS_LEVEL_1,
	GS_WIN,
	GS_LOSE,
	GS_PAUSE,
	GS_RULE,
	//Special Game State. DONT CHANGE HOR
	GS_RESTART,
	GS_QUIT,
	GS_NONE
};


