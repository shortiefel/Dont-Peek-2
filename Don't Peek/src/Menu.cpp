/* Start Header ************************************************************************/
/*!
\file Menu.cpp
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
#include "Menu.h"

static Menu menu;
static Button button;
void MenuLoad()
{
	//MENU
	menu.pos = { 0.f, 0.f };
	menu.scale = { 950.f,650.f };

	menu.pObj = sGameObjList + sGameObjNum++;
	menu.pObj->texture = AEGfxTextureLoad("Resources/Menu.png");
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

	//BUTTON
	button.pos = { -150.f, -100.f };
	button.scale = { 200.f,80.f };
	button.pObj = sGameObjList + sGameObjNum++;
	button.pObj->texture = AEGfxTextureLoad("Resources/Play.jpg");
	button.pObj->type = TYPE_PLAY;
	AE_ASSERT_MESG(button.pObj->texture, "Failed to load Menu!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	button.pObj->pMesh = AEGfxMeshEnd();

	AEMtx33	trans, sc;
	// Compute the scaling matrix
	AEMtx33Scale(&sc, menu.scale.x, menu.scale.y);
	// Compute the translation matrix
	AEMtx33Trans(&trans, menu.pos.x, menu.pos.y);

	AEMtx33Concat(&(menu.transform), &trans, &sc);

	AEMtx33Scale(&sc, button.scale.x, button.scale.y);
	// Compute the translation matrix
	AEMtx33Trans(&trans, button.pos.x, button.pos.y);

	AEMtx33Concat(&(button.transform), &trans, &sc);

}
void MenuInit()
{

}
void MenuUpdate()
{

}
void MenuDraw()
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(menu.pObj->texture, 0, 0);
	AEGfxSetTransform(menu.transform.m);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(menu.pObj->pMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxTextureSet(button.pObj->texture, 0, 0);
	AEGfxSetTransform(button.transform.m);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(button.pObj->pMesh, AE_GFX_MDM_TRIANGLES);
}
void MenuFree()
{

}
void MenuUnload()
{

}