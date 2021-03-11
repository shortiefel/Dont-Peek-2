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
#include "Collision.h"
#include "Sharpener.h"
#include "Highlighter.h"
#include "Door.h"
#include "Player.h"
#include "Wall.h"

Sharpener SharpenerArray[MAX];
static int SharpenerNum;
int right, left;

/******************************************************************************/
/*!
	Sharpener Load
*/
/******************************************************************************/
void Sharpener::LoadSharpener() 
{
	pSharpener = sGameObjList + sGameObjNum++;
	pSharpener->type = TYPE_SHARPENER;

	pSharpener->texture = AEGfxTextureLoad("Resources/Sharpener_Animation.png");
	AE_ASSERT_MESG(pSharpener->texture, "Failed to load sharpener!!");

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

/******************************************************************************/
/*!
	Sharpener Init
*/
/******************************************************************************/
void Sharpener::InitSharpener() {
	//Velocity.x = SPEED;
	Scale = 80.0f;
	AEVec2Set(&vel, SPEED, 0);
	AEVec2* pVel = &vel;
	for (int i = 0; i < SharpenerNum; i++)
	{
		Sharpener* Sharpenertemp = SharpenerArray + i;
		Sharpenertemp->flag = FLAG_ACTIVE;
		Sharpenertemp->vel = *pVel;
	}
}

/******************************************************************************/
/*!
	Sharpener Update
*/
/******************************************************************************/
void Sharpener::UpdateSharpener() 
{
	BoundingBox();

	for (int i = 0; i < SharpenerNum; i++)
	{
		Sharpener* Sharpenertemp = SharpenerArray + i;
		BoundingBox();
		/******************************************************************************/
		/*!
			DOOR
		*/
		/******************************************************************************/
		for (int j = 0; j < GetDoorNum(); j++)
		{
			Door* Doortemp = DoorArray + j;
			if (CollisionIntersection_RectRect(Sharpenertemp->boundingBox, Sharpenertemp->vel, Doortemp->GetDoorBoundingBox(j), Doortemp->GetDoorVelocity(j)))
			{
				if (j % 2 == 0)
				{
					Sharpenertemp->pos = Doortemp->GetDoorPosition(j + 1);
					Sharpenertemp->pos.x += 50;
				}
				else
				{
					Sharpenertemp->pos = Doortemp->GetDoorPosition(j - 1);
					Sharpenertemp->pos.x += -50;
				}
			}
		}//End of Door for loop

		/******************************************************************************/
		/*!
			WALLS
		*/
		/******************************************************************************/
		for (int j = 0; j < Get_NumWalls(); j++)
		{
			Wall* Walltemp = Get_WallArr() + j;
			if (CollisionIntersection_RectRect(Sharpenertemp->boundingBox, Sharpenertemp->vel, Walltemp->GetWallBoundingBox(j), { 0,0 }))
			{
				if (Sharpenertemp->boundingBox.max.x >= Walltemp->GetWallBoundingBox(j).min.x && right == 1)
				{
					Sharpenertemp->pos.x = (Walltemp->GetWallBoundingBox(j).min.x - 30);
				}
				else if (Sharpenertemp->boundingBox.min.x <= Walltemp->GetWallBoundingBox(j).max.x && left == 1)
				{
					Sharpenertemp->pos.x = (Walltemp->GetWallBoundingBox(j).max.x + 30);
					//printf("collide 2 \n");
				}
			}
		}//End of Wall for loop
		/******************************************************************************/
		/*!
			PLAYER
		*/
		/******************************************************************************/
		if (CollisionIntersection_RectRect(player.GetBoundingBoxPlayer(), player.GetVelPlayer(), Sharpenertemp->boundingBox, Sharpenertemp->vel))
		{
			if ((AEInputCheckCurr(AEVK_LSHIFT) || AEInputCheckCurr(AEVK_RSHIFT)) && AEInputCheckCurr(AEVK_RIGHT))
			{
				Sharpenertemp->pos.x += Sharpenertemp->vel.x;
				right = 1;
				left = 0;
			}
			if ((AEInputCheckCurr(AEVK_LSHIFT) || AEInputCheckCurr(AEVK_RSHIFT)) && AEInputCheckCurr(AEVK_LEFT))
			{
				Sharpenertemp->pos.x -= Sharpenertemp->vel.x;
				left = 1;
				right = 0;
			}
		}

		/******************************************************************************/
		/*!
			HIGHLIGHTER
		*/
		/******************************************************************************/
		for (int j = 0; j < GetHighlighterNum(); j++)
		{
			Highlighter* highlightertemp = HighlighterArray + j;
			if (right == 1) {
				if (CollisionIntersection_RectRect(Sharpenertemp->boundingBox, Sharpenertemp->vel, highlightertemp->GetHighlighterBoundingBox(j), highlightertemp->GetHighlighterVelocity(j)))
				{
					Sharpenertemp->pos.x += 5;
				}
			}
			else if (left == 1) {
				if (CollisionIntersection_RectRect(Sharpenertemp->boundingBox, Sharpenertemp->vel, highlightertemp->GetHighlighterBoundingBox(j), highlightertemp->GetHighlighterVelocity(j)))
				{
					Sharpenertemp->pos.x -= 5;
				}
			}
		}//End of Highlighter for loop
	}//End of Sharpener for loop
}

/******************************************************************************/
/*!
	Sharpener Draw
*/
/******************************************************************************/
void Sharpener::DrawSharpener() 
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	for (int i = 0; i < SharpenerNum; i++)
	{
		Sharpener* Sharpenertemp = SharpenerArray + i;
		AEGfxSetPosition(Sharpenertemp->pos.x, Sharpenertemp->pos.y);
		AEGfxTextureSet(pSharpener->texture, 0, 0);
		AEGfxSetTransform(Sharpenertemp->Transform.m);
		AEGfxMeshDraw(pSharpener->pMesh, AE_GFX_MDM_TRIANGLES);
	}
}

