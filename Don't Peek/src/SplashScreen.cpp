/* Start Header ************************************************************************/
/*!
\file SplashScreen.cpp
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
#include "SplashScreen.h"

SplashScreen splashscreen;
static float splashscreentimer = 0;
void SSLoad()
{
	/******************************************************************************/
	/*!
		SPLASH SCREEN
	*/
	/******************************************************************************/
	splashscreen.pos = { 0, 0 };
	splashscreen.scale = { 600.f, 300.f };

	splashscreen.pObj = sGameObjList + sGameObjNum++;
	splashscreen.pObj->texture = AEGfxTextureLoad("Resources/DigiPen_BLACK.png");
	AE_ASSERT_MESG(splashscreen.pObj->texture, "Failed to load SplashScreen!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	splashscreen.pObj->pMesh = AEGfxMeshEnd();

	AEMtx33	trans, sc;
	// Compute the scaling matrix
	AEMtx33Scale(&sc, splashscreen.scale.x, splashscreen.scale.y);
	// Compute the translation matrix
	AEMtx33Trans(&trans, splashscreen.pos.x, splashscreen.pos.y);

	AEMtx33Concat(&(splashscreen.transform), &trans, &sc);
	printf("splashscreen LOAD\n");
}

void SSInit()
{
	splashscreentimer = 3;
	printf("splashscreen INIT\n");
}

void SSUpdate()
{
	if (splashscreentimer > 0)
		splashscreentimer -= g_dt;
	else
		gGameStateNext = GS_MENU;
}

void SSDraw()
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(splashscreen.pObj->texture, 0, 0);
	AEGfxSetTransform(splashscreen.transform.m);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(splashscreen.pObj->pMesh, AE_GFX_MDM_TRIANGLES);
}

void SSFree()
{
	

}

void SSUnload()
{
	if (splashscreen.pObj->pMesh)
		AEGfxMeshFree(splashscreen.pObj->pMesh);

	if (splashscreen.pObj->texture)
		AEGfxTextureUnload(splashscreen.pObj->texture);
	printf("splash screen DESTROY\n");

}