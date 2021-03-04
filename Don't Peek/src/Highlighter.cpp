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

#include "Highlighter.h"
#include "Sharpener.h"
#include "GameState_DontPeek.h"

 GameObj* hObj;

void Highlighter::loadHighlighter() {

	hObj= sGameObjList + sGameObjNum++;
	hObj->type = TYPE_HIGHLIGHTER;

	AEGfxMeshStart();
	AEGfxTriAdd(
		-30.0f, -30.0f, 0x00FFFF00, 0.0f, 0.0f,
		120.0f, -30.0f, 0x00FFFF00, 0.0f, 0.0f,
		-30.0f, 0.0f, 0x00FFFF00, 0.0f, 0.0f);

	AEGfxTriAdd(
		120.0f, -30.0f, 0x00FFFF00, 0.0f, 0.0f,
		120.0f, 0.0f, 0x00FFFF00, 0.0f, 0.0f,
		-30.0f, 0.0f, 0x00FFFF00, 0.0f, 0.0f);

	hObj->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(hObj->pMesh, "Failed to create highlighter!!");

}

void Highlighter::initHighlighter() {
	AEVec2Set(&Position, 50, 0);
	AEVec2 zero;
	AEVec2Zero(&zero);

	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInst* pInst = sGameObjInstList + i;

		// check if current instance is not used
		if (pInst->flag == 0)
		{
			// it is not used => use it to create the new instance
			pInst->pObject = sGameObjList + TYPE_HIGHLIGHTER;
			pInst->flag = FLAG_ACTIVE;
			pInst->scale = 1.0f;
			pInst->posCurr = Position;
			pInst->velCurr = zero;
			pInst->dirCurr = 0;
			printf("Highlight Slot %lu\n", i);
			break;
		}

	}
}

void Highlighter::drawHighlighter() {
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(Position.x, Position.y);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(hObj->texture, 0, 0);
	AEGfxMeshDraw(hObj->pMesh, AE_GFX_MDM_TRIANGLES);
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