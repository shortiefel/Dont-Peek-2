/* Start Header ************************************************************************/
/*!
\file Eraser.cpp
\team name Don't Peek
\software name I Don't Wanna Do My Homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu
\date 22/01/2021
\brief 
This file contains all the functions that is required for our object eraser.
The eraser is an object that can be pushed around by the player.
Player can also jump on top of the object.
The eraser can also remove temporary wall [Pencil] when they collide.


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#include "GameStateMgr.h"
#include "GameState_DontPeek.h"
#include "Collision.h"
#include "Sharpener.h"
#include "Highlighter.h"
#include "Door.h"
#include "Player.h"
#include "Wall.h"
#include "Eraser.h"
#include "Animation.h"

//Initialization
Eraser EraserArray[MAX];
static int EraserNum;
static int right, left;
const int Eraser_Gravity = 8;
float EGROUND = 0.f;
Sprite EraserAnim;

/******************************************************************************/
/*!
	Eraser Load
*/
/******************************************************************************/
void Eraser::LoadEraser() {

	pEraser = sGameObjList + sGameObjNum++;
	/*pEraser->type = TYPE_ERASER;

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
	AE_ASSERT_MESG(pEraser->pMesh, "Failed to create eraser!!");*/
	EraserAnim.Anim_Load(pEraser, "Resources/eraser sprite sheet 1800 x 600 72dpi.png", 1.f / 3.f, TYPE_ERASER);
}


/******************************************************************************/
/*!
	Eraser Init
*/
/******************************************************************************/
void Eraser::InitEraser() 
{
	Scale = 100.0f;

	for (int i = 0; i < EraserNum; i++)
	{
		Eraser* Erasertemp = EraserArray + i;
		Erasertemp->flag = FLAG_ACTIVE;
		AEVec2Set(&(Erasertemp->vel), 0, 0);
	}
	EraserAnim.Anim_Init(3, 0.5f);
}

/******************************************************************************/
/*!
	Eraser Update
*/
/******************************************************************************/

