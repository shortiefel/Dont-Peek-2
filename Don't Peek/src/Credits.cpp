/* Start Header ************************************************************************/
/*!
\file Credits.cpp
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
#include "Credits.h"
#include "Menu.h"


static Credits credit[4];
static Button1 button;
static int element = 0;
static int x, y;
static int SetWidthCursor = 1000 / 2;
static int SetHeightCursor = 700 / 2;
void CreditsLoad()
{
	//CREDITS 1
	credit[0].pos = { 0.f, 0.f };
	credit[0].scale = { 950.f, 650.f };

	credit[0].pObj = sGameObjList + sGameObjNum++;
	credit[0].pObj->texture = AEGfxTextureLoad("Resources/Credit1.png");
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

	//CREDITS 2
	credit[1].pos = { 0.f, 0.f };
	credit[1].scale = { 950.f, 650.f };

	credit[1].pObj = sGameObjList + sGameObjNum++;
	credit[1].pObj->texture = AEGfxTextureLoad("Resources/Credit2.png");
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

	//CREDITS 3
	credit[2].pos = { 0.f, 0.f };
	credit[2].scale = { 950.f, 650.f };

	credit[2].pObj = sGameObjList + sGameObjNum++;
	credit[2].pObj->texture = AEGfxTextureLoad("Resources/Credit3.png");
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

	//CREDITS 4
	credit[3].pos = { 0.f, 0.f };
	credit[3].scale = { 950.f, 650.f };

	credit[3].pObj = sGameObjList + sGameObjNum++;
	credit[3].pObj->texture = AEGfxTextureLoad("Resources/Credit4.png");
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

	// NEXT BUTTON
	button.pos = { 0.f, -300.f };
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
	// Compute the scaling matrix
	for (int i = 0; i < 4; i++)
	{ 
		AEMtx33Scale(&sc, credit[i].scale.x, credit[i].scale.y);
		// Compute the translation matrix
		AEMtx33Trans(&trans, credit[i].pos.x, credit[i].pos.y);

		AEMtx33Concat(&(credit[i].transform), &trans, &sc);
	}
	AEMtx33Scale(&sc, button.scale.x, button.scale.y);
	// Compute the translation matrix
	AEMtx33Trans(&trans, button.pos.x, button.pos.y);

	AEMtx33Concat(&(button.transform), &trans, &sc);
}

void CreditsInit()
{

}

void CreditsUpdate()
{
		BoundingBox1();
		AEInputGetCursorPosition(&x, &y);
		if (x >= 0 && y >= 0)
		{
			x = x - SetWidthCursor;
			y -= SetHeightCursor;
			y *= -1;
		}
		if (AEInputCheckTriggered(AEVK_LBUTTON))
		{
			printf("Mouse: %d::%d\n", x, y);

			if (CollisionIntersection_PointRect({ static_cast<float>(x), static_cast<float>(y) }, { 0,0 }, button.boundingBox, { 0,0 }))
			{
				if (AEInputUpdate)
				{
					printf("BUTTON NEXT");
					printf("BBMin: %f::%f\n", button.boundingBox.min.x, button.boundingBox.min.y);
					printf("BBMax: %f::%f\n", button.boundingBox.max.x, button.boundingBox.max.y);
					if (element < 3)
					{
						element++;
					}
					else
					{
						gGameStateNext = GS_MENU;
					}
				}
			}
		}
	if (AEInputCheckCurr(AEVK_B))
		gGameStateNext = GS_MENU;

	if (AEInputCheckCurr(AEVK_ESCAPE))
		gGameStateNext = GS_QUIT;
}

void CreditsDraw()
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(credit[element].pObj->texture, 0, 0);
	AEGfxSetTransform(credit[element].transform.m);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(credit[element].pObj->pMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxTextureSet(button.pButton->texture, 0, 0);
	AEGfxSetTransform(button.transform.m);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(button.pButton->pMesh, AE_GFX_MDM_TRIANGLES);
}

void CreditsFree()
{
	
}

void CreditsUnload()
{
	if (button.pButton->pMesh)
		AEGfxMeshFree(button.pButton->pMesh);
	if (credit[element].pObj->pMesh)
		AEGfxMeshFree(credit[element].pObj->pMesh);

	if (credit[element].pObj->texture)
		AEGfxTextureUnload(credit[element].pObj->texture);
	if (button.pButton->texture)
		AEGfxTextureUnload(button.pButton->texture);
}

void BoundingBox1()
{
	button.boundingBox.min.x = button.pos.x - button.scale.x / 2;
	button.boundingBox.min.y = button.pos.y - button.scale.y / 2;
	button.boundingBox.max.x = button.pos.x + button.scale.x / 2;
	button.boundingBox.max.y = button.pos.y + button.scale.y / 2;
}
