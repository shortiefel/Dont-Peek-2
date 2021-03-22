/* Start Header ************************************************************************/
/*!
\file Level 1.h
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
#include "Tutorial.h"
#include "Door.h"
#include "Sharpener.h"
#include "Pencil.h"
#include "Eraser.h"
#include "Highlighter.h"

static background bg;
static Wall wall[100];
static Door door;
static Sharpener sharpener;
static Eraser eraser;
static Pencil pencil;
static Highlighter highlighter;

void Tutorial_Load()
{
	bg.Bgpos= {350.f,-200.f };
	bg.Bgscale = { 1.2 * 1760.f, 1.2* 1090.f };

	bg.pBg = sGameObjList + sGameObjNum++;
	bg.pBg->texture = AEGfxTextureLoad("Resources/level_1_layout.jpeg");
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
void Tutorial_Init()
{
	SetSharpenerNum(1);
	SetDoorNum(8);
	//Highlighter
	//SetHighlighterrNum(1);
	//highlighter.SetHighlighterPosition(0, { 100,0 });

	//first box
	wall->CreateWall({ -390,-90 }, { 1,0 }, 20, 30.f, PLATFORM); //floor
	wall->CreateWall({ -390,320 }, { 1,0 }, 20, 30.f, WALL); // top wall

	wall->CreateWall({ -405,320 }, { 0,-1 }, 15, 30.f, WALL); //left wall
	wall->CreateWall({ 200,320 }, { 0,-1 }, 15, 30.f, WALL); // right wall

	wall->CreateWall({ 20,105 }, { 1,0 }, 6, 30.f, PLATFORM); //platform
	wall->CreateWall({ 20,75 }, { 0,-1 }, 6, 30.f, WALL); //inside wall

	SetSharpenerNum(1);
	sharpener.SetSharpenerPosition(0, { -250,-20 });


	door.SetDoorPosition(0, { 120 , 170 });

	//2nd box
	door.SetDoorPosition(1, { -40 , -320 });
	door.SetDoorPosition(2, { 150 , -655 });
	wall->CreateWall({ -105,-720 }, { 1,0 }, 11, 30.f, PLATFORM); //floor
	wall->CreateWall({ -105,-210 }, { 1,0 }, 11, 30.f, WALL); // top wall
	wall->CreateWall({ -135,-210 }, { 0,-1 }, 18, 30.f, WALL); // left wall
	wall->CreateWall({ 210,-210 }, { 0,-1 }, 18, 30.f, WALL); // right wall
	wall->CreateWall({ -125,-385 }, { 1,0 }, 6, 30.f, PLATFORM); //platform

	//3rd box
	door.SetDoorPosition(3, { 560 , -440 });
	door.SetDoorPosition(4, { 1130 , -535 });
	wall->CreateWall({ 520,-820 }, { 1,0 }, 24, 30.f, PLATFORM); //floor
	wall->CreateWall({ 520,-368 }, { 1,0 }, 24, 30.f, WALL); // top wall
	wall->CreateWall({ 490,-368 }, { 0,-1 }, 16, 30.f, WALL); // left wall
	wall->CreateWall({ 1210,-368 }, { 0,-1 }, 16, 30.f, WALL); // right wall
	wall->CreateWall({ 520,-505 }, { 1,0 }, 6, 30.f, PLATFORM); //platform left
	wall->CreateWall({ 1060,-600 }, { 1,0 }, 5, 30.f, PLATFORM); //platform right
	wall->CreateWall({ 670,-530 }, { 0,-1 }, 10, 30.f, WALL); //wall mid

	//4th box
	door.SetDoorPosition(5, { 580 , -140 });
	door.SetDoorPosition(6, { 800 , 100 });
	wall->CreateWall({ 540,-205 }, { 1,0 }, 11, 30.f, PLATFORM); //floor
	wall->CreateWall({ 540,310 }, { 1,0 }, 11, 30.f, WALL); //top wall
	wall->CreateWall({ 510,310 }, { 0,-1 }, 18, 30.f, WALL); //left wall
	wall->CreateWall({ 870,310 }, { 0,-1 }, 18, 30.f, WALL); //right wall

	//5th box
	door.SetDoorPosition(7, { 990 , 100 });
	wall->CreateWall({ 950,35 }, { 1,0 }, 8, 30.f, PLATFORM); //floor
	wall->CreateWall({ 950,280 }, { 1,0 }, 3, 30.f, WALL); //ceiling
	wall->CreateWall({ 920,280 }, { 0,-1 }, 9, 30.f, WALL); //left wall
	wall->CreateWall({ 1190,280 }, { 0,-1 }, 9, 30.f, WALL); //left wall
}
void Tutorial_Update()
{

}
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
}
void Tutorial_Free()
{
	
}
void Tutorial_Unload()
{

}