void Eraser::UpdateEraser()
{
	EGROUND = -1000;
	BoundingBox();


	for (int i = 0; i < EraserNum; i++)
	{
		Eraser* Erasertemp = EraserArray + i;

		if (Erasertemp->pos.y < EGROUND)
		{
			Erasertemp->pos.y = EGROUND;
			Erasertemp->vel.y = 0.f;
		}
		Erasertemp->vel.x = 0.f;

		SetGravity();

		/*===============================================================================
			PLAYER
		=================================================================================*/
		if (CollisionIntersection_RectRect(player.GetBoundingBoxPlayer(), player.GetVelPlayer(), Erasertemp->boundingBox, Erasertemp->vel))
		{
			/*======================================
			/ IF: LEVEL HAS NO SHARPENER
			=======================================*/
			if (GetSharpenerNum() == 0) 
			{
				/*==================================================================
				/ RIGHT: check if Player BB max is within range of Eraser BB min
				/ LEFT : check if Player BB min is within range of Eraser BB max
				====================================================================*/

				if ((AEInputCheckCurr(AEVK_LSHIFT) && AEInputCheckCurr(AEVK_RIGHT)) &&
					(player.GetBoundingBoxPlayer().max.x > (Erasertemp->boundingBox.min.x - 15.0f)) &&
					(player.GetBoundingBoxPlayer().max.x < (Erasertemp->boundingBox.min.x + 40.0f)))
				{
					Erasertemp->vel.x = SPEED;
					right = 1;
					left = 0;
				}
				if ((AEInputCheckCurr(AEVK_LSHIFT) && AEInputCheckCurr(AEVK_LEFT)) &&
					(player.GetBoundingBoxPlayer().min.x > (Erasertemp->boundingBox.max.x - 40.0f)) &&
					(player.GetBoundingBoxPlayer().min.x < (Erasertemp->boundingBox.max.x + 15.0f)))
				{
					Erasertemp->vel.x = -SPEED;
					left = 1;
					right = 0;
				}

			}
			/*=====================================
			/ ELSE: LEVEL HAS SHARPENER
			=====================================*/
			else
			{
				for (int j = 0; j < GetSharpenerNum(); j++)
				{
					Sharpener* Sharpenertemp = SharpenerArray + j;

					/*=================================================================
					/ IF: Sharpener and Eraser are NOT colliding
					/      -> Player can push Eraser as per normal
					/
					/ RIGHT: check if player BB max is within range of Eraser BB min
					/ LEFT: check if player BB min is within range of Eraser BB max
					=================================================================*/
					if (CollisionIntersection_RectRect(Erasertemp->boundingBox, Erasertemp->vel, Sharpenertemp->GetSharpenerBoundingBox(j), Sharpenertemp->GetSharpenerVelocity(j)) == 0)
					{
						if ((AEInputCheckCurr(AEVK_LSHIFT) && AEInputCheckCurr(AEVK_RIGHT)) &&
							(player.GetBoundingBoxPlayer().max.x > (Erasertemp->boundingBox.min.x - 15.0f)) &&
							(player.GetBoundingBoxPlayer().max.x < (Erasertemp->boundingBox.min.x + 40.0f)))
						{
							Erasertemp->vel.x = SPEED;
							right = 1;
							left = 0;
						}
						if ((AEInputCheckCurr(AEVK_LSHIFT) && AEInputCheckCurr(AEVK_LEFT)) &&
							(player.GetBoundingBoxPlayer().min.x > (Erasertemp->boundingBox.max.x - 40.0f)) &&
							(player.GetBoundingBoxPlayer().min.x < (Erasertemp->boundingBox.max.x + 15.0f)))
						{
							Erasertemp->vel.x = -SPEED;
							left = 1;
							right = 0;
						}
					}
					/*==============================================================================
					/ IF: Sharpener and Eraser ARE colliding
					/      -> Player only can push Eraser towards direction away from Sharpener
					/         else cannot push
					/
					/ RIGHT: check if Player BB max is within range of Eraser BB min
					/ LEFT: check if Player BB min is within range of Eraser BB max
					===============================================================================*/
					if (CollisionIntersection_RectRect(Erasertemp->boundingBox, Erasertemp->vel, Sharpenertemp->GetSharpenerBoundingBox(j), Sharpenertemp->GetSharpenerVelocity(j)))
					{
						Erasertemp->vel.x = 0.f;
						if (AEInputCheckCurr(AEVK_RIGHT) && AEInputCheckCurr(AEVK_LSHIFT)
							&& (Sharpenertemp->GetSharpenerBoundingBox(j).max.x >= (Erasertemp->boundingBox.min.x - 15.0f))
							&& (Sharpenertemp->GetSharpenerBoundingBox(j).max.x <= (Erasertemp->boundingBox.min.x + 15.0f))
							&& (player.GetBoundingBoxPlayer().max.x > (Erasertemp->boundingBox.min.x - 15.0f))
							&& (player.GetBoundingBoxPlayer().max.x < (Erasertemp->boundingBox.min.x + 40.0f)))
						{
							Erasertemp->vel.x = SPEED;
							right = 1;
							left = 0;
						}
						else if (AEInputCheckCurr(AEVK_LEFT) && AEInputCheckCurr(AEVK_LSHIFT)
							&& (Sharpenertemp->GetSharpenerBoundingBox(j).min.x <= (Erasertemp->boundingBox.max.x + 15.0f))
							&& (Sharpenertemp->GetSharpenerBoundingBox(j).min.x >= (Erasertemp->boundingBox.max.x - 15.0f))
							&& (player.GetBoundingBoxPlayer().min.x > (Erasertemp->boundingBox.max.x - 40.0f))
							&& (player.GetBoundingBoxPlayer().min.x < (Erasertemp->boundingBox.max.x + 15.0f)))
						{
							Erasertemp->vel.x = -SPEED;
							left = 1;
							right = 0;
						}
						else
						{
							Erasertemp->vel.x = 0.f;
							Erasertemp->pos.x += Erasertemp->vel.x;
						}
					}
				}
			}
		}//End of Player for loop

		/*===============================================================================
			SHARPENER
		=================================================================================*/
		for (int j = 0; j < GetSharpenerNum(); j++)
		{
			Sharpener* Sharpenertemp = SharpenerArray + j;
			if (CollisionIntersection_RectRect(Erasertemp->boundingBox, Erasertemp->vel, Sharpenertemp->GetSharpenerBoundingBox(j), Sharpenertemp->GetSharpenerVelocity(j)))
			{
				Erasertemp->vel.x = 0.f;

				/*=======================================================================================
				/ Player only can push Eraser towards direction away from Sharpener	else cannot push
				/		-> RIGHT: check if Player BB max is within range of Eraser BB min
				/		-> LEFT : check if Player BB min is within range of Eraser BB max
				=======================================================================================*/
				if ((AEInputCheckCurr(AEVK_RIGHT) && AEInputCheckCurr(AEVK_LSHIFT))
					&& (player.GetBoundingBoxPlayer().max.x <= Sharpenertemp->GetSharpenerBoundingBox(j).max.x)
					&& (player.GetBoundingBoxPlayer().max.x > Sharpenertemp->GetSharpenerBoundingBox(j).min.x)
					&& (player.GetBoundingBoxPlayer().max.x < (Erasertemp->boundingBox.min.x + 30.0f))
					&& (player.GetBoundingBoxPlayer().max.x > (Erasertemp->boundingBox.min.x - 15.0f)))
				{
					Erasertemp->vel.x = SPEED;
				}
				else if ((AEInputCheckCurr(AEVK_LEFT) && AEInputCheckCurr(AEVK_LSHIFT))
					&& (player.GetBoundingBoxPlayer().min.x >= Sharpenertemp->GetSharpenerBoundingBox(j).min.x)
					&& (player.GetBoundingBoxPlayer().min.x < Sharpenertemp->GetSharpenerBoundingBox(j).max.x)
					&& (player.GetBoundingBoxPlayer().min.x > (Erasertemp->boundingBox.max.x - 30.0f)) 
					&& (player.GetBoundingBoxPlayer().min.x < (Erasertemp->boundingBox.max.x + 15.0f)))
				{
					Erasertemp->vel.x = -SPEED;
				}
				else
				{
					Erasertemp->vel.x += 0.f;
				}
			}

		}//End of Sharpener for loop

		/*===============================================================================
			HIGHLIGHTER
		=================================================================================*/
		for (int j = 0; j < GetHighlighterNum(); j++)
		{
			Highlighter* highlightertemp = HighlighterArray + j;
			for (int s = 0; s < GetSharpenerNum(); s++)
			{
				/*----------------------------------
					PUSHED FROM THE RIGHT
				----------------------------------*/
				if (right == 1) {
					if (CollisionIntersection_RectRect(Erasertemp->boundingBox, Erasertemp->vel, highlightertemp->GetHighlighterBoundingBox(j), highlightertemp->GetHighlighterVelocity(j)))
					{
						if (CollisionIntersection_RectRect(Erasertemp->boundingBox, Erasertemp->vel, sharpener.GetSharpenerBoundingBox(s), sharpener.GetSharpenerVelocity(s)) == 0)
						{
							Erasertemp->vel.x = SPEED;
						}
					}
				}
				/*----------------------------------
					PUSHED FROM THE LEFT
				----------------------------------*/
				else if (left == 1) {
					if (CollisionIntersection_RectRect(Erasertemp->boundingBox, Erasertemp->vel, highlightertemp->GetHighlighterBoundingBox(j), highlightertemp->GetHighlighterVelocity(j)))
					{
						if (CollisionIntersection_RectRect(Erasertemp->boundingBox, Erasertemp->vel, sharpener.GetSharpenerBoundingBox(s), sharpener.GetSharpenerVelocity(s)) == 0)
						{
							Erasertemp->vel.x = SPEED;
						}
					}
				}
			}
		}//End of Highlighter for loop

		/*===============================================================================
			DOOR
		=================================================================================*/
		for (int j = 0; j < GetDoorNum(); j++)
		{
			Door* Doortemp = DoorArray + j;
			if (CollisionIntersection_RectRect(Erasertemp->boundingBox, Erasertemp->vel, Doortemp->GetDoorBoundingBox(j), Doortemp->GetDoorVelocity(j)))
			{
				if (j == 4)
				{
					Erasertemp->pos = Doortemp->GetDoorPosition(j + 1);
					Erasertemp->pos.y -= 120;
					Erasertemp->pos.x += 100;
				}
				else if (j % 2 == 0)
				{
					Erasertemp->pos = Doortemp->GetDoorPosition(j + 1);
					Erasertemp->pos.x += 150;
				}
				else
				{
					Erasertemp->pos = Doortemp->GetDoorPosition(j - 1);
					Erasertemp->pos.x += -150;
				}
			}
		}//End of Door for loop

		/*===============================================================================
			WALLS/PLATFORM/CEILING
		=================================================================================*/
		for (int j = 0; j < Get_NumWalls(); j++)
		{
			Wall* Walltemp = Get_WallArr() + j;
			BoundingBox();

			if (CollisionIntersection_RectRect(Erasertemp->boundingBox, Erasertemp->vel, Walltemp->GetWallBoundingBox(j), { 0,0 }))
			{
				WallCollision = true;
				Erasertemp->vel.y = 0.f;
				/*----------------------------------
					WALLS
				----------------------------------*/
				if (Walltemp->GetType(j) == WALL)
				{
					/*----------------------------------
						PUSHED FROM THE RIGHT
					----------------------------------*/
					if (Erasertemp->pos.x >= Walltemp->GetWallBoundingBox(j).min.x)
					{
						Erasertemp->pos.x = (Walltemp->GetWallBoundingBox(j).max.x + Scale / 3);
					}
					/*----------------------------------
						PUSHED FROM THE LEFT
					----------------------------------*/
					else if (Erasertemp->pos.x <= Walltemp->GetWallBoundingBox(j).max.x)
					{
						Erasertemp->pos.x = (Walltemp->GetWallBoundingBox(j).min.x - Scale / 3);
					}
				}
				/*----------------------------------
					PLATFORM
				----------------------------------*/
				else if (Walltemp->GetType(j) == PLATFORM)
				{
					if (Erasertemp->pos.y >= Walltemp->GetWallBoundingBox(j).max.y + 40 && Erasertemp->vel.y < 0)
					{
						Erasertemp->vel.y = 0.f;
						Erasertemp->pos.y = Walltemp->GetWallBoundingBox(j).max.y + 40;
					}
				}
			}
		}//End of Wall for loop

		Erasertemp->pos.x += Erasertemp->vel.x * g_dt;
		Erasertemp->pos.y += Erasertemp->vel.y * g_dt;

	}//End of Eraser for loop
}

