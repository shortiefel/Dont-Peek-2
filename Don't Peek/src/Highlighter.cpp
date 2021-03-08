/* Start Header ************************************************************************/
/*!
\file Highlighter.cpp
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
#include "GameState_DontPeek.h"
#include "Highlighter.h"
#include "Sharpener.h"


Highlighter HighlighterArray[1];

void Highlighter::loadHighlighter() {

	pHighlighter = sGameObjList + sGameObjNum++;
	pHighlighter->type = TYPE_HIGHLIGHTER;

	AEGfxMeshStart();
	//AEGfxTriAdd(
	//	-30.0f, -30.0f, 0x00FFFF00, 0.0f, 0.0f,
	//	120.0f, -30.0f, 0x00FFFF00, 0.0f, 0.0f,
	//	-30.0f, 0.0f, 0x00FFFF00, 0.0f, 0.0f);

	//AEGfxTriAdd(
	//	120.0f, -30.0f, 0x00FFFF00, 0.0f, 0.0f,
	//	120.0f, 0.0f, 0x00FFFF00, 0.0f, 0.0f,
	//	-30.0f, 0.0f, 0x00FFFF00, 0.0f, 0.0f);


	//AEGfxTriAdd(
	//	-0.5f, -0.5f, 0x00FFFF00, 0.0f, 0.0f,
	//	1.5f, -0.5f, 0x00FFFF00, 0.0f, 0.0f,
	//	-0.5f, 0.0f, 0x00FFFF00, 0.0f, 0.0f);

	//AEGfxTriAdd(
	//	1.5f, -0.5f, 0x00FFFF00, 0.0f, 0.0f,
	//	1.5f, 0.0f, 0x00FFFF00, 0.0f, 0.0f,
	//	-0.5f, 0.0f, 0x00FFFF00, 0.0f, 0.0f);

	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00FFFF00, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00FFFF00, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00FFFF00, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00FFFF00, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00FFFF00, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00FFFF00, 0.0f, 0.0f);

	pHighlighter->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pHighlighter->pMesh, "Failed to create highlighter!!");

}

void Highlighter::initHighlighter() {

	scaleX = 150.0f;
	scaleY = 50.0f;
	AEVec2Set(&pos, 100, -25);
	AEVec2Set(&vel, 0, 0);
	for (int i = 0; i < 1; i++)
	{
		Highlighter* temp = HighlighterArray + i;

		temp->flag = FLAG_ACTIVE;
		temp->pos = pos;
		temp->vel = vel;

	}
	//printf("Init Highlighter %lu \n", i);
}

void Highlighter::drawHighlighter() {
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(pos.x, pos.y);
	//AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	//AEGfxTextureSet(pHighlighter->texture, 0, 0);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetTransparency(1.0f);
	AEGfxSetTransform(Transform.m);
	AEGfxMeshDraw(pHighlighter->pMesh, AE_GFX_MDM_TRIANGLES);

}

void Highlighter::updateHighlighter()
{
	BoundingBox();

}

void Highlighter::unloadHighlighter() {

}

void Highlighter::BoundingBox()
{
	//for (int i = 0; i < 1; i++)
	//{
	//	Highlighter* temp = HighlighterArray + i;

	//	temp->boundingBox.min.x = pos.x - 100 / 2;
	//	temp->boundingBox.min.y = pos.y - 10 / 2;
	//	temp->boundingBox.max.x = pos.x + 100 / 2;
	//	temp->boundingBox.max.y = pos.y + 10 / 2;
	//}
	AEMtx33 Transform2, Size;
	for (int i = 0; i < 1; i++)
	{
		Highlighter* Highlightertemp = HighlighterArray + i;
		AEMtx33Scale(&Size, scaleX, scaleY);
		AEMtx33Trans(&Transform2, pos.x, pos.y);
		AEMtx33Concat(&Transform, &Transform2, &Size);

		Highlightertemp->boundingBox.min.x = pos.x - scaleX / 2;
		Highlightertemp->boundingBox.min.y = pos.y - scaleY / 2;
		Highlightertemp->boundingBox.max.x = pos.x + scaleX / 2;
		Highlightertemp->boundingBox.max.y = pos.y + scaleY / 2;
	}
}


