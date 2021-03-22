/* Start Header ************************************************************************/
/*!
\file Menu.cpp
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

#include "main.h"
#include "GameStateMgr.h"
#include "Win.h"
#include "Menu.h"

static Win win;
Button Wbutton[2];
int Win_x, Win_y;
int SetWidthCursorWin = 1000 / 2;
int SetHeightCursorLose = 700 / 2;

void WinLoad()
{
	//For level Win
	win.pos = { 0.f, 0.f };
	win.scale = { 950.f, 650.f };

	win.pObj = sGameObjList + sGameObjNum++;
	win.pObj->texture = AEGfxTextureLoad("Resources/win.png");
	AE_ASSERT_MESG(win.pObj->texture, "Failed to load win screen!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	win.pObj->pMesh = AEGfxMeshEnd();

	//MISSING NEXT LEVEl BUTTON
}

void WinInit()
{
}

void WinUpdate()
{
}

void WinDraw()
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(win.pObj->texture, 0, 0);
	AEGfxSetTransform(win.transform.m);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(win.pObj->pMesh, AE_GFX_MDM_TRIANGLES);
}

void WinFree()
{
}

void WinUnload()
{
}

void BoundingBoxWin()
{
}
