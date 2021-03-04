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

#include "Sharpener.h"
//#include "Highlighter.h"
#include "GameState_DontPeek.h"
#include "Collision.h"


//AEGfxTexture* sharpeners;
static GameObj* pObj;

void Sharpener::loadSharpener() {

	//memset(sGameObjList, 0, sizeof(GameObj) * GAME_OBJ_NUM_MAX);
	//sGameObjNum = 0;

	pObj = sGameObjList + sGameObjNum++;
	pObj->type = TYPE_SHARPENER;

	pObj->texture = AEGfxTextureLoad("Resources/Sharpener_Animation.png");
	AE_ASSERT_MESG(pObj->texture, "Failed to load sharpener!!");

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

	pObj->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pObj->pMesh, "Failed to create sharpener!!");

}

void Sharpener::drawSharpener() {

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(Position.x, Position.y);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(pObj->texture, 0, 0);
	AEGfxMeshDraw(pObj->pMesh, AE_GFX_MDM_TRIANGLES);
	AEGfxSetTransparency(1.0f);
}

void Sharpener::initSharpener() {
	//Velocity.x = SPEED;
	AEVec2Set(&SPEED, 10, 0);
	AEVec2Set(&Position, -100.0f, -60.0f);

	AEVec2 zero;
	AEVec2* PP = &Position;
	AEVec2Zero(&zero);
	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInst* pInst = sGameObjInstList + i;

		// check if current instance is not used
		if (pInst->flag == 0)
		{
			// it is not used => use it to create the new instance
			pInst->pObject = sGameObjList + TYPE_SHARPENER;
			pInst->flag = FLAG_ACTIVE;
			pInst->scale = 1.0f;
			pInst->posCurr = *PP;
			pInst->velCurr = SPEED;
			pInst->dirCurr = 0;
			printf("Sharpener Slot %lu\n", i);
			break;
		}
	}
}

void Sharpener::updateSharpener() {

	if (AEInputCheckCurr(AEVK_RIGHT))
	{
		Position.x += 5.0f;
		//printf("Move");
	}
	//AEGfxSetPosition(Position.x, Position.y);

	//if ((AEInputCheckCurr(AEVK_LSHIFT) || AEInputCheckCurr(AEVK_RSHIFT)) &&
	//	AEInputCheckCurr(AEVK_LEFT)) //[]o player pushing left
	//{
	//	Position.x -= Velocity.x;
	//}

	//if ((AEInputCheckCurr(AEVK_LSHIFT) || AEInputCheckCurr(AEVK_RSHIFT)) &&
	//	AEInputCheckCurr(AEVK_RIGHT)) //o[] player pushing right
	//{
	//	Position.x += Velocity.x;
	//}

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

					if ((pInst_2->flag && FLAG_ACTIVE) == 0)
						continue;

					if (pInst_2->pObject->type == TYPE_HIGHLIGHTER)
					{
						while (CollisionIntersection_RectRect(pInst_1->boundingBox, pInst_1->velCurr, pInst_2->boundingBox, pInst_2->velCurr))
						{
							pInst_1->posCurr.x += 50;
							printf("Colliding");
						}

					}
				}
			}
		}
}

void Sharpener::unloadSharpener() {

	AEGfxTextureUnload(pObj->texture);
	//AEGfxTextureUnload(sharpeners);
}