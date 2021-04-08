/* Start Header ************************************************************************/
/*!
\file GameState_DontPeek.cpp
\team name Don't Peek
\software name I Don't Wanna Do My Homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief 
This file contains all the functions that is required for our level 1 game state.
It will call each individual objects that is required to build the level 1.


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
#include "Level 1.h"
#include "Win.h"
#include "Music.h"
#include "Pause.h"
#include "Animation.h"
#include "loading.h"


/******************************************************************************/
/*!
	DEFINES
*/
/******************************************************************************/
GameObj				sGameObjList[GAME_OBJ_NUM_MAX];				// Each element in this array represents a unique game object (shape)
unsigned long		sGameObjNum;
float static	loadingTime = 2;
float totaltime2;

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
Sprite anim;
Loading loading1;


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


	/******************************************************************************/
	/*!
		LOADING SCREEN
	*/
	/******************************************************************************/
	loading1.pos = { 0, 0 };
	loading1.scale = { 950.f,650.f };

	loading1.pObj = sGameObjList + sGameObjNum++;
	loading1.pObj->texture = AEGfxTextureLoad("Resources/loading.jpg");
	AE_ASSERT_MESG(loading1.pObj->texture, "Failed to load SplashScreen!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	loading1.pObj->pMesh = AEGfxMeshEnd();

	AEMtx33	trans, sc;
	// Compute the scaling matrix
	AEMtx33Scale(&sc, loading1.scale.x, loading1.scale.y);
	// Compute the translation matrix
	AEMtx33Trans(&trans, loading1.pos.x, loading1.pos.y);

	AEMtx33Concat(&(loading1.transform), &trans, &sc);

	/******************************************************************************/
	/*!
		FUNCTIONS FOR LOADING
	*/
	/******************************************************************************/


	Level1_Load();
	PauseLoad();
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
	totaltime2 += g_dt;

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
	if (totaltime2 > loadingTime)
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
	else
	{
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(0, 0);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxTextureSet(loading1.pObj->texture, 0, 0);
		AEGfxSetTransform(loading1.transform.m);
		AEGfxSetTransparency(1.0f);
		AEGfxMeshDraw(loading1.pObj->pMesh, AE_GFX_MDM_TRIANGLES);
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
	Level1_Free();
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
	PauseUnload();
	sharpener.UnloadSharpener();
	eraser.UnloadEraser();
	highlighter.UnloadHighlighter();
	pencil.UnloadPencil();
	door.UnloadDoor();
	player.Player_Unload();
	wall.UnloadWall();
}