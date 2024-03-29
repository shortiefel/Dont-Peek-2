/* Start Header ************************************************************************/
/*!
\file Win.cpp
\team name Don't Peek
\software name I Don't Wanna Do My Homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief This file is done by felicia. 
In this file, it contains the win screen, and 2
different buttons which allows players to navigate.


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#include "GameStateMgr.h"
#include "Win.h"
#include "Menu.h"

//Initalization
static Win win;
static ButtonW Wbutton[2];
static int Win_x, Win_y;
static int SetWidthCursorWin = 1000 / 2;
static int SetHeightCursorWin = 700 / 2;

/******************************************************************************/
/*!
	Win Load
*/
/******************************************************************************/
void WinLoad()
{
	/*===============================================================================
		WIN SCREEN
	=================================================================================*/
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

	/*===============================================================================
		SCALING/TRANSFORMATION/CONCAT FOR WIN SCREEN
	=================================================================================*/
	AEMtx33	trans, sc;
	// Compute the scaling matrix
	AEMtx33Scale(&sc, win.scale.x, win.scale.y);
	// Compute the translation matrix
	AEMtx33Trans(&trans, win.pos.x, win.pos.y);

	AEMtx33Concat(&(win.transform), &trans, &sc);


	/*===============================================================================
		MAIN MENU BUTTON
	=================================================================================*/
	Wbutton[0].pos = { 200.f, -150.f };
	Wbutton[0].scale = { 200.f,80.f };
	Wbutton[0].pButton = sGameObjList + sGameObjNum++;
	Wbutton[0].pButton->texture = AEGfxTextureLoad("Resources/MBtn.jpg");
	Wbutton[0].pButton->type = TYPE_LEVEL;
	AE_ASSERT_MESG(Wbutton[0].pButton->texture, "Failed to load Button1!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	Wbutton[0].pButton->pMesh = AEGfxMeshEnd();

	/*===============================================================================
		NEXT LEVEL BUTTON
	=================================================================================*/
	Wbutton[1].pos = { 200.f, -230.f };
	Wbutton[1].scale = { 200.f,80.f };
	Wbutton[1].pButton = sGameObjList + sGameObjNum++;
	Wbutton[1].pButton->texture = AEGfxTextureLoad("Resources/NextLevel.jpg");
	Wbutton[1].pButton->type = TYPE_LEVEL;
	AE_ASSERT_MESG(Wbutton[1].pButton->texture, "Failed to load Button1!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	Wbutton[1].pButton->pMesh = AEGfxMeshEnd();
	
	/*===============================================================================
		SCALING/TRANSFORMATION/CONCAT FOR ALL BUTTON
	=================================================================================*/
	for (int i = 0; i < 2; i++)
	{
		AEMtx33Scale(&sc, Wbutton[i].scale.x, Wbutton[i].scale.y);
		// Compute the translation matrix
		AEMtx33Trans(&trans, Wbutton[i].pos.x, Wbutton[i].pos.y);

		AEMtx33Concat(&(Wbutton[i].transform), &trans, &sc);
	}
}

/******************************************************************************/
/*!
	Win Initalization
*/
/******************************************************************************/
void WinInit()
{
}

/******************************************************************************/
/*!
	Win Update
*/
/******************************************************************************/
void WinUpdate()
{
	AEGfxSetCamPosition(0, 0);	//Set camera back to 0,0
	BoundingBoxWin();
	AEInputGetCursorPosition(&Win_x, &Win_y);
	//IN ORDER TO USE BOUNDING BOX FOR BUTTON, HAVE TO CHANGE MOUSE POSITION VALUE TO BOUNDING BOX POSITION.
	//AEInputGetCursorPosition gets the value of 0,0 at the top left of the window.
	//This if function changes the 0,0 position to the center of the window.
	if (Win_x >= 0 && Win_y >= 0)
	{
		Win_x = Win_x - SetWidthCursorWin;
		Win_y -= SetHeightCursorWin;
		Win_y *= -1;
	}
	//CHECK FOR MOUSE LEFT CLICK
	if (AEInputCheckTriggered(AEVK_LBUTTON))
	{
		//printf("Mouse: %d::%d\n", Win_x, Win_y);	//USED TO CHECK FOR MOUSE POSITION

		if (CollisionIntersection_PointRect({ static_cast<float>(Win_x), static_cast<float>(Win_y) }, { 0,0 }, Wbutton[0].boundingBox, { 0,0 }))
		{
			if (AEInputUpdate)
			{
				gGameStateNext = GS_MENU;
				//printf("BBMin: %f::%f\n", Wbutton[0].boundingBox.min.x, Wbutton[0].boundingBox.min.y);	//Checks for MAIN MENU button bounding box.
				//printf("BBMax: %f::%f\n", Wbutton[0].boundingBox.max.x, Wbutton[0].boundingBox.max.y);
			}
		}
		else if (CollisionIntersection_PointRect({ static_cast<float>(Win_x), static_cast<float>(Win_y) }, { 0,0 }, Wbutton[1].boundingBox, { 0,0 }))
		{
			if (AEInputUpdate)
			{
				gGameStateNext = GS_DONT_PEEK;
				//printf("BUTTON NEXT LEVEL \n");
				//printf("BBMin: %f::%f\n", Wbutton[1].boundingBox.min.x, Wbutton[0].boundingBox.min.y);	//Checks for NEXT LEVEL button bounding box.
				//printf("BBMax: %f::%f\n", Wbutton[1].boundingBox.max.x, Wbutton[0].boundingBox.max.y);
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
	Win Draw
*/
/******************************************************************************/
void WinDraw()
{
	/*===============================================================================
		DRAW WIN SCREEN
	=================================================================================*/
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(win.pObj->texture, 0, 0);
	AEGfxSetTransform(win.transform.m);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(win.pObj->pMesh, AE_GFX_MDM_TRIANGLES);

	/*===============================================================================
		DRAW ALL BUTTONS
	=================================================================================*/
	for (int i = 0; i < 2; i++)
	{
		AEGfxTextureSet(Wbutton[i].pButton->texture, 0, 0);
		AEGfxSetTransform(Wbutton[i].transform.m);
		AEGfxSetTransparency(1.0f);
		AEGfxMeshDraw(Wbutton[i].pButton->pMesh, AE_GFX_MDM_TRIANGLES);
	}
}

/******************************************************************************/
/*!
	Win Free
*/
/******************************************************************************/
void WinFree()
{
}

/******************************************************************************/
/*!
	Win Unload
*/
/******************************************************************************/
void WinUnload()
{
	/*===============================================================================
		UNLOAD ALL BUTTONS
	=================================================================================*/
	for (int i = 0; i < 2; i++)
	{
		if (Wbutton[i].pButton->pMesh)
			AEGfxMeshFree(Wbutton[i].pButton->pMesh);
		if (Wbutton[i].pButton->texture)
			AEGfxTextureUnload(Wbutton[i].pButton->texture);
	}
	/*===============================================================================
		UNLOAD WIN SCREEN
	=================================================================================*/
	if (win.pObj->pMesh)
		AEGfxMeshFree(win.pObj->pMesh);
	if (win.pObj->texture)
		AEGfxTextureUnload(win.pObj->texture);
}

/******************************************************************************/
/*!
	Button Bounding Box
*/
/******************************************************************************/
void BoundingBoxWin()
{
	for (int i = 0; i < 2; i++)
	{
		Wbutton[i].boundingBox.min.x = Wbutton[i].pos.x - Wbutton[i].scale.x / 2;
		Wbutton[i].boundingBox.min.y = Wbutton[i].pos.y - Wbutton[i].scale.y / 2;
		Wbutton[i].boundingBox.max.x = Wbutton[i].pos.x + Wbutton[i].scale.x / 2;
		Wbutton[i].boundingBox.max.y = Wbutton[i].pos.y + Wbutton[i].scale.y / 2;
	}
}
