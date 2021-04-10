/* Start Header************************************************************************ /
/*!
\file Howtoplay.cpp
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

#include "Howtoplay2.h"
#include "Door.h"
#include "Player.h"
#include "Sharpener.h"
#include "Eraser.h"
#include "Highlighter.h"
#include "Pencil.h"
#include "Wall.h"
#include "Tutorial.h"
#include "Win.h"
#include "Pause.h"
#include "Music.h"
#include "Loading.h"

static float		loadingTimer;
static float		Time;
static Loading loading;
/******************************************************************************/
/*!
	"LOAD" FUNCTION OF THE STATE
*/
/******************************************************************************/
void HowtoplayLoad(void)
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
	Tutorial_Load();
	PauseLoad();
	wall.LoadWall();
	sharpener.LoadSharpener();
	eraser.LoadEraser();
	highlighter.LoadHighlighter();
	pencil.LoadPencil();
	door.LoadDoor();
	player.Player_Load();
}

void HowtoplayInit(void)
{
	CheckPause = false;
	loadingTimer = 2;
	SoundSystem_Init();
	SoundSystem_SFX();
	CheckPause = false;
	Tutorial_Init();
	wall.InitWall();
	sharpener.InitSharpener();
	eraser.InitEraser();
	highlighter.InitHighlighter();
	pencil.InitPencil();
	door.InitDoor();
	player.Player_Init();
}

void HowtoplayUpdate(void)
{
	totaltime += g_dt;

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
		Tutorial_Update();
		wall.UpdateWall();
		sharpener.UpdateSharpener();
		eraser.UpdateEraser();
		highlighter.UpdateHighlighter();
		pencil.UpdatePencil();
		door.UpdateDoor();
		player.Player_Update();
	}
}

void HowtoplayDraw(void)
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
			Tutorial_Draw();
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

void HowtoplayFree(void)
{
	SoundSystem_Destroy();
	Tutorial_Free();
	wall.FreeWall();
	sharpener.FreeSharpener();
	eraser.FreeEraser();
	highlighter.FreeHighlighter();
	pencil.FreePencil();
	door.FreeDoor();
	player.Player_Free();
}

void HowtoplayUnload(void)
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
	Tutorial_Unload();
	PauseUnload();

	wall.UnloadWall();
	sharpener.UnloadSharpener();
	eraser.UnloadEraser();
	highlighter.UnloadHighlighter();
	pencil.UnloadPencil();
	door.UnloadDoor();
	player.Player_Unload();
}
