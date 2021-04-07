/* Start Header ************************************************************************/
/*!
\file Lose.cpp
\team name Don't Peak
\software name I don't want to do homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief 
In this file, it contains the lose screen, and 2
different buttons which allows players to navigate.


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#include "GameStateMgr.h"
#include "Win.h"
#include "Lose.h"
#include "Menu.h"

//Initalization
static Win lose; //Used Win.h struct for screen
static ButtonW Wbutton[2];	//Used Win.h struct for buttons
static int lose_x, lose_y;
static int SetWidthCursorWin = 1000 / 2;
static int SetHeightCursorWin = 700 / 2;

/******************************************************************************/
/*!
	Lose Load
*/
/******************************************************************************/
void LoseLoad()
{
	/*===============================================================================
		LOSE SCREEN
	=================================================================================*/
	lose.pos = { 0.f, 0.f };
	lose.scale = { 950.f, 650.f };

	lose.pObj = sGameObjList + sGameObjNum++;
	lose.pObj->texture = AEGfxTextureLoad("Resources/lose.png");
	AE_ASSERT_MESG(lose.pObj->texture, "Failed to load win screen!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	lose.pObj->pMesh = AEGfxMeshEnd();

	/*===============================================================================
		SCALING/TRANSFORMATION/CONCAT FOR LOSE SCREEN
	=================================================================================*/
	AEMtx33	trans, sc;
	// Compute the scaling matrix
	AEMtx33Scale(&sc, lose.scale.x, lose.scale.y);
	// Compute the translation matrix
	AEMtx33Trans(&trans, lose.pos.x, lose.pos.y);

	AEMtx33Concat(&(lose.transform), &trans, &sc);


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
	Lose Initalization
*/
/******************************************************************************/
void LoseInit()
{
}

/******************************************************************************/
/*!
	Lose Update
*/
/******************************************************************************/
void LoseUpdate()
{
	AEGfxSetCamPosition(0, 0); //Set camera back to 0,0
	BoundingBoxLose();
	AEInputGetCursorPosition(&lose_x, &lose_y);
	//IN ORDER TO USE BOUNDING BOX FOR BUTTON, HAVE TO CHANGE MOUSE POSITION VALUE TO BOUNDING BOX POSITION.
	//AEInputGetCursorPosition gets the value of 0,0 at the top left of the window.
	//This if function changes the 0,0 position to the center of the window.
	if (lose_x >= 0 && lose_y >= 0)
	{
		lose_x = lose_x - SetWidthCursorWin;
		lose_y -= SetHeightCursorWin;
		lose_y *= -1;
	}
	//CHECK FOR MOUSE LEFT CLICK
	if (AEInputCheckTriggered(AEVK_LBUTTON))
	{
		//printf("Mouse: %d::%d\n", lose_x, lose_y);	//USED TO CHECK FOR MOUSE POSITION

		if (CollisionIntersection_PointRect({ static_cast<float>(lose_x), static_cast<float>(lose_y) }, { 0,0 }, Wbutton[0].boundingBox, { 0,0 }))
		{
			if (AEInputUpdate)
			{
				gGameStateNext = GS_MENU;
				//printf("BBMin: %f::%f\n", Wbutton[0].boundingBox.min.x, Wbutton[0].boundingBox.min.y); //Checks for MAIN MENU button bounding box.
				//printf("BBMax: %f::%f\n", Wbutton[0].boundingBox.max.x, Wbutton[0].boundingBox.max.y);
			}
		}
		else if (CollisionIntersection_PointRect({ static_cast<float>(lose_x), static_cast<float>(lose_y) }, { 0,0 }, Wbutton[0].boundingBox, { 0,0 }))
		{
			if (AEInputUpdate)
			{
				gGameStateNext = GS_DONT_PEEK;
				//printf("BUTTON NEXT LEVEL \n");
				//printf("BBMin: %f::%f\n", Wbutton[1].boundingBox.min.x, Wbutton[0].boundingBox.min.y);  //Checks for NEXT LEVEL button bounding box.
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
	Lose Draw
*/
/******************************************************************************/
void LoseDraw()
{
	/*===============================================================================
		DRAW LOSE SCREEN
	=================================================================================*/
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(lose.pObj->texture, 0, 0);
	AEGfxSetTransform(lose .transform.m);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(lose.pObj->pMesh, AE_GFX_MDM_TRIANGLES);

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
	Lose Free
*/
/******************************************************************************/
void LoseFree()
{
	for (int i = 0; i < 2; i++)
	{
		if (Wbutton[i].pButton->pMesh)
			AEGfxMeshFree(Wbutton[i].pButton->pMesh);
	}
}

/******************************************************************************/
/*!
	Lose Unload
*/
/******************************************************************************/
void LoseUnload()
{
	for (int i = 0; i < 2; i++)
	{
		if (Wbutton[i].pButton->texture)
			AEGfxTextureUnload(Wbutton[i].pButton->texture);
	}

}

/******************************************************************************/
/*!
	Button Bounding Box
*/
/******************************************************************************/
void BoundingBoxLose()
{
	for (int i = 0; i < 2; i++)
	{
		Wbutton[i].boundingBox.min.x = Wbutton[i].pos.x - Wbutton[i].scale.x / 2;
		Wbutton[i].boundingBox.min.y = Wbutton[i].pos.y - Wbutton[i].scale.y / 2;
		Wbutton[i].boundingBox.max.x = Wbutton[i].pos.x + Wbutton[i].scale.x / 2;
		Wbutton[i].boundingBox.max.y = Wbutton[i].pos.y + Wbutton[i].scale.y / 2;
	}
}