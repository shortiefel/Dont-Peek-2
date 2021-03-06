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

void Highlighter::loadHighlighter() {

	pHighlighter = (sGameObjList + sGameObjNum++) - 1;
	pHighlighter->type = TYPE_HIGHLIGHTER;

	AEGfxMeshStart();
	AEGfxTriAdd(
		-30.0f, -30.0f, 0x00FFFF00, 0.0f, 0.0f,
		120.0f, -30.0f, 0x00FFFF00, 0.0f, 0.0f,
		-30.0f, 0.0f, 0x00FFFF00, 0.0f, 0.0f);

	AEGfxTriAdd(
		120.0f, -30.0f, 0x00FFFF00, 0.0f, 0.0f,
		120.0f, 0.0f, 0x00FFFF00, 0.0f, 0.0f,
		-30.0f, 0.0f, 0x00FFFF00, 0.0f, 0.0f);

	pHighlighter->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pHighlighter->pMesh, "Failed to create highlighter!!");

}

void Highlighter::initHighlighter() {
	for (unsigned long i = 0; i < MAX; i++)
	{
		Highlighter* Highlighterinst = HighlighterArray + i;
		if (flag == 0)
		{
			AEVec2Set(&pos, 0, 100);
			AEVec2Set(&vel, 0, 0);
			flag = FLAG_ACTIVE;
		}
		printf("Init Highlighter %lu", i);
	}

}

void Highlighter::drawHighlighter() {
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(pos.x, pos.y);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(pHighlighter->texture, 0, 0);
	AEGfxMeshDraw(pHighlighter->pMesh, AE_GFX_MDM_TRIANGLES);
	AEGfxSetTransparency(1.0f);
}

void Highlighter::updateHighlighter() 
{
	//IF sharpener has collided
	//    IF on the left []____
	//velocity.x = SPEED;

}

void Highlighter::unloadHighlighter() {

}