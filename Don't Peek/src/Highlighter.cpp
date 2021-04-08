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
#include "GameStateMgr.h"
#include "GameState_DontPeek.h"
#include "Highlighter.h"


Highlighter HighlighterArray[MAX];
static int HighlighterNum = 0;

/******************************************************************************/
/*!
	Highlighter Load
*/
/******************************************************************************/
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
	printf("highlighter LOAD\n");
}

/******************************************************************************/
/*!
	Highlighter Init
*/
/******************************************************************************/
void Highlighter::InitHighlighter() {

	scaleX = 150.0f;
	scaleY = 50.0f;
	for (int i = 0; i < HighlighterNum; i++)
	{
		Highlighter* Highlightertemp = HighlighterArray + i;

		Highlightertemp->flag = FLAG_ACTIVE;
		Highlightertemp->vel = {0,0};
	}
	printf("highlighter INIT\n");
}

/******************************************************************************/
/*!
	Highlighter Update
*/
/******************************************************************************/
void Highlighter::UpdateHighlighter()
{
	BoundingBox();
}

/******************************************************************************/
/*!
	Highlighter Draw
*/
/******************************************************************************/
void Highlighter::DrawHighlighter() 
{
	
	for (int i = 0; i < HighlighterNum; i++)
	{
		Highlighter* Highlightertemp = HighlighterArray + i;
		AEGfxSetBlendMode(AE_GFX_BM_NONE);
		//AEGfxSetBlendColor(0.0f, 0.f, 0.f, 0.f);
		AEGfxSetTransparency(1.0f);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetPosition(Highlightertemp->pos.x, Highlightertemp->pos.y);
		AEGfxSetTransform(Highlightertemp->Transform.m);
		//AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxMeshDraw(pHighlighter->pMesh, AE_GFX_MDM_TRIANGLES);
	}
}

/******************************************************************************/
/*!
	Highlighter Free
*/
/******************************************************************************/
void Highlighter::FreeHighlighter()
{
	HighlighterNum = 0;
}

/******************************************************************************/
/*!
	Highlighter Unload
*/
/******************************************************************************/
void Highlighter::UnloadHighlighter()
{
	if (pHighlighter->pMesh)
		AEGfxMeshFree(pHighlighter->pMesh);

	if (pHighlighter->texture)
		AEGfxTextureUnload(pHighlighter->texture);
	printf("highlighter DESTROY\n");
}

/******************************************************************************/
/*!
	Highlighter Bounding Box
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
	Highlighter Getter & Setter Functions
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
	Highlighter External Functions
*/
/******************************************************************************/
int GetHighlighterNum()
{
	return HighlighterNum;
}
void SetHighlighterNum(int Num)
{
	HighlighterNum = Num;
}

//set pos scale type
//remove scale in init