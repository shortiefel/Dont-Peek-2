/* Start Header ************************************************************************/
/*!
\file GameState_DontPeek.cpp
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

#include "GameState_DontPeek.h"
#include "GameStateMgr.h"
#include "Door.h"
#include "Player.h"
#include "Sharpener.h"
#include "Eraser.h"
#include "Highlighter.h"
#include "Pencil.h"
#include "Wall.h"
#include "Tutorial.h"
#include "Level 1.h"
#include "Win.h"
#include "Music.h"
#include "Pause.h"


/******************************************************************************/
/*!
	DEFINES
*/
/******************************************************************************/
GameObj				sGameObjList[GAME_OBJ_NUM_MAX];				// Each element in this array represents a unique game object (shape)
unsigned long		sGameObjNum;

/******************************************************************************/
/*!
	INDIVIDUAL CLASSES
*/
/******************************************************************************/

Door door;
Player player;
Sharpener sharpener;
Eraser eraser;
Pencil pencil;
Highlighter highlighter;
Wall wall;



/******************************************************************************/
/*!
	"LOAD" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekLoad(void)
{
	memset(sGameObjList, 0, sizeof(GameObj) * GAME_OBJ_NUM_MAX);
	// No game objects (shapes) at this point
	sGameObjNum = 0;

	//Tutorial_Load();
	Level1_Load();
	wall.LoadWall();
	sharpener.LoadSharpener();
	eraser.LoadEraser();
	highlighter.LoadHighlighter();
	pencil.LoadPencil();
	door.LoadDoor();
	player.Player_Load();
}

/******************************************************************************/
/*!
	"INIT" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekInit(void)
{
	SoundSystem_Init();
	SoundSystem_SFX();
	CheckPause = false;
	Level1_Init();
	wall.InitWall();
	sharpener.InitSharpener();
	eraser.InitEraser();
	highlighter.InitHighlighter();
	pencil.InitPencil();
	door.InitDoor();
	player.Player_Init();
}

/******************************************************************************/
/*!
	"UPDATE" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekUpdate(void)
{
	if (AEInputCheckCurr(AEVK_P))
	{
		CheckPause = true;
	}

	if (CheckPause == true)
	{
		PauseUpdate();
	}
	else if (CheckPause == false)
	{
		Level1_Update();
		sharpener.UpdateSharpener();
		eraser.UpdateEraser();
		highlighter.UpdateHighlighter();
		pencil.UpdatePencil();
		door.UpdateDoor();
		wall.UpdateWall();
		player.Player_Update();
	}


}


/******************************************************************************/
/*!
	"DRAW" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekDraw(void)
{
	if (CheckPause == true)
	{
		PauseDraw();
	}
	else if (CheckPause == false)
	{
		Level1_Draw();
		wall.DrawWall();
		highlighter.DrawHighlighter();
		pencil.DrawPencil();
		sharpener.DrawSharpener();
		eraser.DrawEraser();
		door.DrawDoor();
		player.Player_Draw();
	}

}

/******************************************************************************/
/*!
	"FREE" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekFree(void)
{
	SoundSystem_Destroy();
	sharpener.FreeSharpener();
	eraser.FreeEraser();
	highlighter.FreeHighlighter();
	pencil.FreePencil();
	door.FreeDoor();
	player.Player_Free();
	wall.FreeWall();
}

/******************************************************************************/
/*!
	"UNLOAD" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekUnload(void)
{

	Level1_Unload();
	sharpener.UnloadSharpener();
	eraser.UnloadEraser();
	highlighter.UnloadHighlighter();
	pencil.UnloadPencil();
	door.UnloadDoor();
	player.Player_Unload();
	wall.UnloadWall();
}