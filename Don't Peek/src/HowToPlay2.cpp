/* Start Header************************************************************************ /
/*!
\file HowToPlay2.cpp
\team name Don't Peek
\software name I Don't Wanna Do My Homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu
\date 22/01/2021
\brief 
This file contains all the functions that is required for our Tutorial game state.
It will call each individual objects that is required to build the Tutorial.


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
#include "loading.h"

float totaltime;
Loading loading;

float static loadingTime = 2;

/******************************************************************************/
/*!
	"LOAD" FUNCTION OF THE STATE
*/
/******************************************************************************/
void HowtoplayLoad(void)
{
	/******************************************************************************/
	/*!
		LOADING SCREEN
	*/
	/******************************************************************************/
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

	AEMtx33	trans, sc;
	// Compute the scaling matrix
	AEMtx33Scale(&sc, loading.scale.x, loading.scale.y);
	// Compute the translation matrix
	AEMtx33Trans(&trans, loading.pos.x, loading.pos.y);

	AEMtx33Concat(&(loading.transform), &trans, &sc);

	/******************************************************************************/
	/*!
		FUNCTIONS FOR LOADING
	*/
	/******************************************************************************/

	PauseLoad();
	Tutorial_Load();
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
void HowtoplayInit(void)
{
	SoundSystem_Init();
	SoundSystem_SFX();
	Tutorial_Init();
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

/******************************************************************************/
/*!
	"DRAW" FUNCTION OF THE STATE
*/
/******************************************************************************/
void HowtoplayDraw(void)
{
	if (totaltime > loadingTime)
	{
		if (CheckPause == true)
		{
			PauseDraw();
		}
		else if (CheckPause == false)
		{
			Tutorial_Draw();
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
void HowtoplayFree(void)
{
	SoundSystem_Destroy();
	//printf("TUT IS FREEING\n");
	Tutorial_Free();
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
void HowtoplayUnload(void)
{
	if (loading.pObj->texture)
		AEGfxTextureUnload(loading.pObj->texture);

	PauseUnload();
	wall.UnloadWall();
	sharpener.UnloadSharpener();
	eraser.UnloadEraser();
	highlighter.UnloadHighlighter();
	pencil.UnloadPencil();
	door.UnloadDoor();
	player.Player_Unload();
}
