/* Start Header ************************************************************************/
/*!
\file Level Select.cpp
\team name Don't Peek
\software name I Don't Wanna Do My Homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief
This file contains all the functions that is required for creating Level Select screen.
It enables the player to choose Tutorial or Level 1


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/
#include "main.h"
#include "GameStateMgr.h"
#include "Menu.h"
#include "Level Select.h"
#include "Music.h"

//Initalization
static Level_Select screen[2];
static Button button;
static int element = 0;
static int x, y;
static int SetWidthCursor = 1000 / 2;
static int SetHeightCursor = 700 / 2;
static int CurrentScreen;

static enum LevelScreen
{
	TUT,
	LV1
};

/******************************************************************************/
/*!
	Button Bounding Box
*/
/******************************************************************************/
static void BoundingBox1()
{
	button.boundingBox.min.x = button.pos.x - button.scale.x / 2;
	button.boundingBox.min.y = button.pos.y - button.scale.y / 2;
	button.boundingBox.max.x = button.pos.x + button.scale.x / 2;
	button.boundingBox.max.y = button.pos.y + button.scale.y / 2;
}
/******************************************************************************/
/*!
	Level Select Load
*/
/******************************************************************************/
void LevelSelectLoad()
{
	/*===============================================================================
		LEVEL 1 LEVEL SELECT SCREEN
	=================================================================================*/
	screen[0].pos = { 0.f, 0.f };
	screen[0].scale = { 950.f, 650.f };
	
	screen[0].pObj = sGameObjList + sGameObjNum++;
	screen[0].pObj->texture = AEGfxTextureLoad("Resources/LevelSelect.jpg");
	AE_ASSERT_MESG(screen[0].pObj->texture, "Failed to load credit screen!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	screen[0].pObj->pMesh = AEGfxMeshEnd();

	/*===============================================================================
		TUTORIAL LEVEL SELECT SCREEN
	=================================================================================*/
	screen[1].pos = { 0.f, 0.f };
	screen[1].scale = { 950.f, 650.f };

	screen[1].pObj = sGameObjList + sGameObjNum++;
	screen[1].pObj->texture = AEGfxTextureLoad("Resources/LevelSelect_tutorial.jpg");
	AE_ASSERT_MESG(screen[1].pObj->texture, "Failed to load credit screen!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	screen[1].pObj->pMesh = AEGfxMeshEnd();

	/*===============================================================================
		PLAY BUTTON
	=================================================================================*/
	button.pos = { 235.f, -20.f };
	button.scale = { 200.f,80.f };
	button.pButton = sGameObjList + sGameObjNum++;
	button.pButton->texture = AEGfxTextureLoad("Resources/Play.jpg");
	button.pButton->type = TYPE_NEXT;
	AE_ASSERT_MESG(button.pButton->texture, "Failed to load Next!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	button.pButton->pMesh = AEGfxMeshEnd();

	/*===============================================================================
		SCALING/TRANSFORMATION/CONCAT FOR ALL LEVEL SELECT SCREEN
	=================================================================================*/
	AEMtx33	trans, sc;
	
	for (int i = 0; i < 2; i++)
	{
		AEMtx33Scale(&sc, screen[i].scale.x, screen[i].scale.y);
		AEMtx33Trans(&trans, screen[i].pos.x, screen[i].pos.y);
		AEMtx33Concat(&(screen[i].transform), &trans, &sc);
	}

	/*===============================================================================
		SCALING/TRANSFORMATION/CONCAT FOR PLAY BUTTON
	=================================================================================*/
	AEMtx33Scale(&sc, button.scale.x, button.scale.y);
	AEMtx33Trans(&trans, button.pos.x, button.pos.y);
	AEMtx33Concat(&(button.transform), &trans, &sc);
}

/******************************************************************************/
/*!
	Level Select Initalization
*/
/******************************************************************************/
void LevelSelectInit()
{
	CurrentScreen = TUT;
	SoundSystem_Init();
	SoundSystem_SFX();
}

/******************************************************************************/
/*!
	Level Select Update
*/
/******************************************************************************/
void LevelSelectUpdate()
{
	BoundingBox1();
	AEInputGetCursorPosition(&x, &y);
	//IN ORDER TO USE BOUNDING BOX FOR BUTTON, HAVE TO CHANGE MOUSE POSITION VALUE TO BOUNDING BOX POSITION.
	//AEInputGetCursorPosition gets the value of 0,0 at the top left of the window.
	//This if function changes the 0,0 position to the center of the window.
	if (x >= 0 && y >= 0)
	{
		x = x - SetWidthCursor;
		y -= SetHeightCursor;
		y *= -1;
	}
	//CHECK FOR MOUSE LEFT CLICK
	if (AEInputCheckTriggered(AEVK_LBUTTON))
	{
		//printf("Mouse: %d::%d\n", x, y);	//USED TO CHECK FOR MOUSE POSITION

		/*===============================================================================
			PLAY BUTTON [LEVEL 1]
		=================================================================================*/
		if (CollisionIntersection_PointRect({ static_cast<float>(x), static_cast<float>(y) }, 
			{ 0,0 }, button.boundingBox, { 0,0 }) && CurrentScreen == LV1)
		{
			if (AEInputUpdate)
			{
				gGameStateNext = GS_DONT_PEEK;
				//printf("BUTTON PLAY \n");
				//printf("BBMin: %f::%f\n", button.boundingBox.min.x, button.boundingBox.min.y);
				//printf("BBMax: %f::%f\n", button.boundingBox.max.x, button.boundingBox.max.y);
			}

		}
		/*===============================================================================
			PLAY BUTTON [TUTORIAL]
		=================================================================================*/
		if (CollisionIntersection_PointRect({ static_cast<float>(x), static_cast<float>(y) },
			{ 0,0 }, button.boundingBox, { 0,0 }) && CurrentScreen == TUT)
		{
			if (AEInputUpdate)
			{
				gGameStateNext = GS_TUTORIAL;
				//printf("BUTTON PLAY \n");
				//printf("BBMin: %f::%f\n", button.boundingBox.min.x, button.boundingBox.min.y);
				//printf("BBMax: %f::%f\n", button.boundingBox.max.x, button.boundingBox.max.y);
			}

		}
	}
	if (x > -430 && x < -90 && y < -30 && y > -95 && AEInputCheckTriggered(AEVK_LBUTTON))
	{
		CurrentScreen = TUT;
	}
	if (x > -430 && x < -90 && y < -120 && y > -195 && AEInputCheckTriggered(AEVK_LBUTTON))
	{
		CurrentScreen = LV1;
	}

	if (AEInputCheckCurr(AEVK_ESCAPE))	//Close the game
		gGameStateNext = GS_QUIT;

	if (AEInputCheckCurr(AEVK_B))		//Goes back to main menu
		gGameStateNext = GS_MENU;
}

/******************************************************************************/
/*!
	Level Select Draw
*/
/******************************************************************************/
void LevelSelectDraw()
{
	/*===============================================================================
		DRAW TUTORIAL LEVEL SELECT SCREEN
	=================================================================================*/
	if (CurrentScreen == TUT)
	{
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(0, 0);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxTextureSet(screen[1].pObj->texture, 0, 0);
		AEGfxSetTransform(screen[1].transform.m);
		AEGfxSetTransparency(1.0f);
		AEGfxMeshDraw(screen[1].pObj->pMesh, AE_GFX_MDM_TRIANGLES);
	}
	/*===============================================================================
		DRAW LEVEL 1 LEVEL SELECT SCREEN
	=================================================================================*/
	else if (CurrentScreen == LV1)
	{
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(0, 0);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxTextureSet(screen[0].pObj->texture, 0, 0);
		AEGfxSetTransform(screen[0].transform.m);
		AEGfxSetTransparency(1.0f);
		AEGfxMeshDraw(screen[0].pObj->pMesh, AE_GFX_MDM_TRIANGLES);
	}

	/*===============================================================================
		DRAW PLAY BUTTONS
	=================================================================================*/
	AEGfxTextureSet(button.pButton->texture, 0, 0);
	AEGfxSetTransform(button.transform.m);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(button.pButton->pMesh, AE_GFX_MDM_TRIANGLES);
}

/******************************************************************************/
/*!
	Level Select Free
*/
/******************************************************************************/
void LevelSelectFree()
{
	CurrentScreen = TUT;
	CurrentScreen == LV1;
	SoundSystem_Destroy();
	
}

/******************************************************************************/
/*!
	Level Select Unload
*/
/******************************************************************************/
void LevelSelectUnload()
{
	/*===============================================================================
		UNLOAD PLAY BUTTONS
	=================================================================================*/
	if (button.pButton->pMesh)
		AEGfxMeshFree(button.pButton->pMesh);
	if (button.pButton->texture)
		AEGfxTextureUnload(button.pButton->texture);

	/*===============================================================================
		UNLOAD ALL LEVEL SELECT SCREEN
	=================================================================================*/
	for (int i = 0; i < 2; i++)
	{
		if (screen[i].pObj->pMesh)
			AEGfxMeshFree(screen[i].pObj->pMesh);
		if (screen[i].pObj->texture)
			AEGfxTextureUnload(screen[i].pObj->texture);
	}
}
