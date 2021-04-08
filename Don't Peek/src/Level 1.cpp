/* Start Header ************************************************************************/
/*!
\file Level 1.cpp
\team name Don't Peek
\software name I Don't Wanna Do My Homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief 
This file contains all the functions that is required for creating Level 1.
It determines the number of object  to be create.
It also determine the position of each objects.
It draws the Level1 background as well.
The timer for the level is also set here.


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#include "Level 1.h"
#include "GameStateMgr.h"
#include "Player.h"
#include "Door.h"
#include "Sharpener.h"
#include "Pencil.h"
#include "Eraser.h"
#include "Highlighter.h"
#include "Wall.h"
#include "Music.h"

//Initalization
static float timer = 0;
char strBuffer[100];
char Fonts;

/******************************************************************************/
/*!
	Level 1 Load
	/brief loads background for level
*/
/******************************************************************************/
void Level1_Load()
{
	/*===============================================================================
		LEVEL 1 BACKGROUND SCREEN
	=================================================================================*/
	bg.Bgpos = { 350.f,-200.f };
	bg.Bgscale = { 1.2 * 1760.f, 1.2 * 1090.f };

	bg.pBg = sGameObjList + sGameObjNum++;
	bg.pBg->texture = AEGfxTextureLoad("Resources/Level 1_1.jpg");
	AE_ASSERT_MESG(bg.pBg->texture, "Failed to load Background!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	bg.pBg->pMesh = AEGfxMeshEnd();

	/*===============================================================================
		SCALING/TRANSFORMATION/CONCAT FOR LEVEL 1 BACKGROUND SCREEN
	=================================================================================*/
	AEMtx33	trans, sc;
	// Compute the scaling matrix
	AEMtx33Scale(&sc, bg.Bgscale.x, bg.Bgscale.y);
	// Compute the translation matrix
	AEMtx33Trans(&trans, bg.Bgpos.x, bg.Bgpos.y);

	AEMtx33Concat(&(bg.transform), &trans, &sc);
	printf("level1 LOAD");
}
/******************************************************************************/
/*!
	Level 1 Init
	/brief inits all objects for level
*/
/******************************************************************************/
void Level1_Init()
{
	/*===============================================================================
		LEVEL 1 WIN POINT
	=================================================================================*/
	SetWin({ 1045, 260 });

	/*===============================================================================
		NUMBER OF OBJECTS TO BE CREATED
	=================================================================================*/
	SetDoorNum(8);
	SetSharpenerNum(2);
	SetEraserNum(1);
	SetPencilNum(2);

	/*===============================================================================
		FIRST BOX BORDERS AND PLATFORM
	=================================================================================*/
	wall.CreateWall({ -430,-235 }, { 1,0 }, 22, 30.f, PLATFORM); //floor
	wall.CreateWall({ -430,260 }, { 1,0 }, 22, 30.f, CEILING); // top wall
	wall.CreateWall({ -460,260 }, { 0,-1 }, 17, 30.f, WALL); // left wall
	wall.CreateWall({ -440 + 22 * 30,260 }, { 0,-1 }, 17, 30.f, WALL); // right wall
	wall.CreateWall({ 0, -90 }, { 1,0 }, 20 , 10.f, CEILING); //platform
	wall.CreateWall({ -190, -90 }, { 1,0 }, 23, 10.f, PLATFORM); //platform
	//wall.CreateWall({ 40, 70 }, { 1,0 }, 6, 30.f, CEILING); // cover door

	/*===============================================================================
		FIRST BOX DOORS
	=================================================================================*/
	door.SetDoorPosition(0, { 120 , -160 });//door 0
	door.SetDoorPosition(5, { -220 , 180});//door 5
	door.SetDoorPosition(6, { 120 , -20 - 10});//door 6

	/*===============================================================================
		FIRST BOX PENCIL
	=================================================================================*/
	pencil.SetPencil(0, { 30, -10 }, 20, 160);
	pencil.SetPencil(1, { 120, 60 }, 160, 20);
	wall.CreateWall({ 40, 65 }, { 1,0 }, 21, 10.f, PLATFORM); //cover door



	/*===============================================================================
		SECOND BOX BORDERS AND PLATFORM
	=================================================================================*/
	wall.CreateWall({ -450, -765}, { 1,0 }, 18, 30.f, PLATFORM); //floor
	wall.CreateWall({ -450, -265 }, { 1,0 }, 18, 30.f, CEILING); // top wall
	wall.CreateWall({ -440,-295 }, { 0,-1 }, 16, 30.f, WALL); // left wall
	wall.CreateWall({ 80,-295 }, { 0,-1 }, 16, 30.f, WALL); // right wall

	wall.CreateWall({ -100, -565-40 }, { 1,0 }, 6, 30.f, PLATFORM); //platform lowest
	wall.CreateWall({ -210, -480-40 }, { 1,0 }, 3, 30.f, PLATFORM); //platform mid
	wall.CreateWall({ -410, -410-40 }, { 1,0 }, 5, 30.f, PLATFORM); //platform high

	/*===============================================================================
		SECOND BOX DOORS
	=================================================================================*/
	door.SetDoorPosition(1, { -350 , -695 });//door 1
	door.SetDoorPosition(2, { -20 , -695 });//door 2

	/*===============================================================================
		SECOND BOX ERASER
	=================================================================================*/
	eraser.SetEraserPosition(0, { -300, -370 }); //eraser

	/*===============================================================================
		THIRD BOX BORDERS AND PLATFORM
	=================================================================================*/
	wall.CreateWall({ 715, -790 }, { 1,0 }, 14, 30.f, PLATFORM); //floor
	wall.CreateWall({ 715, -465 }, { 1,0 }, 14, 30.f, CEILING); // top wall
	wall.CreateWall({ 685,-465 }, { 0,-1 }, 11, 30.f, WALL); // left wall
	wall.CreateWall({ 715 + 14 * 30,-465 }, { 0,-1 }, 11, 30.f, WALL); // right wall
	wall.CreateWall({ 715, -650+30 }, { 1,0 }, 6, 30.f, PLATFORM); //platform

	/*===============================================================================
		THIRD BOX DOORS
	=================================================================================*/
	door.SetDoorPosition(3, { 805 , -585+30 });//door 3
	door.SetDoorPosition(4, { 1060 , -720 });//door 4

	/*===============================================================================
		THIRD BOX SHARPENER
	=================================================================================*/
	sharpener.SetSharpenerPosition(0, { 830,-720 }); // sharpener

	/*===============================================================================
		FORTH BOX BORDERS AND PLATFORM
	=================================================================================*/
	wall.CreateWall({ 450, -440 }, { 1,0 }, 24, 30.f, PLATFORM); // floor
	wall.CreateWall({ 680, 280 }, { 1,0 }, 10, 30.f, CEILING); // top wall
	wall.CreateWall({ 650, 280 }, { 0,-1 }, 5, 30.f, CEILING); // top wall
	wall.CreateWall({ 470, 160 }, { 1,0 }, 7, 30.f, CEILING); // top wall
	wall.CreateWall({ 440, 160 }, { 0,-1 }, 21, 30.f, WALL); // left wall
	wall.CreateWall({ 680 + 15*30, 280 }, { 0,-1 }, 24, 30.f, WALL); // right wall

	wall.CreateWall({ 885 ,-340 }, { 1,0 }, 5, 30.f, PLATFORM); //platform lowest
	wall.CreateWall({ 720 ,- 210 }, { 1,0 }, 5, 25.f, PLATFORM); //platform MID
	wall.CreateWall({ 470 ,-250 }, { 1,0 }, 6, 30.f, PLATFORM); //platform MID 2
	wall.CreateWall({ 470 ,-40 }, { 1,0 }, 15, 30.f, PLATFORM); //platform MID 3
	wall.CreateWall({ 960 ,-130 }, { 1,0 }, 6, 30.f, PLATFORM); //platform MID 4
	wall.CreateWall({ 960 ,-210 }, { 1,0 }, 6, 30.f, PLATFORM); //platform MID 4
	wall.CreateWall({ 865 ,110 }, { 1,0 }, 5, 30.f, PLATFORM); //platform MID 5

	/*===============================================================================
		FORTH BOX DOORS
	=================================================================================*/
	door.SetDoorPosition(7, { 530 , -370 });//door 7

	/*===============================================================================
		FORTH BOX SHARPENER
	=================================================================================*/
	sharpener.SetSharpenerPosition(1, { 780, 20 }); // sharpener
	
	/*===============================================================================
		TIMER
	=================================================================================*/
	timer = 150.f;
	printf("level1 INIT\n");
}

/******************************************************************************/
/*!
	Level 1 Update
	/brief updates timer
*/
/******************************************************************************/
void Level1_Update()
{
	/*===============================================================================
		TIMER
	=================================================================================*/
	//printf("timer: %f \n", timer);
	if (timer < 0)
	{
		gGameStateNext = GS_LOSE;
	}
	else
	{
		timer -= g_dt;
	}
}

/******************************************************************************/
/*!
	Level 1 Draw
	\brief draws background
*/
/******************************************************************************/
void Level1_Draw()
{
	/*===============================================================================
		DRAW LEVEL 1 BACKGROUND SCREEN
	=================================================================================*/
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(bg.pBg->texture, 0, 0);
	AEGfxSetTransform(bg.transform.m);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(bg.pBg->pMesh, AE_GFX_MDM_TRIANGLES);
	AEGfxSetTransparency(0.0f);
	/*===============================================================================
		DRAW TIMER
	=================================================================================*/
	sprintf_s(strBuffer, "Timer: %d", (int)timer);
	AEGfxPrint(Fonts, strBuffer, -1.0f, 0.9f, 1.0f, 0.0f, 0.0f, 0.0f);
}

/******************************************************************************/
/*!
	Level 1 Free
	\brief frees level
*/
/******************************************************************************/
void Level1_Free()
{
	SoundSystem_Destroy();
}

/******************************************************************************/
/*!
	Level 1 Unload
	\ unloads textures
*/
/******************************************************************************/
void Level1_Unload()
{
	if (bg.pBg->pMesh)
		AEGfxMeshFree(bg.pBg->pMesh);
	if (bg.pBg->texture)
		AEGfxTextureUnload(bg.pBg->texture);
}