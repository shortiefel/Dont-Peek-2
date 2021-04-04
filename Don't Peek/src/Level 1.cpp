/* Start Header ************************************************************************/
/*!
\file Level 1.cpp
\team name Don't Peak
\software name I don't want to do homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief <give a brief description of this file>


Copyright (C) 20xx DigiPen Institute of Technology.
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

static float timer = 0;
char strBuffer[100];
char Fonts;
void Level1_Load()
{
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

	AEMtx33	trans, sc;
	// Compute the scaling matrix
	AEMtx33Scale(&sc, bg.Bgscale.x, bg.Bgscale.y);
	// Compute the translation matrix
	AEMtx33Trans(&trans, bg.Bgpos.x, bg.Bgpos.y);

	AEMtx33Concat(&(bg.transform), &trans, &sc);

}
void Level1_Init()
{
	SetWin({ 1045, 260 });
	SetDoorNum(8);
	//Highlighter
	//SetHighlighterNum(2);
	//Sharperner
	SetSharpenerNum(2);
	//eraser
	SetEraserNum(1);
	//pencil
	SetPencilNum(2);

	//first box
	wall.CreateWall({ -430,-235 }, { 1,0 }, 22, 30.f, PLATFORM); //floor
	wall.CreateWall({ -430,260 }, { 1,0 }, 22, 30.f, CEILING); // top wall
	wall.CreateWall({ -460,260 }, { 0,-1 }, 17, 30.f, WALL); // left wall
	wall.CreateWall({ -440 + 22 * 30,260 }, { 0,-1 }, 17, 30.f, WALL); // right wall
	wall.CreateWall({ 0, -90 }, { 1,0 }, 20 , 10.f, CEILING); //platform
	wall.CreateWall({ -190, -90 }, { 1,0 }, 23, 10.f, PLATFORM); //platform

	//wall.CreateWall({ 40, 70 }, { 1,0 }, 6, 30.f, CEILING); // cover door

	door.SetDoorPosition(0, { 120 , -160 });//door 0
	door.SetDoorPosition(5, { -220 , 180});//door 5
	door.SetDoorPosition(6, { 120 , -20 - 10});//door 6

	pencil.SetPencil(0, { 30, -10 }, 20, 160);
	pencil.SetPencil(1, { 120, 60 }, 160, 20);
	wall.CreateWall({ 40, 65 }, { 1,0 }, 21, 10.f, PLATFORM); //cover door



	//2nd box
	wall.CreateWall({ -450, -765}, { 1,0 }, 18, 30.f, PLATFORM); //floor
	wall.CreateWall({ -450, -265 }, { 1,0 }, 18, 30.f, CEILING); // top wall
	wall.CreateWall({ -440,-295 }, { 0,-1 }, 16, 30.f, WALL); // left wall
	wall.CreateWall({ 80,-295 }, { 0,-1 }, 16, 30.f, WALL); // right wall

	wall.CreateWall({ -100, -565-40 }, { 1,0 }, 6, 30.f, PLATFORM); //platform lowest
	wall.CreateWall({ -210, -480-40 }, { 1,0 }, 3, 30.f, PLATFORM); //platform mid
	wall.CreateWall({ -410, -410-40 }, { 1,0 }, 5, 30.f, PLATFORM); //platform high

	door.SetDoorPosition(1, { -350 , -695 });//door 1
	door.SetDoorPosition(2, { -20 , -695 });//door 2
	eraser.SetEraserPosition(0, { -300, -370 }); //eraser

	//3rd box
	wall.CreateWall({ 715, -790 }, { 1,0 }, 14, 30.f, PLATFORM); //floor
	wall.CreateWall({ 715, -465 }, { 1,0 }, 14, 30.f, CEILING); // top wall
	wall.CreateWall({ 685,-465 }, { 0,-1 }, 11, 30.f, WALL); // left wall
	wall.CreateWall({ 715 + 14 * 30,-465 }, { 0,-1 }, 11, 30.f, WALL); // right wall
	wall.CreateWall({ 715, -650+30 }, { 1,0 }, 6, 30.f, PLATFORM); //platform
	door.SetDoorPosition(3, { 805 , -585+30 });//door 3
	door.SetDoorPosition(4, { 1060 , -720 });//door 4
	sharpener.SetSharpenerPosition(0, { 830,-720 }); // sharpener

	//4th box
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

	door.SetDoorPosition(7, { 530 , -370 });//door 7
	sharpener.SetSharpenerPosition(1, { 780, 20 }); // sharpener
	
	//timer
	timer = 150.f;
}
void Level1_Update()
{
	/******************************************************************************/
	/*!
		TIMER
	*/
	/******************************************************************************/
	printf("timer: %f \n", timer);
	if (timer < 0)
	{
		gGameStateNext = GS_LOSE;
	}
	else
	{
		timer -= g_dt;
	}
	
}
void Level1_Draw()
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(bg.pBg->texture, 0, 0);
	AEGfxSetTransform(bg.transform.m);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(bg.pBg->pMesh, AE_GFX_MDM_TRIANGLES);
	AEGfxSetTransparency(0.0f);
	sprintf_s(strBuffer, "Timer: %d", (int)timer);
	AEGfxPrint(Fonts, strBuffer, -1.0f, 0.9f, 1.0f, 0.0f, 0.0f, 0.0f);
}
void Level1_Free()
{
	AEGfxMeshFree(bg.pBg->pMesh);

}
void Level1_Unload()
{
	timer = 100.f;
	AEGfxTextureUnload(bg.pBg->texture);
}