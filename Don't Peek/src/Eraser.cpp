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
#include "Eraser.h"

Eraser EraserArray[MAX];
static int EraserNum;
static int right, left;

/******************************************************************************/
/*!
	Eraser Load
*/
/******************************************************************************/

void Eraser::LoadEraser() {

	pEraser = sGameObjList + sGameObjNum++;
	pEraser->type = TYPE_ERASER;

	pEraser->texture = AEGfxTextureLoad("Resources/eraser.png");
	AE_ASSERT_MESG(pEraser->texture, "Failed to load eraser!!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	pEraser->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pEraser->pMesh, "Failed to create eraser!!");

}


/******************************************************************************/
/*!
	Eraser Init
*/
/******************************************************************************/
void Eraser::InitEraser() {
	Scale = 80.0f;
	AEVec2Set(&vel, 5, 0);
	AEVec2* pVel = &vel;
	for (int i = 0; i < EraserNum; i++)
	{
		Eraser* Erasertemp = EraserArray + i;
		Erasertemp->flag = FLAG_ACTIVE;
		Erasertemp->vel = *pVel;
	}
}

/******************************************************************************/
/*!
	Eraser Update
*/
/******************************************************************************/
void Eraser::UpdateEraser()
{
	BoundingBox();

	for (int i = 0; i < EraserNum; i++)
	{
		Eraser* Erasertemp = EraserArray + i;

		/******************************************************************************/
		/*!
			PLAYER
		*/
		/******************************************************************************/
		if (CollisionIntersection_RectRect(player.GetBoundingBoxPlayer(), player.GetVelPlayer(), Erasertemp->boundingBox, Erasertemp->vel))
		{
			for (int j = 0; j < GetSharpenerNum(); j++)
			{
				Sharpener* Sharpenertemp = SharpenerArray + j;
				if (CollisionIntersection_RectRect(Erasertemp->boundingBox, Erasertemp->vel, Sharpenertemp->GetSharpenerBoundingBox(j), Sharpenertemp->GetSharpenerVelocity(j)) == 0)
				{
					if ((AEInputCheckCurr(AEVK_LSHIFT) && AEInputCheckCurr(AEVK_RIGHT)) && 
						(Erasertemp->boundingBox.min.x < (player.GetBoundingBoxPlayer().max.x + 5.0f)) && (Erasertemp->boundingBox.min.x > (player.GetBoundingBoxPlayer().max.x - 5.0f)))
					{
						Erasertemp->pos.x += Erasertemp->vel.x;
						right = 1;
						left = 0;
						printf("ERASER VEL RIGHT: %f\n", Erasertemp->vel.x);
					}
					if ((AEInputCheckCurr(AEVK_LSHIFT) && AEInputCheckCurr(AEVK_LEFT)) && 
						(Erasertemp->boundingBox.max.x > (player.GetBoundingBoxPlayer().min.x - 5.0f)) && (Erasertemp->boundingBox.max.x < (player.GetBoundingBoxPlayer().min.x + 5.0f)))
					{
						Erasertemp->pos.x -= Erasertemp->vel.x;
						left = 1;
						right = 0;
						printf("ERASER VEL LEFT: %f\n", Erasertemp->vel.x);
					}
				}
				else if (CollisionIntersection_RectRect(Erasertemp->boundingBox, Erasertemp->vel, Sharpenertemp->GetSharpenerBoundingBox(j), Sharpenertemp->GetSharpenerVelocity(j)))
				{
					if (AEInputCheckCurr(AEVK_RIGHT) && AEInputCheckCurr(AEVK_LSHIFT)
						&& (sharpener.GetSharpenerBoundingBox(j).max.x >= Erasertemp->boundingBox.min.x) && (Erasertemp->boundingBox.max.x > sharpener.GetSharpenerBoundingBox(j).min.x)
						&& (Erasertemp->boundingBox.min.x < (player.GetBoundingBoxPlayer().max.x + 5.0f)) && (Erasertemp->boundingBox.min.x > (player.GetBoundingBoxPlayer().max.x - 5.0f)))
					{
						Erasertemp->pos.x += Erasertemp->vel.x;
						right = 1;
						left = 0;
						printf("ELSE -- ERASER VEL RIGHT: %f\n", Erasertemp->vel.x);
					}
					else if (AEInputCheckCurr(AEVK_LEFT) && AEInputCheckCurr(AEVK_LSHIFT)
						&& (sharpener.GetSharpenerBoundingBox(j).min.x <= Erasertemp->boundingBox.max.x) && (sharpener.GetSharpenerBoundingBox(j).max.x > Erasertemp->boundingBox.min.x)
						&& (Erasertemp->boundingBox.max.x > (player.GetBoundingBoxPlayer().min.x - 5.0f)) && (Erasertemp->boundingBox.max.x < (player.GetBoundingBoxPlayer().min.x + 5.0f)))
					{
						Erasertemp->pos.x -= Erasertemp->vel.x;
						left = 1;
						right = 0;
						printf("ELSE -- ERASER VEL LEFT: %f\n", Erasertemp->vel.x);
					}
					else
					{
						Erasertemp->vel.x = 0;
						printf("eraser -> IS VEL 0: %f\n", Erasertemp->vel.x);
					}
				}
			}
		}//End of Player for loop

		/******************************************************************************/
		/*!
			SHARPENER
		*/
		/******************************************************************************/
		for (int j = 0; j < GetSharpenerNum(); j++)
		{
			Sharpener* Sharpenertemp = SharpenerArray + j;
			if (CollisionIntersection_RectRect(Erasertemp->boundingBox, Erasertemp->vel, Sharpenertemp->GetSharpenerBoundingBox(j), Sharpenertemp->GetSharpenerVelocity(j)))
			{
				Erasertemp->vel.x = 0;
				if ((player.GetBoundingBoxPlayer().max.x <= Sharpenertemp->GetSharpenerBoundingBox(j).max.x) &&
					(player.GetBoundingBoxPlayer().max.x < (Erasertemp->boundingBox.min.x + 5.0f)) && (player.GetBoundingBoxPlayer().max.x > (Erasertemp->boundingBox.min.x - 5.0f)))
				{
					Erasertemp->vel.x = 5.f;
				}
				else if ((player.GetBoundingBoxPlayer().min.x >= Sharpenertemp->GetSharpenerBoundingBox(j).min.x) &&
					(player.GetBoundingBoxPlayer().min.x > (Erasertemp->boundingBox.max.x - 5.0f)) && (player.GetBoundingBoxPlayer().min.x < (Erasertemp->boundingBox.max.x +5.0f)))
				{
					Erasertemp->vel.x = 5.f;
				}
				else
				{
					Erasertemp->vel.x = 5.f;
				}
			}

		}//End of Sharpener for loop

		/******************************************************************************/
		/*!
			HIGHLIGHTER
		*/
		/******************************************************************************/
		for (int j = 0; j < GetHighlighterNum(); j++)
		{
			Highlighter* highlightertemp = HighlighterArray + j;
			for (int s = 0; s < GetSharpenerNum(); s++)
			{
				if (right == 1) {
					if (CollisionIntersection_RectRect(Erasertemp->boundingBox, Erasertemp->vel, highlightertemp->GetHighlighterBoundingBox(j), highlightertemp->GetHighlighterVelocity(j)))
					{
						if (CollisionIntersection_RectRect(Erasertemp->boundingBox, Erasertemp->vel, sharpener.GetSharpenerBoundingBox(s), sharpener.GetSharpenerVelocity(s)) == 0)
							Erasertemp->pos.x += 5.f;
					}
				}
				else if (left == 1) {
					if (CollisionIntersection_RectRect(Erasertemp->boundingBox, Erasertemp->vel, highlightertemp->GetHighlighterBoundingBox(j), highlightertemp->GetHighlighterVelocity(j)))
					{
						if (CollisionIntersection_RectRect(Erasertemp->boundingBox, Erasertemp->vel, sharpener.GetSharpenerBoundingBox(s), sharpener.GetSharpenerVelocity(s)) == 0)
							Erasertemp->pos.x -= 5.f;
					}
				}
			}
		}//End of Highlighter for loop


		/******************************************************************************/
		/*!
			DOOR
		*/
		/******************************************************************************/
		for (int i = 0; i < Get_NumWalls(); i++)
		{
			Wall* Walltemp = Get_WallArr() + i;
			BoundingBox();
			if (CollisionIntersection_RectRect(Erasertemp->boundingBox, Erasertemp->vel, Walltemp->GetWallBoundingBox(i), { 0,0 }))
			{
				WallCollision = true;
				if (Walltemp->GetType(i) == WALL)
				{
					if (Erasertemp->pos.x >= Walltemp->GetWallBoundingBox(i).min.x)
					{
						Erasertemp->pos.x = (Walltemp->GetWallBoundingBox(i).max.x + 30);
					}
					else if (Erasertemp->pos.x <= Walltemp->GetWallBoundingBox(i).max.x)
					{
						Erasertemp->pos.x = (Walltemp->GetWallBoundingBox(i).min.x - 30);
					}
				}
			}
		}//End of Wall for loop

		/******************************************************************************/
		/*!
			WALLS
		*/
		/******************************************************************************/
		for (int j = 0; j < Get_NumWalls(); j++)
		{
			Wall* Walltemp = Get_WallArr() + j;
			if (CollisionIntersection_RectRect(Erasertemp->boundingBox, Erasertemp->vel, Walltemp->GetWallBoundingBox(j), { 0,0 }))
			{
				if (Erasertemp->pos.x < -370)
				{
					Erasertemp->pos.x = -370;
				}
			}
		}//End of Wall for loop

		//Erasertemp->pos.x += Erasertemp->vel.x * g_dt;
	}//End of Eraser for loop
}

/******************************************************************************/
/*!
	Eraser Draw
*/
/******************************************************************************/
void Eraser::DrawEraser()
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	for (int i = 0; i < EraserNum; i++)
	{
		Eraser* Erasertemp = EraserArray + i;
		AEGfxSetPosition(Erasertemp->pos.x, Erasertemp->pos.y);
		AEGfxTextureSet(pEraser->texture, 0, 0);
		AEGfxSetTransform(Erasertemp->Transform.m);
		AEGfxMeshDraw(pEraser->pMesh, AE_GFX_MDM_TRIANGLES);
	}
}

