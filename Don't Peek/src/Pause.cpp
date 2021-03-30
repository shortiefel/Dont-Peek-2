/* Start Header ************************************************************************/
/*!
\file Pause.cpp
\team name Don't Peak
\software name I don't want to do homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu
\date 24/03/2021
\brief This is the player file. It contains all the player function
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#include "main.h"
#include "GameStateMgr.h"
#include "Win.h"
#include "Pause.h"
#include "Menu.h"


Pause pause;
ButtonP Pbtn[3];
int Px, Py;
int SetWidthCursorP = 1000 / 2;
int SetHeightCursorP = 700 / 2;

void PauseLoad()
{
	//bg for pause
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

	AEMtx33	trans, sc;
	// Compute the scaling matrix
	AEMtx33Scale(&sc, pause.scale.x, pause.scale.y);
	// Compute the translation matrix
	AEMtx33Trans(&trans, pause.pos.x, pause.pos.y);

	AEMtx33Concat(&(pause.transform), &trans, &sc);


	//MAIN MENU BUTTON
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

	//NEXT LEVEL
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


	//NEXT LEVEL
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

	for (int i = 0; i < 3; i++)
	{
		AEMtx33Scale(&sc, Pbtn[i].scale.x, Pbtn[i].scale.y);
		// Compute the translation matrix
		AEMtx33Trans(&trans, Pbtn[i].pos.x, Pbtn[i].pos.y);

		AEMtx33Concat(&(Pbtn[i].transform), &trans, &sc);
	}


}

void PauseInit()
{
}

void PauseUpdate()
{
	CheckPause = true;

	AEGfxSetCamPosition(0, 0);
	BoundingBoxPause();
	AEInputGetCursorPosition(&Px, &Py);
	if (Px >= 0 && Py >= 0)
	{
		Px = Px - SetWidthCursorP;
		Py -= SetHeightCursorP;
		Py *= -1;
	}

	
	
	if (AEInputCheckTriggered(AEVK_LBUTTON))
	{
		printf("Mouse: %d::%d\n", Px, Py);

		if (CollisionIntersection_PointRect({ static_cast<float>(Px), static_cast<float>(Py) }, { 0,0 }, Pbtn[0].boundingBox, { 0,0 }))
		{

			if (gGameStatePrev == GS_TUTORIAL)
			{
				if (AEInputUpdate)
				{
					gGameStateCurr = GS_TUTORIAL;
					printf("Go tutorial");
				}
					
			}
			else if (gGameStatePrev == GS_DONT_PEEK)
			{
				if (AEInputUpdate)
				{
					gGameStateCurr = GS_DONT_PEEK;
					printf("Go level");
				}
					
			}
				
				
		}
		else if (CollisionIntersection_PointRect({ static_cast<float>(Px), static_cast<float>(Py) }, { 0,0 }, Pbtn[1].boundingBox, { 0,0 }))
		{

			if (gGameStatePrev == GS_TUTORIAL)
			{
				if (AEInputUpdate)
				{
					gGameStateNext = GS_TUTORIAL;
					printf("Go tutorial");
				}
						
			}
			else if (gGameStatePrev == GS_DONT_PEEK)
			{
				if (AEInputUpdate)
				{
					gGameStateNext = GS_DONT_PEEK;
					printf("Go level");
				}
						
			}
		}
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


	
	//MAIN BUTTONS
	if (AEInputCheckCurr(AEVK_ESCAPE))
		gGameStateNext = GS_MENU;

	if (AEInputCheckCurr(AEVK_Q))
		gGameStateNext = GS_QUIT;


}

void PauseDraw()
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(pause.pObj->texture, 0, 0);
	AEGfxSetTransform(pause.transform.m);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(pause.pObj->pMesh, AE_GFX_MDM_TRIANGLES);

	for (int i = 0; i < 3; i++)
	{
		AEGfxTextureSet(Pbtn[i].pButton->texture, 0, 0);
		AEGfxSetTransform(Pbtn[i].transform.m);
		AEGfxSetTransparency(1.0f);
		AEGfxMeshDraw(Pbtn[i].pButton->pMesh, AE_GFX_MDM_TRIANGLES);
	}
}

void PauseFree()
{
}

void PauseUnload()
{
}

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