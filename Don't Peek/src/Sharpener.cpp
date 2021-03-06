/* Start Header ************************************************************************/
/*!
\file Sharpener.cpp
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
#include "Sharpener.h"
#include "Collision.h"
#include "Highlighter.h"

Sharpener SharpenerArray[MAX];

void Sharpener::loadSharpener() {

	//memset(sGameObjList, 0, sizeof(GameObj) * GAME_OBJ_NUM_MAX);
	//sGameObjNum = 0;

	pSharpener = sGameObjList + sGameObjNum++ ;
	pSharpener->type = TYPE_SHARPENER;

	pSharpener->texture = AEGfxTextureLoad("Resources/Sharpener_Animation.png");
	AE_ASSERT_MESG(pSharpener->texture, "Failed to load sharpener!!");

	//sharpeners = AEGfxTextureLoad("Sharpener_Animation.png");
	//AEGfxVertexList* sharpener = 0;
	AEGfxMeshStart();
	AEGfxTriAdd(
		-30.0f, -30.0f, 0x00000000, 0.0f, 1.0f,
		45.0f, -30.0f, 0x00000000, 1.0f, 1.0f,
		-30.0f, 30.0f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		45.0f, -30.0f, 0x00000000, 1.0f, 1.0f,
		45.0f, 30.0f, 0x00000000, 1.0f, 0.0f,
		-30.0f, 30.0f, 0x00000000, 0.0f, 0.0f);

	pSharpener->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pSharpener->pMesh, "Failed to create sharpener!!");

}

void Sharpener::drawSharpener() {

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(pos.x, pos.y);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(pSharpener->texture, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxMeshDraw(pSharpener->pMesh, AE_GFX_MDM_TRIANGLES);
	AEGfxSetTransparency(1.0f);
}

void Sharpener::initSharpener() {
	//Velocity.x = SPEED;
	AEVec2Set(&vel, SPEED, 0);
	AEVec2Set(&pos, -100.0f, 0.0f);

	for (unsigned long i = 0; i < MAX; i++)
	{
		Sharpener* Sharpenerinst = SharpenerArray + i;
		if (flag == 0)
		{
			AEVec2Set(&pos, 0, 100);
			AEVec2Set(&vel, 0, 0);
			flag = FLAG_ACTIVE;
			printf("Init Sharpener %lu \n", i);
			break;
		}
	}
}

void Sharpener::updateSharpener() {

	if (AEInputCheckCurr(AEVK_RIGHT))
	{
		pos.x += 5.0f;
		//printf("Move");
	}
	for (unsigned long i = 0; i < MAX; i++)
	{
		Sharpener* SharpenerInst = SharpenerArray + i;
		//printf("SharpenerInst %lu", i);
		for (unsigned long j = 0; j < MAX; j++)
		{
			//printf("Check SharpenerInst %lu", i);
			Highlighter* HighlighterInst = HighlighterArray + j;
			//printf("HighlighterInst %lu", j);
			if ((flag && HighlighterInst->flag) == 0)
			{
				continue;
			}
			//printf(" Check HighlighterInst %lu",j);
			if (CollisionIntersection_RectRect(boundingBox, vel, HighlighterInst->boundingBox, HighlighterInst->vel))
			{
				pos.x += 50;
				printf("Collision True");
			}
			else
			{
				printf("No Collision");
			}
		}
	}
	/*
		for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
		{
			GameObjInst* pInst_1 = sGameObjInstList + i;
			if ((pInst_1->flag && FLAG_ACTIVE) == 0)
				continue;

			//if object is an asteroid
			if ((pInst_1->pObject->type == TYPE_SHARPENER))
			{
				//setting object instance
				for (unsigned long j = 0; j < GAME_OBJ_INST_NUM_MAX; j++)
				{
					GameObjInst* pInst_2 = sGameObjInstList + j;

					if ((pInst_2->flag && FLAG_ACTIVE) == 0 )
						continue;
					
					if (pInst_2->pObject->type == TYPE_HIGHLIGHTER)
					{
						printf("Area2");
						if (CollisionIntersection_RectRect(pInst_1->boundingBox, pInst_1->velCurr, pInst_2->boundingBox, pInst_2->velCurr))
						{
							pos.x += 50;
							printf("Colliding");
						}

					}
				}
			}
		}
		*/
}

void Sharpener::unloadSharpener() {

	AEGfxTextureUnload(pSharpener->texture);
	//AEGfxTextureUnload(sharpeners);
}

void Sharpener::BoundingBox()
{
	for (unsigned long i = 0; i < MAX; i++)
	{
		Sharpener* Sharpenerinst = SharpenerArray + i;

		if ((flag & FLAG_ACTIVE) == 0)
			continue;

		boundingBox.min.x = pos.x - 1 / 2;
		boundingBox.min.y = pos.y - 1 / 2;
		boundingBox.max.x = pos.x + 1 / 2;
		boundingBox.max.y = pos.y + 1 / 2;
		break;
		//printf("Create %lu", i);
	}
}