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
#include "Loading.h"

/******************************************************************************/
/*!
	DEFINES
*/
/******************************************************************************/
GameObj				sGameObjList[GAME_OBJ_NUM_MAX];				// Each element in this array represents a unique game object (shape)
unsigned long		sGameObjNum;

static float		loadingTimer;
static float		Time;
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
static Loading loading;

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

	/*===============================================================================
		LOADING SCREEN
	=================================================================================*/
	loading.pos = { 0, 0 };
	loading.scale = { 950.f,650.f };

	loading.pObj = sGameObjList + sGameObjNum++;
	loading.pObj->texture = AEGfxTextureLoad("Resources/loading.jpg");
	AE_ASSERT_MESG(loading.pObj->texture, "Failed to load SplashScreen!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	loading.pObj->pMesh = AEGfxMeshEnd();

	/*===============================================================================
		SCALING/TRANSFORMATION/CONCAT FOR LOADING SCREEN
	=================================================================================*/
	AEMtx33	trans, sc;
	// Compute the scaling matrix
	AEMtx33Scale(&sc, loading.scale.x, loading.scale.y);
	// Compute the translation matrix
	AEMtx33Trans(&trans, loading.pos.x, loading.pos.y);

	AEMtx33Concat(&(loading.transform), &trans, &sc);

	/*===============================================================================
		OBJECT FUNCTIONS
	=================================================================================*/
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
	CheckPause = false;
	loadingTimer = 2;
	SoundSystem_Init();
	SoundSystem_SFX();

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
	//For our pause state
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
		Time += g_dt;
		Level1_Update();
		wall.UpdateWall();
		sharpener.UpdateSharpener();
		eraser.UpdateEraser();
		highlighter.UpdateHighlighter();
		pencil.UpdatePencil();
		door.UpdateDoor();
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
	if (Time > loadingTimer)
	{
		//For our pause state
		if (CheckPause == true)
		{
			/*===============================================================================
				DRAW PAUSE SCREEN
			=================================================================================*/
			PauseDraw();
		}
		else if (CheckPause == false)
		{
			/*===============================================================================
				DRAW GAME LEVEL & OBJECT
			=================================================================================*/
			Level1_Draw();
			wall.DrawWall();
			sharpener.DrawSharpener();
			eraser.DrawEraser();
			highlighter.DrawHighlighter();
			pencil.DrawPencil();
			door.DrawDoor();
			player.Player_Draw();
		}
	}
	else
	{
		/*===============================================================================
			DRAW LOADING SCREEN
		=================================================================================*/
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(0, 0);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxTextureSet(loading.pObj->texture, 0, 0);
		AEGfxSetTransform(loading.transform.m);
		AEGfxSetTransparency(1.0f);
		AEGfxMeshDraw(loading.pObj->pMesh, AE_GFX_MDM_TRIANGLES);
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
	wall.FreeWall();
	sharpener.FreeSharpener();
	eraser.FreeEraser();
	highlighter.FreeHighlighter();
	pencil.FreePencil();
	door.FreeDoor();
	player.Player_Free();
}

/******************************************************************************/
/*!
	"UNLOAD" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekUnload(void)
{
	/*===============================================================================
		UNLOAD LOADING TEXTURE & MESH
	=================================================================================*/
	if (loading.pObj->pMesh)
		AEGfxMeshFree(loading.pObj->pMesh);
	if (loading.pObj->texture)
		AEGfxTextureUnload(loading.pObj->texture);

	/*===============================================================================
		UNLOAD LEVEL & OBJECT TEXTURE & MESH
	=================================================================================*/
	Level1_Unload();
	PauseUnload();

	wall.UnloadWall();
	sharpener.UnloadSharpener();
	eraser.UnloadEraser();
	highlighter.UnloadHighlighter();
	pencil.UnloadPencil();
	door.UnloadDoor();
	player.Player_Unload();
}