/* Start Header ************************************************************************/
/*!
\file Rules.cpp
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
#include "Rules.h"

Rule rule;

void RulesLoad()
{
	// just the background
	rule.pos = { 0.f, 0.f };
	rule.scale = { 950.f,650.f };

	rule.pObj = sGameObjList + sGameObjNum++;
	rule.pObj->texture = AEGfxTextureLoad("Resources/Rules.jpg");
	AE_ASSERT_MESG(rule.pObj->texture, "Failed to load Menu!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	rule.pObj->pMesh = AEGfxMeshEnd();
	AEMtx33	trans, sc;
	// Compute the scaling matrix
	AEMtx33Scale(&sc, rule.scale.x, rule.scale.y);
	// Compute the translation matrix
	AEMtx33Trans(&trans, rule.pos.x, rule.pos.y);

	AEMtx33Concat(&(rule.transform), &trans, &sc);
}
void RulesInit()
{

}
void RulesUpdate()
{
	AEGfxSetCamPosition(0, 0);

	//MAIN BUTTONS
	if (AEInputCheckCurr(AEVK_ESCAPE))
		gGameStateNext = GS_QUIT;

	if (AEInputCheckCurr(AEVK_B))
		gGameStateNext = GS_MENU;
}
void RulesDraw()
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(rule.pObj->texture, 0, 0);
	AEGfxSetTransform(rule.transform.m);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(rule.pObj->pMesh, AE_GFX_MDM_TRIANGLES);
}
void RulesFree()
{

}
void RulesUnload()
{
	if (rule.pObj->pMesh)
		AEGfxMeshFree(rule.pObj->pMesh);
	if (rule.pObj->texture)
		AEGfxTextureUnload(rule.pObj->texture);
}
