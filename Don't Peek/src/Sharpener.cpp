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
#include "Player.h"
#include "Door.h"
#include "Wall.h"

Sharpener SharpenerArray[1];
int right, left;

void Sharpener::loadSharpener() {

	//memset(sGameObjList, 0, sizeof(GameObj) * GAME_OBJ_NUM_MAX);
	//sGameObjNum = 0;

	pSharpener = sGameObjList + sGameObjNum++;
	pSharpener->type = TYPE_SHARPENER;

	pSharpener->texture = AEGfxTextureLoad("Resources/Sharpener_Animation.png");
	AE_ASSERT_MESG(pSharpener->texture, "Failed to load sharpener!!");

	//sharpeners = AEGfxTextureLoad("Sharpener_Animation.png");
	//AEGfxVertexList* sharpener = 0;
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	pSharpener->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pSharpener->pMesh, "Failed to create sharpener!!");

}

void Sharpener::initSharpener() {
	//Velocity.x = SPEED;
	Scale = 80.0f;
	flag = FLAG_ACTIVE;
	AEVec2Set(&vel, SPEED, 0);
	AEVec2Set(&pos, -150.0f, -15.0f);
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

	BoundingBox();

	for (int i = 0; i < 1; i++)
	{
		Sharpener* Sharpenertemp = SharpenerArray + i;


		/******************************************************************************/
		/*!
			DOOR
		*/
		/******************************************************************************/
		for (int s = 0; s < 1; s++)
		{
			Door* Doortemp = DoorArray + s;
			if (CollisionIntersection_RectRect(Sharpenertemp->boundingBox, Sharpenertemp->vel, Doortemp->boundingBox, Doortemp->vel))
			{
				AEVec2Set(&pos, -300, 0);
			}
		}

		/******************************************************************************/
		/*!
			PLAYER
		*/
		/******************************************************************************/
		if (CollisionIntersection_RectRect(player.GetBoundingBoxPlayer(), player.GetVelPlayer(), Sharpenertemp->boundingBox, Sharpenertemp->vel))
		{
			//printf("PLAYER COLLIDE WITH Sharpener\n");

			if ((AEInputCheckCurr(AEVK_LSHIFT) || AEInputCheckCurr(AEVK_RSHIFT)) && AEInputCheckCurr(AEVK_RIGHT))
			{
				pos.x += 5;
				right = 1;
				left = 0;
			}
			if ((AEInputCheckCurr(AEVK_LSHIFT) || AEInputCheckCurr(AEVK_RSHIFT)) && AEInputCheckCurr(AEVK_LEFT))
			{
				pos.x -= 5;
				left = 1;
				right = 0;
			}
		}

		/******************************************************************************/
		/*!
			HIGHLIGHTER
		*/
		/******************************************************************************/
		for (int j = 0; j < 1; j++)
		{
			Highlighter* highlightertemp = HighlighterArray + j;
			//printf("R: %d\n L: %d\n", right, left);
			if (right == 1) {
				if (CollisionIntersection_RectRect(Sharpenertemp->boundingBox, Sharpenertemp->vel, highlightertemp->boundingBox, highlightertemp->vel))
				{
					pos.x += 5;
					/*printf("Collision to the right is True-------------------------------------------\n");
					printf("BB2 min x %f \n", Sharpenertemp->boundingBox.min.x);
					printf("BB2 min y %f \n", Sharpenertemp->boundingBox.min.y);
					printf("BB2 maX x %f \n", Sharpenertemp->boundingBox.max.x);
					printf("BB2 max y %f \n", Sharpenertemp->boundingBox.max.y);
					printf("-\n");
					printf("BBH min x %f \n", highlightertemp->boundingBox.min.x);
					printf("BBH min y %f \n", highlightertemp->boundingBox.min.y);
					printf("BBH maX x %f \n", highlightertemp->boundingBox.max.x);
					printf("BBH max y %f \n", highlightertemp->boundingBox.max.y);*/
				}
			}
			else if (left == 1) {
				if (CollisionIntersection_RectRect(Sharpenertemp->boundingBox, Sharpenertemp->vel, highlightertemp->boundingBox, highlightertemp->vel))
				{
					pos.x -= 5;
					//printf("im moving to the lefttttttttt+++++++++++++++++++++++++++++++++++++++++\n");
				}
			}
		}

		/******************************************************************************/
		/*!
			WALLS
		*/
		/******************************************************************************/
		for (int i = 0; i < Get_NumWalls(); i++)
		{
			Wall* Walltemp = Get_WallArr() + i;
			if (CollisionIntersection_RectRect(Sharpenertemp->boundingBox, Sharpenertemp->vel, Walltemp->boundingBox, { 0,0 }))
			{
				if (pos.x < -370)
				{
					pos.x = -370;
				}

			}

		}
	}

	



}


void Sharpener::drawSharpener() {

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(pos.x, pos.y);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(pSharpener->texture, 0, 0);
	AEGfxSetTransform(Transform.m);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	//AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(pSharpener->pMesh, AE_GFX_MDM_TRIANGLES);

}

void Sharpener::unloadSharpener() {

	AEGfxTextureUnload(pSharpener->texture);
	//AEGfxTextureUnload(sharpeners);
}

void Sharpener::BoundingBox()
{
	AEMtx33 Transform2, Size;
	for (int i = 0; i < 1; i++)
	{
		Sharpener* Sharpenertemp = SharpenerArray + i;
		AEMtx33Scale(&Size, Scale, Scale);
		AEMtx33Trans(&Transform2, pos.x, pos.y);
		AEMtx33Concat(&Transform, &Transform2, &Size);

		Sharpenertemp->boundingBox.min.x = pos.x - Scale / 2;
		Sharpenertemp->boundingBox.min.y = pos.y - Scale / 2;
		Sharpenertemp->boundingBox.max.x = pos.x + Scale / 2;
		Sharpenertemp->boundingBox.max.y = pos.y + Scale / 2;
	}

}