/******************************************************************************/
/*!
	Eraser Unload
*/
/******************************************************************************/
void Eraser::UnloadEraser() {

	AEGfxTextureUnload(pEraser->texture);
}

/******************************************************************************/
/*!
	Eraser Bounding Box
*/
/******************************************************************************/
void Eraser::BoundingBox()
{
	AEMtx33 Transform2, Size;
	for (int i = 0; i < EraserNum; i++)
	{
		Eraser* Erasertemp = EraserArray + i;
		AEMtx33Scale(&Size, Scale, Scale);
		AEMtx33Trans(&Transform2, Erasertemp->pos.x, Erasertemp->pos.y);
		AEMtx33Concat(&(Erasertemp->Transform), &Transform2, &Size);

		Erasertemp->boundingBox.min.x = Erasertemp->pos.x - Scale / 2;// 4;
		Erasertemp->boundingBox.min.y = Erasertemp->pos.y - Scale / 2;
		Erasertemp->boundingBox.max.x = Erasertemp->pos.x + Scale / 2;// 4;
		Erasertemp->boundingBox.max.y = Erasertemp->pos.y + Scale / 2;
	}

}
/******************************************************************************/
/*!
	Eraser Getter & Setter Functions
*/
/******************************************************************************/
AABB Eraser::GetEraserBoundingBox(int i)
{
	Eraser* Erasertemp = EraserArray + i;
	return Erasertemp->boundingBox;
}
AEVec2 Eraser::GetEraserVelocity(int i)
{
	Eraser* Erasertemp = EraserArray + i;
	return Erasertemp->vel;
}
AEVec2 Eraser::GetEraserPosition(int i)
{
	Eraser* Erasertemp = EraserArray + i;
	return Erasertemp->pos;
}
void Eraser::SetEraserPosition(int i, AEVec2 NewPos)
{
	Eraser* Erasertemp = EraserArray + i;
	Erasertemp->pos = NewPos;
}

/******************************************************************************/
/*!
	Eraser External Functions
*/
/******************************************************************************/
int GetEraserNum()
{
	return EraserNum;
}
void SetEraserNum(int Num)
{
	EraserNum = Num;
}