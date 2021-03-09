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

Highlighter HighlighterArray[MAX];
static int HighlighterNum = 0;


void Highlighter::LoadHighlighter() 
{
	pHighlighter = sGameObjList + sGameObjNum++;
	pHighlighter->type = TYPE_HIGHLIGHTER;

	AEGfxMeshStart();
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

void Highlighter::InitHighlighter() {

	scaleX = 150.0f;
	scaleY = 50.0f;
	AEVec2Set(&pos, 0, -25);
	AEVec2Set(&vel, 0, 0);
	for (int i = 0; i < 1; i++)
	{
		Highlighter* temp = HighlighterArray + i;

		temp->flag = FLAG_ACTIVE;
		temp->pos = pos;
		temp->vel = vel;
	}
}


void Highlighter::UpdateHighlighter()
{
	BoundingBox();

}

void Highlighter::DrawHighlighter() 
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < HighlighterNum; i++)
	{
		Highlighter* Highlightertemp = HighlighterArray + i;
		AEGfxSetPosition(Highlightertemp->pos.x, Highlightertemp->pos.y);
		AEGfxTextureSet(pHighlighter->texture, 0, 0);
		AEGfxSetTransform(Highlightertemp->Transform.m);
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxMeshDraw(pHighlighter->pMesh, AE_GFX_MDM_TRIANGLES);
	}
}

void Highlighter::UnloadHighlighter() 
{
	AEGfxTextureUnload(pHighlighter->texture);
}

void Highlighter::BoundingBox()
{
	AEMtx33 Transform2, Size;
	for (int i = 0; i < HighlighterNum; i++)
	{
		Highlighter* Highlightertemp = HighlighterArray + i;
		AEMtx33Scale(&Size, scaleX, scaleY);
		AEMtx33Trans(&Transform2, Highlightertemp->pos.x, Highlightertemp->pos.y);
		AEMtx33Concat(&(Highlightertemp->Transform), &Transform2, &Size);

		Highlightertemp->boundingBox.min.x = Highlightertemp->pos.x - scaleX / 2;
		Highlightertemp->boundingBox.min.y = Highlightertemp->pos.y - scaleY / 2;
		Highlightertemp->boundingBox.max.x = Highlightertemp->pos.x + scaleX / 2;
		Highlightertemp->boundingBox.max.y = Highlightertemp->pos.y + scaleY / 2;
	}
}

//Get Function
AABB Highlighter::GetHighlighterBoundingBox(int i)
{
	Highlighter* Highlightertemp = HighlighterArray + i;
	return Highlightertemp->boundingBox;
}

AEVec2 Highlighter::GetHighlighterVelocity(int i)
{
	Highlighter* Highlightertemp = HighlighterArray + i;
	return Highlightertemp->vel;
}

AEVec2 Highlighter::GetHighlighterPosition(int i)
{
	Highlighter* Highlightertemp = HighlighterArray + i;
	return Highlightertemp->pos;
}
void Highlighter::SetHighlighterPosition(int i, AEVec2 NewPos)
{
	Highlighter* Highlightertemp = HighlighterArray + i;
	Highlightertemp->pos = NewPos;
}

//External Function
int GetHighlighterNum()
{
	return HighlighterNum;
}
void SetHighlighterrNum(int Num)
{
	HighlighterNum = Num;
}
