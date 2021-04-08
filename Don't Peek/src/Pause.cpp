/* Start Header ************************************************************************/
/*!
\file Pause.cpp
\team name Don't Peek
\software name I Don't Wanna Do My Homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu
\date 24/03/2021
\brief
This file contains all the functions that is required for our pause screen.
It contains 3 buttons [Resume, Restart & Main Menu]
Resume - to continue where u left off.
Restart - the restart the current level.
Main Menu - Send you back to Main Menu Page.
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#include "GameStateMgr.h"
#include "Win.h"
#include "Pause.h"
#include "Menu.h"
#include "Player.h"

//Initalization
static Pause pause;
static ButtonP Pbtn[3];
static int Px, Py;
static int SetWidthCursorP = 1000 / 2;
static int SetHeightCursorP = 700 / 2;

/******************************************************************************/
/*!
	Pause Load
*/
/******************************************************************************/
void PauseLoad()
{
	/*===============================================================================
		PAUSE SCREEN
	=================================================================================*/
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

	/*===============================================================================
		SCALING/TRANSFORMATION/CONCAT FOR PAUSE SCREEN
	=================================================================================*/
	AEMtx33	trans, sc;
	// Compute the scaling matrix
	AEMtx33Scale(&sc, pause.scale.x, pause.scale.y);
	// Compute the translation matrix
	AEMtx33Trans(&trans, pause.pos.x, pause.pos.y);

	AEMtx33Concat(&(pause.transform), &trans, &sc);


	/*===============================================================================
		RESUME BUTTON
	=================================================================================*/
	Pbtn[0].pos = { -175.f, 0.f };
	Pbtn[0].scale = { 200.f,80.f };
	Pbtn[0].pButton = sGameObjList + sGameObjNum++;
	Pbtn[0].pButton->texture = AEGfxTextureLoad("Resources/Resume.jpg");
	Pbtn[0].pButton->type = TYPE_LEVEL;
	AE_ASSERT_MESG(Pbtn[0].pButton->texture, "Failed to load Resume!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	Pbtn[0].pButton->pMesh = AEGfxMeshEnd();

	/*===============================================================================
		RESTART BUTTON
	=================================================================================*/
	Pbtn[1].pos = { -175.f, -100.f };
	Pbtn[1].scale = { 200.f,80.f };
	Pbtn[1].pButton = sGameObjList + sGameObjNum++;
	Pbtn[1].pButton->texture = AEGfxTextureLoad("Resources/Restart.jpg");
	Pbtn[1].pButton->type = TYPE_LEVEL;
	AE_ASSERT_MESG(Pbtn[1].pButton->texture, "Failed to load Restart!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	Pbtn[1].pButton->pMesh = AEGfxMeshEnd();


	/*===============================================================================
		MAIN MENU BUTTON
	=================================================================================*/
	Pbtn[2].pos = { -175.f, -200.f };
	Pbtn[2].scale = { 200.f,80.f };
	Pbtn[2].pButton = sGameObjList + sGameObjNum++;
	Pbtn[2].pButton->texture = AEGfxTextureLoad("Resources/MBtn.jpg");
	Pbtn[2].pButton->type = TYPE_LEVEL;
	AE_ASSERT_MESG(Pbtn[2].pButton->texture, "Failed to load Restart!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	Pbtn[2].pButton->pMesh = AEGfxMeshEnd();

	/*===============================================================================
		SCALING/TRANSFORMATION/CONCAT FOR ALL BUTTON
	=================================================================================*/
	for (int i = 0; i < 3; i++)
	{
		AEMtx33Scale(&sc, Pbtn[i].scale.x, Pbtn[i].scale.y);
		// Compute the translation matrix
		AEMtx33Trans(&trans, Pbtn[i].pos.x, Pbtn[i].pos.y);

		AEMtx33Concat(&(Pbtn[i].transform), &trans, &sc);
	}
}

/******************************************************************************/
/*!
	Pause Initalization
*/
/******************************************************************************/
void PauseInit()
{
}

/******************************************************************************/
/*!
	Pause Update
*/
/******************************************************************************/
void PauseUpdate()
{

	AEGfxSetCamPosition(0, 0);	//Set camera back to 0,0
	BoundingBoxPause();
	AEInputGetCursorPosition(&Px, &Py);
	//IN ORDER TO USE BOUNDING BOX FOR BUTTON, HAVE TO CHANGE MOUSE POSITION VALUE TO BOUNDING BOX POSITION.
	//AEInputGetCursorPosition gets the value of 0,0 at the top left of the window.
	//This if function changes the 0,0 position to the center of the window.
	if (Px >= 0 && Py >= 0)
	{
		Px = Px - SetWidthCursorP;
		Py -= SetHeightCursorP;
		Py *= -1;
	}
	//CHECK FOR MOUSE LEFT CLICK
	if (AEInputCheckTriggered(AEVK_LBUTTON))
	{
		//printf("Mouse: %d::%d\n", Px, Py);	//USED TO CHECK FOR MOUSE POSITION

		/*===============================================================================
			RESUME BUTTON
		=================================================================================*/
		if (CollisionIntersection_PointRect({ static_cast<float>(Px), static_cast<float>(Py) }, { 0,0 }, Pbtn[0].boundingBox, { 0,0 }))
		{
			if (gGameStateCurr == GS_TUTORIAL) //If statement can be removed if required.
			{
				if (AEInputUpdate)
				{
					CheckPause = false;
					AEGfxSetCamPosition(player.GetPosPlayer().x, player.GetPosPlayer().y); //Return camera position to player position.	
					//printf("Go tutorial");
				}

			}
			else if (gGameStateCurr == GS_DONT_PEEK)	//If statement can be removed if required.
			{
				if (AEInputUpdate)
				{
					CheckPause = false;
					AEGfxSetCamPosition(player.GetPosPlayer().x, player.GetPosPlayer().y); //Return camera position to player position.	
					//printf("Go level");
				}
			}
		}
		/*===============================================================================
			RESTART BUTTON
		=================================================================================*/
		else if (CollisionIntersection_PointRect({ static_cast<float>(Px), static_cast<float>(Py) }, { 0,0 }, Pbtn[1].boundingBox, { 0,0 }))
		{
			if (AEInputUpdate)
			{
				CheckPause = false;
				gGameStateNext = GS_RESTART;
				printf("Restarting \n");
			}
		}
		/*===============================================================================
			MAIN MENU BUTTON
		=================================================================================*/
		else if (CollisionIntersection_PointRect({ static_cast<float>(Px), static_cast<float>(Py) }, { 0,0 }, Pbtn[2].boundingBox, { 0,0 }))
		{
			if (AEInputUpdate)
			{
				gGameStateNext = GS_MENU;
				printf("BUTTON MAIN MENU \n");
				printf("BBMin: %f::%f\n", Pbtn[2].boundingBox.min.x, Pbtn[2].boundingBox.min.y);
				printf("BBMax: %f::%f\n", Pbtn[2].boundingBox.max.x, Pbtn[2].boundingBox.max.y);
			}
		}
	}

	if (AEInputCheckCurr(AEVK_ESCAPE))	//Close the game
		gGameStateNext = GS_QUIT;

	if (AEInputCheckCurr(AEVK_B))		//Goes back to main menu
		gGameStateNext = GS_MENU;
}

/******************************************************************************/
/*!
	Pause Draw
*/
/******************************************************************************/
void PauseDraw()
{
	/*===============================================================================
		DRAW PAUSE SCREEN
	=================================================================================*/
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(pause.pObj->texture, 0, 0);
	AEGfxSetTransform(pause.transform.m);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(pause.pObj->pMesh, AE_GFX_MDM_TRIANGLES);

	/*===============================================================================
		DRAW ALL BUTTONS
	=================================================================================*/
	for (int i = 0; i < 3; i++)
	{
		AEGfxTextureSet(Pbtn[i].pButton->texture, 0, 0);
		AEGfxSetTransform(Pbtn[i].transform.m);
		AEGfxSetTransparency(1.0f);
		AEGfxMeshDraw(Pbtn[i].pButton->pMesh, AE_GFX_MDM_TRIANGLES);
	}
}

/******************************************************************************/
/*!
	Pause Free
*/
/******************************************************************************/
void PauseFree()
{

}

/******************************************************************************/
/*!
	Pause Unload
*/
/******************************************************************************/
void PauseUnload()
{
	for (int i = 0; i < 3; i++)
	{
		if (Pbtn[i].pButton->pMesh)
			AEGfxMeshFree(Pbtn[i].pButton->pMesh);
		if (Pbtn[i].pButton->texture)
			AEGfxTextureUnload(Pbtn[i].pButton->texture);
	}
	if (pause.pObj->pMesh)
		AEGfxMeshFree(pause.pObj->pMesh);
	if (pause.pObj->texture)
		AEGfxTextureUnload(pause.pObj->texture);

}

/******************************************************************************/
/*!
	Button Bounding Box
*/
/******************************************************************************/
void BoundingBoxPause()
{
	for (int i = 0; i < 3; i++)
	{
		Pbtn[i].boundingBox.min.x = Pbtn[i].pos.x - Pbtn[i].scale.x / 2;
		Pbtn[i].boundingBox.min.y = Pbtn[i].pos.y - Pbtn[i].scale.y / 2;
		Pbtn[i].boundingBox.max.x = Pbtn[i].pos.x + Pbtn[i].scale.x / 2;
		Pbtn[i].boundingBox.max.y = Pbtn[i].pos.y + Pbtn[i].scale.y / 2;
	}
}