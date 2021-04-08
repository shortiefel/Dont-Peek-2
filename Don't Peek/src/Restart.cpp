/* Start Header ************************************************************************/
/*!
\file Restart.cpp
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
#include "Restart.h"


static Restart restart;
static float restarttimer;

void RestartLoad()
{
	restart.pos = { 0.f, 0.f };
	restart.scale = { 950.f,650.f };

	restart.pObj = sGameObjList + sGameObjNum++;
	restart.pObj->texture = AEGfxTextureLoad("Resources/BGempty.jpg");
	AE_ASSERT_MESG(restart.pObj->texture, "Failed to load Menu!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	restart.pObj->pMesh = AEGfxMeshEnd();
	AEMtx33	trans, sc;
	// Compute the scaling matrix
	AEMtx33Scale(&sc, restart.scale.x, restart.scale.y);
	// Compute the translation matrix
	AEMtx33Trans(&trans, restart.pos.x, restart.pos.y);

	AEMtx33Concat(&(restart.transform), &trans, &sc);
}

void RestartInit()
{

}

void RestartUpdate()
{
	if (restarttimer < 0)
	{
		if (gGameStatePrev == GS_TUTORIAL)
			gGameStateNext = GS_TUTORIAL;
		else if (gGameStatePrev == GS_DONT_PEEK)
			gGameStateNext = GS_DONT_PEEK;
	}
	else
		restarttimer -= g_dt;
}

void RestartDraw()
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(restart.pObj->texture, 0, 0);
	AEGfxSetTransform(restart.transform.m);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(restart.pObj->pMesh, AE_GFX_MDM_TRIANGLES);
}

void RestartFree()
{

}

void RestartUnload()
{
	if (restart.pObj->texture)
		AEGfxTextureUnload(restart.pObj->texture);
}