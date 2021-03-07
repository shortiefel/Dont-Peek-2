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
<<<<<<< HEAD

//Sharpener SharpenerArray[MAX];
=======
#include "Highlighter.h"

Sharpener SharpenerArray[1];
>>>>>>> origin/DontTouch

void Sharpener::loadSharpener() {

	//memset(sGameObjList, 0, sizeof(GameObj) * GAME_OBJ_NUM_MAX);
	//sGameObjNum = 0;

<<<<<<< HEAD
	pSharpener = sGameObjList + sGameObjNum++;
=======
	pSharpener = sGameObjList + sGameObjNum++ ;
>>>>>>> origin/DontTouch
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

<<<<<<< HEAD
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
	flag = FLAG_ACTIVE;
	AEVec2Set(&vel, SPEED, 0);
	AEVec2Set(&pos, -100.0f, 100.0f);

	//printf("Init Sharpener %lu \n", i);

}

void Sharpener::updateSharpener() {

=======
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
	flag = FLAG_ACTIVE;
	AEVec2Set(&vel, SPEED, 0);
	AEVec2Set(&pos, -100.0f, 100.0f);
	AEVec2* pPos = &pos;
	AEVec2* pVel = &vel;
	for (int i = 0; i < 1; i++)
	{
		Sharpener* Sharpenertemp = SharpenerArray + i;
		Sharpenertemp->flag = FLAG_ACTIVE;
		Sharpenertemp->pos = *pPos;
		Sharpenertemp->vel = *pVel;
	}
	
	//printf("Init Sharpener %lu \n", i);

}

void Sharpener::updateSharpener() {
	
>>>>>>> origin/DontTouch
	if (AEInputCheckCurr(AEVK_RIGHT))
	{
		pos.x += 5.0f;
		//printf("Move");
	}
	if (AEInputCheckCurr(AEVK_LEFT))
	{
		pos.x -= 5.0f;
		//printf("Move");
	}
	if (AEInputCheckCurr(AEVK_UP))
	{
		pos.y += 5.0f;
		//printf("Move");
	}
	if (AEInputCheckCurr(AEVK_DOWN))
<<<<<<< HEAD
	{
		pos.y -= 5.0f;
		//printf("Move");
	}
	BoundingBox();
	for (int i = 0; i < 1; i++)
	{
		Highlighter* temp = HighlighterArray + i;
		if (CollisionIntersection_RectRect(boundingBox, vel, temp->boundingBox, temp->vel))
		{
			pos.x += 5;
			printf("Collision True");
			printf("BB2 min x %f \n", boundingBox.min.x);
			printf("BB2 min y %f \n", boundingBox.min.y);
			printf("BB2 maX x %f \n", boundingBox.max.x);
			printf("BB2 max y %f \n", boundingBox.max.y);
			printf("BB min x %f \n", temp->boundingBox.min.x);
			printf("BB min y %f \n", temp->boundingBox.min.y);
			printf("BB maX x %f \n", temp->boundingBox.max.x);
			printf("BB max y %f \n", temp->boundingBox.max.y);
		}
=======
	{
		pos.y -= 5.0f;
		//printf("Move");
	}
	BoundingBox();
	for (int i = 0; i < 1; i++)
	{
		Sharpener* Sharpenertemp = SharpenerArray + i;
		for (int j = 0; j < 1; j++)
		{
			Highlighter* highlightertemp = HighlighterArray + j;
			if (CollisionIntersection_RectRect(Sharpenertemp->boundingBox, Sharpenertemp->vel, highlightertemp->boundingBox, highlightertemp->vel))
			{
				pos.x += 5;
				printf("Collision True");
				printf("BB2 min x %f \n", Sharpenertemp->boundingBox.min.x);
				printf("BB2 min y %f \n", Sharpenertemp->boundingBox.min.y);
				printf("BB2 maX x %f \n", Sharpenertemp->boundingBox.max.x);
				printf("BB2 max y %f \n", Sharpenertemp->boundingBox.max.y);
				printf("BB min x %f \n", highlightertemp->boundingBox.min.x);
				printf("BB min y %f \n", highlightertemp->boundingBox.min.y);
				printf("BB maX x %f \n", highlightertemp->boundingBox.max.x);
				printf("BB max y %f \n", highlightertemp->boundingBox.max.y);
			}
		}
	}
	/*
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
	for (int i = 0; i < 1; i++)
	{
		Sharpener* Sharpenertemp = SharpenerArray + i;

		Sharpenertemp->boundingBox.min.x = pos.x - 10 / 2;
		Sharpenertemp->boundingBox.min.y = pos.y - 10 / 2;
		Sharpenertemp->boundingBox.max.x = pos.x + 10 / 2;
		Sharpenertemp->boundingBox.max.y = pos.y + 10 / 2;
>>>>>>> origin/DontTouch
	}
	/*
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

	boundingBox.min.x = pos.x - 10 / 2;
	boundingBox.min.y = pos.y - 10 / 2;
	boundingBox.max.x = pos.x + 10 / 2;
	boundingBox.max.y = pos.y + 10 / 2;

}