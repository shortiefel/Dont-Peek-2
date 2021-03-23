/* Start Header ************************************************************************/
/*!
\file Pause.cpp
\team name Don't Peak
\software name I don't want to do homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu
\date 24/03/2021
\brief This is the player file. It contains all the player function
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#include "Win.h"
#include "Pause.h"
#include "Menu.h"

Pause pause;
ButtonP Pbtn[2];
int Px, Py;
int SetWidthCursorP = 1000 / 2;
int SetHeightCursorP = 700 / 2;

void PauseLoad()
{
	//bg for pause
	pause.pos = { 0.f, 0.f };
	pause.scale = { 950.f, 650.f };

	pause.pObj = sGameObjList + sGameObjNum++;
	pause.pObj->texture = AEGfxTextureLoad("Resources/pause.png");
	AE_ASSERT_MESG(pause.pObj->texture, "Failed to load win screen!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	pause.pObj->pMesh = AEGfxMeshEnd();

	AEMtx33	trans, sc;
	// Compute the scaling matrix
	AEMtx33Scale(&sc, pause.scale.x, pause.scale.y);
	// Compute the translation matrix
	AEMtx33Trans(&trans, pause.pos.x, pause.pos.y);

	AEMtx33Concat(&(pause.transform), &trans, &sc);

}

void PauseInit()
{
}

void PauseUpdate()
{
	AEGfxSetCamPosition(0, 0);
}

void PauseDraw()
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(pause.pObj->texture, 0, 0);
	AEGfxSetTransform(pause.transform.m);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(pause.pObj->pMesh, AE_GFX_MDM_TRIANGLES);
}

void PauseFree()
{
}

void PauseUnload()
{
}

void BoundingBoxPause()
{
}
