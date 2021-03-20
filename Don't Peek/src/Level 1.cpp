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
#include"Level 1.h"
#include "Door.h"
#include "Sharpener.h"
#include "Highlighter.h"

static background bg;
static Wall wall[100];
static Door door;
static Sharpener sharpener;
static Highlighter highlighter;
void Level1_Load()
{
	bg.Bgpos= {350.f,-200.f };
	bg.Bgscale = { 1760.f,1090.f };

	bg.pBg = sGameObjList + sGameObjNum++;
	bg.pBg->texture = AEGfxTextureLoad("Resources/Background.png");
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
	wall->CreateWall({ -410,-60 }, { 1,0 }, 26, 30.f, PLATFORM);
	wall->CreateWall({  100, 0 }, { 1,0 }, 5, 30.f, PLATFORM);
	wall->CreateWall({ -150,210 }, { 0,-1 }, 9, 30.f, WALL);
	wall->CreateWall({ -410,210 }, { 1,0 }, 26, 30.f, PLATFORM);
	wall->CreateWall({ 340,210 }, { 0,-1 }, 9, 30.f, WALL);

	//Sharpener
	SetSharpenerNum(1);
	sharpener.SetSharpenerPosition(0, { -100,0 });

	//Highlighter
	//SetHighlighterrNum(1);
	//highlighter.SetHighlighterPosition(0, { 100,0 });

	//Door
	SetDoorNum(2);
	door.SetDoorPosition(0, { 300 , 0 });
	door.SetDoorPosition(1, { -300 , 0 });
}
void Level1_Update()
{

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
}
void Level1_Free()
{

}
void Level1_Unload()
{

}