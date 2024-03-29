/* Start Header ************************************************************************/
/*!
\file Highlighter.cpp
\team name Don't Peek
\software name I Don't Wanna Do My Homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief 
This file contains all the functions that is required for our object highlighter.
When a sharpener/eraser collide into the highlighter, they will auto move either left or right. [Based on the pushing direction]
The object will not be able to stop in between the highlighter.


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/
#include "GameStateMgr.h"
#include "GameState_DontPeek.h"
#include "Highlighter.h"
#include "Animation.h"

//Initialization
Highlighter HighlighterArray[MAX];
static int HighlighterNum = 0;
Sprite HighlighterAnim;

/******************************************************************************/
/*!
	Highlighter Load
*/
/******************************************************************************/
void Highlighter::LoadHighlighter() 
{
	pHighlighter = sGameObjList + sGameObjNum++;
	/*pHighlighter->type = TYPE_HIGHLIGHTER;

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
	AE_ASSERT_MESG(pHighlighter->pMesh, "Failed to create highlighter!!");*/
	HighlighterAnim.Anim_Load(pHighlighter, "Resources/highlighter sprite sheet 4800 x 600 72dpi.png", 1.f / 8.f, TYPE_HIGHLIGHTER);

}

/******************************************************************************/
/*!
	Highlighter Init
*/
/******************************************************************************/
void Highlighter::InitHighlighter() {

	scaleX = 100.0f;
	scaleY = 60.0f;
	for (int i = 0; i < HighlighterNum; i++)
	{
		Highlighter* Highlightertemp = HighlighterArray + i;

		Highlightertemp->flag = FLAG_ACTIVE;
		Highlightertemp->vel = {0,0};
	}
	HighlighterAnim.Anim_Init(8, 1.f);
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
	/*AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetBlendColor(0.0f, 0.f, 0.f, 0.f);
	AEGfxSetTransparency(1.0f);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);*/
	for (int i = 0; i < HighlighterNum; i++)
	{
		Highlighter* Highlightertemp = HighlighterArray + i;
		HighlighterAnim.Anim_Update(pHighlighter, Highlightertemp->Transform);
		//AEGfxSetPosition(Highlightertemp->pos.x, Highlightertemp->pos.y);
		//AEGfxSetTransform(Highlightertemp->Transform.m);
		////AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		//AEGfxMeshDraw(pHighlighter->pMesh, AE_GFX_MDM_TRIANGLES);
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
	/*if (pHighlighter->pMesh)
		AEGfxMeshFree(pHighlighter->pMesh);

	if (pHighlighter->texture)
		AEGfxTextureUnload(pHighlighter->texture);*/
	HighlighterAnim.Anim_Unload(pHighlighter);
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
AABB Highlighter::GetHighlighterBoundingBox(int i)	//Allow other files to use highlighter boundingbox without changing it.
{
	Highlighter* Highlightertemp = HighlighterArray + i;
	return Highlightertemp->boundingBox;
}

AEVec2 Highlighter::GetHighlighterVelocity(int i)	//Allow other files to use highlighter velocity without changing it.
{
	Highlighter* Highlightertemp = HighlighterArray + i;
	return Highlightertemp->vel;
}

AEVec2 Highlighter::GetHighlighterPosition(int i)	//Allow other files to use highlighter position without changing it.
{
	Highlighter* Highlightertemp = HighlighterArray + i;
	return Highlightertemp->pos;
}

void Highlighter::SetHighlighterPosition(int i, AEVec2 NewPos)	//Allow other files to set the highlighter position. [This is used for level design]
{
	Highlighter* Highlightertemp = HighlighterArray + i;
	Highlightertemp->pos = NewPos;
}

/******************************************************************************/
/*!
	Highlighter External Functions
*/
/******************************************************************************/
int GetHighlighterNum()	//Allow other files to run through a loop of all the highlighter. [E.g. to detect collision of all highlighter]
{
	return HighlighterNum;
}
void SetHighlighterNum(int Num)	//Set the number of highlighter object to be created. [This is used for level design]
{
	HighlighterNum = Num;
}

