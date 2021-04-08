/* Start Header ************************************************************************/
/*!
\file Tutorial.cpp
\team name Don't Peek
\software name I Don't Wanna Do My Homework
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
#include "GameStateMgr.h"
#include "Tutorial.h"
#include "Door.h"
#include "Sharpener.h"
#include "Pencil.h"
#include "Eraser.h"
#include "Highlighter.h"
#include "Wall.h"
#include "Music.h"
#include "Player.h"

static background bg;
//static float timer = 0;

/******************************************************************************/
/*!
	Tutorial Load
	/brief loads background for level
*/
/******************************************************************************/
void Tutorial_Load()
{
	/******************************************************************************/
	/*!
		BACKGROUND
	*/
	/******************************************************************************/
	bg.Bgpos= {350.f,-200.f };
	bg.Bgscale = { 1.2 * 1760.f, 1.2* 1090.f };

	bg.pBg = sGameObjList + sGameObjNum++;
	bg.pBg->texture = AEGfxTextureLoad("Resources/Level 1.jpg");
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

/******************************************************************************/
/*!
	Tutorial Init
	/brief inits all objects for level
*/
/******************************************************************************/
void Tutorial_Init()
{
	SetWin({ 1045, 260 });
	//timer = 50.f;
	SetDoorNum(8);
	//Highlighter
	SetHighlighterNum(2);
	//Sharperner
	SetSharpenerNum(2);
	//eraser
	SetEraserNum(1);
	//pencil
	SetPencilNum(2);
	/******************************************************************************/
	/*!
		FIRST BOX
	*/
	/******************************************************************************/

	wall.CreateWall({ -390,-90 }, { 1,0 }, 20, 30.f, PLATFORM); //floor
	wall.CreateWall({ -390,320 }, { 1,0 }, 20, 30.f, CEILING); // top wall

	wall.CreateWall({ -405,320 }, { 0,-1 }, 15, 30.f, WALL); //left wall
	wall.CreateWall({ 200,320 }, { 0,-1 }, 15, 30.f, WALL); // right wall

	wall.CreateWall({ 50,80 }, { 1,0 }, 5, 30.f, CEILING); //platform
	wall.CreateWall({ 20,60 }, { 0,-1 }, 6, 30.f, WALL); //inside wall

	sharpener.SetSharpenerPosition(0, { -250,-20 });

	door.SetDoorPosition(0, { 120 , 150 });

	/******************************************************************************/
	/*!
		SECOND BOX
	*/
	/******************************************************************************/
	door.SetDoorPosition(1, { -40 , -315 });
	door.SetDoorPosition(2, { 150 , -650 });
	wall.CreateWall({ -105,-720 }, { 1,0 }, 11, 30.f, PLATFORM); //floor
	wall.CreateWall({ -105,-210 }, { 1,0 }, 11, 30.f, CEILING); // top wall
	wall.CreateWall({ -135,-210 }, { 0,-1 }, 18, 30.f, WALL); // left wall
	wall.CreateWall({ 210,-210 }, { 0,-1 }, 18, 30.f, WALL); // right wall
	wall.CreateWall({ -125,-385 }, { 1,0 }, 6, 30.f, CEILING); //platform

	sharpener.SetSharpenerPosition(1, { 10,-610 });

	/******************************************************************************/
	/*!
		THIRD BOX
	*/
	/******************************************************************************/
	door.SetDoorPosition(3, { 560 , -750 });
	door.SetDoorPosition(4, { 1130 , -535-40 });
	wall.CreateWall({ 520,-820 }, { 1,0 }, 24, 30.f, PLATFORM); //floor
	wall.CreateWall({ 520,-368 }, { 1,0 }, 24, 30.f, CEILING); // top wall
	wall.CreateWall({ 490,-368 }, { 0,-1 }, 16, 30.f, WALL); // left wall
	wall.CreateWall({ 1210,-368 }, { 0,-1 }, 16, 30.f, WALL); // right wall
	wall.CreateWall({ 1060,-640 }, { 1,0 }, 6, 30.f, PLATFORM); //platform right


	highlighter.SetHighlighterPosition(0, { 850, -770 });
	highlighter.SetHighlighterPosition(1, { 950, -770 });

	/******************************************************************************/
	/*!
		FOURTH BOX
	*/
	/******************************************************************************/
	door.SetDoorPosition(5, { 570 , 180 });
	door.SetDoorPosition(6, { 800 , -135 });
	wall.CreateWall({ 540,-205 }, { 1,0 }, 11, 30.f, PLATFORM); //floor
	wall.CreateWall({ 540, 115 }, { 1,0 }, 5, 30.f, PLATFORM); //below door
	wall.CreateWall({ 540,310 }, { 1,0 }, 11, 30.f, CEILING); //top wall
	wall.CreateWall({ 510,310 }, { 0,-1 }, 18, 30.f, WALL); //left wall
	wall.CreateWall({ 870,310 }, { 0,-1 }, 18, 30.f, WALL); //right wall
	wall.CreateWall({ 730,-40 }, { 1,0 }, 15, 10.f, PLATFORM); //Pencil Line

	eraser.SetEraserPosition(0, {650, -80 });
	//pencil not showing
	pencil.SetPencil(0, { 730, -130 }, 20, 130);
	pencil.SetPencil(1, { 780, -50 }, 120, 20);

	/******************************************************************************/
	/*!
		FIFTH BOX
	*/
	/******************************************************************************/
	door.SetDoorPosition(7, { 990 , 110 });
	wall.CreateWall({ 950,35 }, { 1,0 }, 8, 30.f, PLATFORM); //floor
	wall.CreateWall({ 950,280 }, { 1,0 }, 3, 30.f, CEILING); //ceiling
	wall.CreateWall({ 920,280 }, { 0,-1 }, 9, 30.f, WALL); //left wall
	wall.CreateWall({ 1190,280 }, { 0,-1 }, 9, 30.f, WALL); //left wall

	//timer
	//timer = 50.f;
}

/******************************************************************************/
/*!
	Tutorial Update
	/brief updates timer
*/
/******************************************************************************/
void Tutorial_Update()
{
}

/******************************************************************************/
/*!
	Tutorial Draw
	\brief draws background
*/
/******************************************************************************/
void Tutorial_Draw()
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
}

/******************************************************************************/
/*!
	Tutorial Free
	\brief free background
*/
/******************************************************************************/
void Tutorial_Free()
{
}

/******************************************************************************/
/*!
	Tutorial Unload
	\brief unload background
*/
/******************************************************************************/
void Tutorial_Unload()
{
	if (bg.pBg->pMesh)
		AEGfxMeshFree(bg.pBg->pMesh);
	if (bg.pBg->texture)
		AEGfxTextureUnload(bg.pBg->texture);
}