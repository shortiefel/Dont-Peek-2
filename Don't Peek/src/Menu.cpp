/* Start Header ************************************************************************/
/*!
\file Menu.cpp
\team name Don't Peek
\software name I Don't Wanna Do My Homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu
\date 22/01/2021
\brief
In this file, it contains the main menu screen, and 4 different buttons.
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#include "GameStateMgr.h"
#include "Menu.h"
#include "Music.h"

//Initalization
static Menu menu;
static Button button[4];
static int x, y;
static int SetWidthCursor = 1000 / 2;
static int SetHeightCursor = 700 / 2;

/******************************************************************************/
/*!
	Menu Load
*/
/******************************************************************************/
void MenuLoad()
{
	/*===============================================================================
		MENU SCREEN
	=================================================================================*/
	menu.pos = { 0.f, 0.f };
	menu.scale = { 950.f,650.f };

	//MENU BG
	menu.pObj = sGameObjList + sGameObjNum++;
	menu.pObj->texture = AEGfxTextureLoad("Resources/MenuNEW.png");
	AE_ASSERT_MESG(menu.pObj->texture, "Failed to load Menu!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	menu.pObj->pMesh = AEGfxMeshEnd();

	/*===============================================================================
		SCALING/TRANSFORMATION/CONCAT FOR MENU SCREEN
	=================================================================================*/
	AEMtx33	trans, sc;
	// Compute the scaling matrix
	AEMtx33Scale(&sc, menu.scale.x, menu.scale.y);
	// Compute the translation matrix
	AEMtx33Trans(&trans, menu.pos.x, menu.pos.y);

	AEMtx33Concat(&(menu.transform), &trans, &sc);


	/*===============================================================================
		PLAY BUTTON
	=================================================================================*/
	button[0].pos = { -150.f, -100.f };
	button[0].scale = { 200.f,80.f };
	button[0].pButton = sGameObjList + sGameObjNum++;
	button[0].pButton->texture = AEGfxTextureLoad("Resources/Play.jpg");
	button[0].pButton->type = TYPE_PLAY;
	AE_ASSERT_MESG(button[0].pButton->texture, "Failed to load Button0!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	button[0].pButton->pMesh = AEGfxMeshEnd();

	/*===============================================================================
		LEVEL SELECT BUTTON
	=================================================================================*/
	button[1].pos = { 150.f, -100.f };
	button[1].scale = { 200.f,80.f };
	button[1].pButton = sGameObjList + sGameObjNum++;
	button[1].pButton->texture = AEGfxTextureLoad("Resources/Level.jpg");
	button[1].pButton->type = TYPE_LEVEL;
	AE_ASSERT_MESG(button[1].pButton->texture, "Failed to load Button1!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	button[1].pButton->pMesh = AEGfxMeshEnd();

	/*===============================================================================
		OPTIONS BUTTON
	=================================================================================*/
	button[2].pos = { -150.f, -200.f };
	button[2].scale = { 200.f,80.f };
	button[2].pButton = sGameObjList + sGameObjNum++;
	button[2].pButton->texture = AEGfxTextureLoad("Resources/HowToPlay.jpg");
	button[2].pButton->type = TYPE_OPTIONS;
	AE_ASSERT_MESG(button[2].pButton->texture, "Failed to load Button2!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	button[2].pButton->pMesh = AEGfxMeshEnd();

	/*===============================================================================
		CREDITS BUTTON
	=================================================================================*/
	button[3].pos = { 150.f, -200.f };
	button[3].scale = { 200.f,80.f };
	button[3].pButton = sGameObjList + sGameObjNum++;
	button[3].pButton->texture = AEGfxTextureLoad("Resources/Credits.jpg");
	button[3].pButton->type = TYPE_CREDITS;
	AE_ASSERT_MESG(button[3].pButton->texture, "Failed to load Menu!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	button[3].pButton->pMesh = AEGfxMeshEnd();

	/*===============================================================================
		SCALING/TRANSFORMATION/CONCAT FOR ALL BUTTON
	=================================================================================*/
	for (int i = 0; i < 4; i++)
	{
		AEMtx33Scale(&sc, button[i].scale.x, button[i].scale.y);
		// Compute the translation matrix
		AEMtx33Trans(&trans, button[i].pos.x, button[i].pos.y);

		AEMtx33Concat(&(button[i].transform), &trans, &sc);
	}
}

/******************************************************************************/
/*!
	Menu Initalization
/******************************************************************************/
void MenuInit()
{
	SoundSystem_Init();
	SoundSystem_SFX();
}

/******************************************************************************/
/*!
	Menu Update
*/
/******************************************************************************/
void MenuUpdate()
{
	AEGfxSetCamPosition(0, 0);	//Set camera back to 0,0
	BoundingBox();
	//IN ORDER TO USE BOUNDING BOX FOR BUTTON, HAVE TO CHANGE MOUSE POSITION VALUE TO BOUNDING BOX POSITION.
	//AEInputGetCursorPosition gets the value of 0,0 at the top left of the window.
	//This if function changes the 0,0 position to the center of the window.
	AEInputGetCursorPosition(&x, &y);
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
			PLAY BUTTON
		=================================================================================*/
		if (CollisionIntersection_PointRect({ static_cast<float>(x), static_cast<float>(y) }, { 0,0 }, button[0].boundingBox, { 0,0 }))
		{
			if (AEInputUpdate)
			{
				//SoundSystem_Destroy();

				gGameStateNext = GS_TUTORIAL;
				//printf("BUTTON PLAY \n");
				//printf("BBMin: %f::%f\n", button[0].boundingBox.min.x, button[0].boundingBox.min.y);
				//printf("BBMax: %f::%f\n", button[0].boundingBox.max.x, button[0].boundingBox.max.y);
			}

		}
		/*===============================================================================
			LEVEL SELECT BUTTON
		=================================================================================*/
		else if (CollisionIntersection_PointRect({ static_cast<float>(x), static_cast<float>(y) }, { 0,0 }, button[1].boundingBox, { 0,0 }))
		{
			if (AEInputUpdate)
			{
				//printf("BUTTON LEVEL \n");
				gGameStateNext = GS_LEVEL;
			}

		}
		/*===============================================================================
			OPTIONS BUTTON
		=================================================================================*/
		else if (CollisionIntersection_PointRect({ static_cast<float>(x), static_cast<float>(y) }, { 0,0 }, button[2].boundingBox, { 0,0 }))
		{
			if (AEInputUpdate)
			{
				gGameStateNext = GS_RULE;
				//printf("BUTTON HOW TO PLAY \n");
			}

		}
		/*===============================================================================
			CREDITS BUTTON
		=================================================================================*/
		else if (CollisionIntersection_PointRect({ static_cast<float>(x), static_cast<float>(y) }, { 0,0 }, button[3].boundingBox, { 0,0 }))
		{
			if (AEInputUpdate)
			{
				gGameStateNext = GS_CREDITS;
				//printf("BUTTON CREDITS \n");
			}
		}
	}

	if (AEInputCheckCurr(AEVK_ESCAPE))	//Close the game
		gGameStateNext = GS_QUIT;

	if (AEInputCheckCurr(AEVK_B))		//Goes back to main menu
		gGameStateNext = GS_MENU;
}
void MenuDraw()
{
	/*===============================================================================
		DRAW MENU SCREEN
	=================================================================================*/
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(menu.pObj->texture, 0, 0);
	AEGfxSetTransform(menu.transform.m);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(menu.pObj->pMesh, AE_GFX_MDM_TRIANGLES);

	/*===============================================================================
		DRAW ALL BUTTONS
	=================================================================================*/
	for (int i = 0; i < 4; i++)
	{
		AEGfxTextureSet(button[i].pButton->texture, 0, 0);
		AEGfxSetTransform(button[i].transform.m);
		AEGfxSetTransparency(1.0f);
		AEGfxMeshDraw(button[i].pButton->pMesh, AE_GFX_MDM_TRIANGLES);
	}
}

/******************************************************************************/
/*!
	Menu Free
*/
/******************************************************************************/
void MenuFree()
{
	SoundSystem_Destroy();
}

/******************************************************************************/
/*!
	Menu Unload
*/
/******************************************************************************/
void MenuUnload()
{
	for (int i = 0; i < 4; i++)
	{
		if (button[i].pButton->pMesh)
			AEGfxMeshFree(button[i].pButton->pMesh);
		if (button[i].pButton->texture)
			AEGfxTextureUnload(button[i].pButton->texture);
	}

	if (menu.pObj->pMesh)
		AEGfxMeshFree(menu.pObj->pMesh);
	if (menu.pObj->texture)
		AEGfxTextureUnload(menu.pObj->texture);
}

/******************************************************************************/
/*!
	Button Bounding Box
*/
/******************************************************************************/
void BoundingBox()
{
	for (int i = 0; i < 4; i++)
	{
		button[i].boundingBox.min.x = button[i].pos.x - button[i].scale.x / 2;
		button[i].boundingBox.min.y = button[i].pos.y - button[i].scale.y / 2;
		button[i].boundingBox.max.x = button[i].pos.x + button[i].scale.x / 2;
		button[i].boundingBox.max.y = button[i].pos.y + button[i].scale.y / 2;
	}
}