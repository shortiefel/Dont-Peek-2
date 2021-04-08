/* Start Header ************************************************************************/
/*!
\file Credits.cpp
\team name Don't Peek
\software name I Don't Wanna Do My Homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief This file is used to display the credit screen.
There is a button to allow the credit screen to change page.
After the last page, credit will go back to main menu.


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/
#include "main.h"
#include "GameStateMgr.h"
#include "Credits.h"
#include "Menu.h"
#include "Music.h"


//Initalization
static Credits credit[5];
static Button1 button;
static int element = 0;
static int x, y;
static int SetWidthCursor = 1000 / 2;
static int SetHeightCursor = 700 / 2;

/******************************************************************************/
/*!
	Credit Load
*/
/******************************************************************************/
void CreditsLoad()
{
	/*===============================================================================
		FIRST PAGE OF CREDITS
	=================================================================================*/
	credit[0].pos = { 0.f, 0.f };
	credit[0].scale = { 950.f, 650.f };

	credit[0].pObj = sGameObjList + sGameObjNum++;
	credit[0].pObj->texture = AEGfxTextureLoad("Resources/Credit1.jpg");
	AE_ASSERT_MESG(credit[0].pObj->texture, "Failed to load credit screen!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	credit[0].pObj->pMesh = AEGfxMeshEnd();

	/*===============================================================================
		SECOND PAGE OF CREDITS
	=================================================================================*/
	credit[1].pos = { 0.f, 0.f };
	credit[1].scale = { 950.f, 650.f };

	credit[1].pObj = sGameObjList + sGameObjNum++;
	credit[1].pObj->texture = AEGfxTextureLoad("Resources/Credit2.jpg");
	AE_ASSERT_MESG(credit[1].pObj->texture, "Failed to load credit screen!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	credit[1].pObj->pMesh = AEGfxMeshEnd();

	/*===============================================================================
		THIRD PAGE OF CREDITS
	=================================================================================*/
	credit[2].pos = { 0.f, 0.f };
	credit[2].scale = { 950.f, 650.f };

	credit[2].pObj = sGameObjList + sGameObjNum++;
	credit[2].pObj->texture = AEGfxTextureLoad("Resources/Credit3.jpg");
	AE_ASSERT_MESG(credit[2].pObj->texture, "Failed to load credit screen!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	credit[2].pObj->pMesh = AEGfxMeshEnd();

	/*===============================================================================
		FOURTH PAGE OF CREDITS
	=================================================================================*/
	credit[3].pos = { 0.f, 0.f };
	credit[3].scale = { 950.f, 650.f };

	credit[3].pObj = sGameObjList + sGameObjNum++;
	credit[3].pObj->texture = AEGfxTextureLoad("Resources/Credit4.jpg");
	AE_ASSERT_MESG(credit[3].pObj->texture, "Failed to load credit screen!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	credit[3].pObj->pMesh = AEGfxMeshEnd();

	/*===============================================================================
		FIFTH PAGE OF CREDITS
	=================================================================================*/
	credit[4].pos = { 0.f, 0.f };
	credit[4].scale = { 950.f, 650.f };

	credit[4].pObj = sGameObjList + sGameObjNum++;
	credit[4].pObj->texture = AEGfxTextureLoad("Resources/Credit5.jpg");
	AE_ASSERT_MESG(credit[4].pObj->texture, "Failed to load credit screen!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	credit[4].pObj->pMesh = AEGfxMeshEnd();

	/*===============================================================================
		NEXT BUTTON
	=================================================================================*/
	button.pos = { 0.f, -200.f };
	button.scale = { 200.f,80.f };
	button.pButton = sGameObjList + sGameObjNum++;
	button.pButton->texture = AEGfxTextureLoad("Resources/Next.png");
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

	AEMtx33	trans, sc;
	/*===============================================================================
		SCALING/TRANSFORMATION/CONCAT OF ALL CREDIT SCREEN
	=================================================================================*/
	for (int i = 0; i < 5; i++)
	{ 
		AEMtx33Scale(&sc, credit[i].scale.x, credit[i].scale.y);
		// Compute the translation matrix
		AEMtx33Trans(&trans, credit[i].pos.x, credit[i].pos.y);

		AEMtx33Concat(&(credit[i].transform), &trans, &sc);
	}
	/*===============================================================================
		SCALING/TRANSFORMATION/CONCAT OF BUTTON
	=================================================================================*/
	AEMtx33Scale(&sc, button.scale.x, button.scale.y);
	// Compute the translation matrix
	AEMtx33Trans(&trans, button.pos.x, button.pos.y);

	AEMtx33Concat(&(button.transform), &trans, &sc);
}

/******************************************************************************/
/*!
	Credit Initialize
*/
/******************************************************************************/
void CreditsInit()
{
	element = 0;
	SoundSystem_Init();
	SoundSystem_SFX();
}

/******************************************************************************/
/*!
	Credit Update
*/
/******************************************************************************/
void CreditsUpdate()
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
			//printf("Mouse: %d::%d\n", x, y); //USED TO CHECK FOR MOUSE POSITION

			//IF STATEMENT TO CHECK FOR MOUSE CLICK WITHIN THE BUTTON BOUNDING BOX TO ACTIVATE BUTTON.
			if (CollisionIntersection_PointRect({ static_cast<float>(x), static_cast<float>(y) }, { 0,0 }, button.boundingBox, { 0,0 }))
			{
				if (AEInputUpdate)
				{
					//printf("BUTTON NEXT");
					//printf("BBMin: %f::%f\n", button.boundingBox.min.x, button.boundingBox.min.y); //Checks for button bounding box.
					//printf("BBMax: %f::%f\n", button.boundingBox.max.x, button.boundingBox.max.y);

					if (element < 4) //CHANGES TO NEXT BACKGROUND AS LONG AS NOT LAST PAGE.
					{
						element++;
					}
					else //IF LAST PAGE, GO BACK TO MAIN MENU
					{
						gGameStateNext = GS_MENU;
					}
				}
			}
		}

		//MAIN BUTTONS
		if (AEInputCheckCurr(AEVK_ESCAPE))
			gGameStateNext = GS_QUIT;	//Close the game

		if (AEInputCheckCurr(AEVK_B))
			gGameStateNext = GS_MENU;	//Goes back to main menu

		if (AEInputCheckCurr(AEVK_P))
			gGameStateNext = GS_PAUSE;	//Can be removed if required.

}

/******************************************************************************/
/*!
	Credit Draw
*/
/******************************************************************************/
void CreditsDraw()
{
	/*===============================================================================
		DRAW CURRENT CREDIT SCREEN
	=================================================================================*/
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(credit[element].pObj->texture, 0, 0);
	AEGfxSetTransform(credit[element].transform.m);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(credit[element].pObj->pMesh, AE_GFX_MDM_TRIANGLES);

	/*===============================================================================
		DRAW NEXT BUTTON
	=================================================================================*/
	AEGfxTextureSet(button.pButton->texture, 0, 0);
	AEGfxSetTransform(button.transform.m);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(button.pButton->pMesh, AE_GFX_MDM_TRIANGLES);
}

/******************************************************************************/
/*!
	Credit Free
*/
/******************************************************************************/
void CreditsFree()
{
	SoundSystem_Destroy();
}

/******************************************************************************/
/*!
	Credit Unload
*/
/******************************************************************************/
void CreditsUnload()
{
	
	for (int i = 0; i < 5; i++)
	{
		if (credit[i].pObj->pMesh)
			AEGfxMeshFree(credit[i].pObj->pMesh);
		if (credit[i].pObj->texture)
			AEGfxTextureUnload(credit[i].pObj->texture);
	}

	if (button.pButton->pMesh)
		AEGfxMeshFree(button.pButton->pMesh);
	if (button.pButton->texture)
		AEGfxTextureUnload(button.pButton->texture);
}

/******************************************************************************/
/*!
	Button Bounding Box
*/
/******************************************************************************/
void BoundingBox1()
{
	button.boundingBox.min.x = button.pos.x - button.scale.x / 2;
	button.boundingBox.min.y = button.pos.y - button.scale.y / 2;
	button.boundingBox.max.x = button.pos.x + button.scale.x / 2;
	button.boundingBox.max.y = button.pos.y + button.scale.y / 2;
}
