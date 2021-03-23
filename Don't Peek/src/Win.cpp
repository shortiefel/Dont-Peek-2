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

Win win;
Button Wbutton[2];
int Win_x, Win_y;
int SetWidthCursorWin = 1000 / 2;
int SetHeightCursorWin = 700 / 2;

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

	AEMtx33	trans, sc;
	// Compute the scaling matrix
	AEMtx33Scale(&sc, win.scale.x, win.scale.y);
	// Compute the translation matrix
	AEMtx33Trans(&trans, win.pos.x, win.pos.y);

	AEMtx33Concat(&(win.transform), &trans, &sc);

	//MISSING NEXT LEVEl BUTTON
}

void WinInit()
{
}

void WinUpdate()
{
	BoundingBox();
	AEInputGetCursorPosition(&Win_x, &Win_y);
	if (Win_x >= 0 && Win_y >= 0)
	{
		Win_x = Win_x - SetWidthCursorWin;
		Win_y -= SetHeightCursorWin;
		Win_y *= -1;
	}


	if (AEInputCheckCurr(AEVK_B))
		gGameStateNext = GS_MENU;

	if (AEInputCheckCurr(AEVK_ESCAPE))
		gGameStateNext = GS_QUIT;
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

	/*for (int i = 0; i < 2; i++)
	{
		AEGfxTextureSet(Wbutton[i].pButton->texture, 0, 0);
		AEGfxSetTransform(Wbutton[i].transform.m);
		AEGfxSetTransparency(1.0f);
		AEGfxMeshDraw(Wbutton[i].pButton->pMesh, AE_GFX_MDM_TRIANGLES);
	}*/
}

void WinFree()
{
	//free(Wbutton->pButton);
	free(win.pObj);
}

void WinUnload()
{
	
}

void BoundingBoxWin()
{
	/*for (int i = 0; i < 2; i++)
	{
		Wbutton[i].boundingBox.min.x = Wbutton[i].pos.x - Wbutton[i].scale.x / 2;
		Wbutton[i].boundingBox.min.y = Wbutton[i].pos.y - Wbutton[i].scale.y / 2;
		Wbutton[i].boundingBox.max.x = Wbutton[i].pos.x + Wbutton[i].scale.x / 2;
		Wbutton[i].boundingBox.max.y = Wbutton[i].pos.y + Wbutton[i].scale.y / 2;
	}*/
}