/******************************************************************************/
/*!
	Eraser Draw
*/
/******************************************************************************/
void Eraser::DrawEraser()
{
	/*AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);*/
	for (int i = 0; i < EraserNum; i++)
	{
		Eraser* Erasertemp = EraserArray + i;
		EraserAnim.Anim_Update(pEraser, Erasertemp->Transform);
		/*AEGfxSetPosition(Erasertemp->pos.x, Erasertemp->pos.y);
		AEGfxTextureSet(pEraser->texture, 0, 0);
		AEGfxSetTransform(Erasertemp->Transform.m);
		AEGfxMeshDraw(pEraser->pMesh, AE_GFX_MDM_TRIANGLES);*/
	}
}

/******************************************************************************/
/*!
	Eraser Free
*/
/******************************************************************************/
void Eraser::FreeEraser()
{
	EraserNum = 0;
}

/******************************************************************************/
/*!
	Eraser Unload
*/
/******************************************************************************/
void Eraser::UnloadEraser() 
{

		/*AEGfxTextureUnload(pEraser->texture);
		AEGfxMeshFree(pEraser->pMesh);*/
	EraserAnim.Anim_Unload(pEraser);
}

/******************************************************************************/
/*!
	Eraser Gravity
*/
/******************************************************************************/
void Eraser::SetGravity()
{
	for (int i = 0; i < EraserNum; i++)
	{
		Eraser* Erasertemp = EraserArray + i;
		Erasertemp->vel.y -= 450.f * g_dt;
	}
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

		Erasertemp->boundingBox.min.x = Erasertemp->pos.x - Scale / 2;
		Erasertemp->boundingBox.min.y = Erasertemp->pos.y - Scale / 2;
		Erasertemp->boundingBox.max.x = Erasertemp->pos.x + Scale / 2;
		Erasertemp->boundingBox.max.y = Erasertemp->pos.y + Scale / 2;
	}

}
/******************************************************************************/
/*!
	Eraser Getter & Setter Functions
*/
/******************************************************************************/
AABB Eraser::GetEraserBoundingBox(int i)				//Allow other files to use eraser boundingbox without changing it.
{
	Eraser* Erasertemp = EraserArray + i;
	return Erasertemp->boundingBox;
}
AEVec2 Eraser::GetEraserVelocity(int i)					//Allow other files to use eraser velocity without changing it.
{
	Eraser* Erasertemp = EraserArray + i;
	return Erasertemp->vel;
}
AEVec2 Eraser::GetEraserPosition(int i)					//Allow other files to use eraser position without changing it.
{
	Eraser* Erasertemp = EraserArray + i;
	return Erasertemp->pos;
}

void Eraser::SetEraserPosition(int i, AEVec2 NewPos)	//Allow other files to set the eraser position. [This is used for level design]
{
	Eraser* Erasertemp = EraserArray + i;
	Erasertemp->pos = NewPos;
}

/******************************************************************************/
/*!
	Eraser External Functions
*/
/******************************************************************************/
int GetEraserNum()				//Allow other files to run through a loop of all the eraser. [E.g. to detect collision of all eraser]
{
	return EraserNum;
}
void SetEraserNum(int Num)		//Set the number of eraser object to be created. [This is used for level design]
{
	EraserNum = Num;
}