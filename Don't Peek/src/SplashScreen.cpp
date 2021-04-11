/* Start Header ************************************************************************/
/*!
\file SplashScreen.cpp
\team name Don't Peek
\software name I Don't Wanna Do My Homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief 
This file contains all the functions that is required for our Splash Screen.
It includes the short timer before changing states to main menu.


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#include "GameStateMgr.h"
#include "SplashScreen.h"

static SplashScreen splashscreen;
static float splashscreentimer = 0;

/******************************************************************************/
/*!
	Splash Screen Load
*/
/******************************************************************************/
void SSLoad()
{
	/*===============================================================================
		SPLASH SCREEN [DIGIPEN LOGO]
	=================================================================================*/
	splashscreen.pos = { 0, 0 };
	splashscreen.scale = { 1000.f,700.f };

	splashscreen.pObj = sGameObjList + sGameObjNum++;
	splashscreen.pObj->texture = AEGfxTextureLoad("Resources/DigiPen.jpg");
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

	/*===============================================================================
		SCALING/TRANSFORMATION/CONCAT FOR SPLASH SCREEN [DIGIPEN LOGO]
	=================================================================================*/
	AEMtx33	trans, sc;
	// Compute the scaling matrix
	AEMtx33Scale(&sc, splashscreen.scale.x, splashscreen.scale.y);
	// Compute the translation matrix
	AEMtx33Trans(&trans, splashscreen.pos.x, splashscreen.pos.y);

	AEMtx33Concat(&(splashscreen.transform), &trans, &sc);
}

/******************************************************************************/
/*!
	Splash Screen Initalization
*/
/******************************************************************************/
void SSInit()
{
	splashscreentimer = 3;
}

/******************************************************************************/
/*!
	Splash Screen Update
*/
/******************************************************************************/
void SSUpdate()
{
	//Timer count down before changing to main menu
	if (splashscreentimer > 0)
		splashscreentimer -= g_dt;
	else
		gGameStateNext = GS_MENU;
}

/******************************************************************************/
/*!
	Splash Screen Draw
*/
/******************************************************************************/
void SSDraw()
{
	/*===============================================================================
		DRAW SPLASH SCREEN SCREEN
	=================================================================================*/
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(splashscreen.pObj->texture, 0, 0);
	AEGfxSetTransform(splashscreen.transform.m);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(splashscreen.pObj->pMesh, AE_GFX_MDM_TRIANGLES);
}

/******************************************************************************/
/*!
	Splash Screen Free
*/
/******************************************************************************/
void SSFree()
{
}

/******************************************************************************/
/*!
	Splash Screen Unload
*/
/******************************************************************************/
void SSUnload()
{
	if (splashscreen.pObj->pMesh)
		AEGfxMeshFree(splashscreen.pObj->pMesh);

	if (splashscreen.pObj->texture)
		AEGfxTextureUnload(splashscreen.pObj->texture);
}