/******************************************************************************/
/*!
	Sharpener Unload
*/
/******************************************************************************/
void Sharpener::UnloadSharpener() {

	AEGfxTextureUnload(pSharpener->texture);
}

/******************************************************************************/
/*!
	Sharpener Bounding Box
*/
/******************************************************************************/
void Sharpener::BoundingBox()
{
	AEMtx33 Transform2, Size;
	for (int i = 0; i < SharpenerNum; i++)
	{
		Sharpener* Sharpenertemp = SharpenerArray + i;
		AEMtx33Scale(&Size, Scale, Scale);
		AEMtx33Trans(&Transform2, Sharpenertemp->pos.x, Sharpenertemp->pos.y);
		AEMtx33Concat(&(Sharpenertemp->Transform), &Transform2, &Size);

		Sharpenertemp->boundingBox.min.x = Sharpenertemp->pos.x - Scale / 3;
		Sharpenertemp->boundingBox.min.y = Sharpenertemp->pos.y - Scale / 2;
		Sharpenertemp->boundingBox.max.x = Sharpenertemp->pos.x + Scale / 3;
		Sharpenertemp->boundingBox.max.y = Sharpenertemp->pos.y + Scale / 2;
	}

}
/******************************************************************************/
/*!
	Sharpener Getter & Setter Functions
*/
/******************************************************************************/
AABB Sharpener::GetSharpenerBoundingBox(int i)
{
	Sharpener* Sharpenertemp = SharpenerArray + i;
	return Sharpenertemp->boundingBox;
}
AEVec2 Sharpener::GetSharpenerVelocity(int i)
{
	Sharpener* Sharpenertemp = SharpenerArray + i;
	return Sharpenertemp->vel;
}
AEVec2 Sharpener::GetSharpenerPosition(int i)
{
	Sharpener* Sharpenertemp = SharpenerArray + i;
	return Sharpenertemp->pos;
}
void Sharpener::SetSharpenerPosition(int i, AEVec2 NewPos)
{
	Sharpener* Sharpenertemp = SharpenerArray + i;
	Sharpenertemp->pos = NewPos;
}

/******************************************************************************/
/*!
	Sharpener External Functions
*/
/******************************************************************************/
int GetSharpenerNum()
{
	return SharpenerNum;
}
void SetSharpenerNum(int Num)
{
	SharpenerNum = Num;
}

