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
\brief 
This file contains all the functions that is required for our object sharpener.
The sharpener is an object that can be pushed around by the player. 
Player can also jump on top of the object.


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
#include "Eraser.h"
#include "Highlighter.h"
#include "Door.h"
#include "Player.h"
#include "Pencil.h"
#include "Wall.h"
#include "Animation.h"

//Initialization
Sharpener SharpenerArray[MAX]; //Array is global as all other files need to use the information inside the array.
static int SharpenerNum;
static int right, left;
const int Sharpener_Gravity = 8;
float SGROUND = 0.f;
Sprite SharpenerAnim;

/******************************************************************************/
/*!
	Sharpener Load
*/
/******************************************************************************/
void Sharpener::LoadSharpener()
{
	pSharpener = sGameObjList + sGameObjNum++;
	/*pSharpener->type = TYPE_SHARPENER;

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
	AE_ASSERT_MESG(pSharpener->pMesh, "Failed to create sharpener!!");*/
	SharpenerAnim.Anim_Load(pSharpener, "Resources/sharpener sprite sheet 1800 x 600 72dpi.png", 1.f / 3.f, TYPE_SHARPENER);

}

/******************************************************************************/
/*!
	Sharpener Init
*/
/******************************************************************************/
void Sharpener::InitSharpener() 
{
	Scale = 100.0f;

	for (int i = 0; i < SharpenerNum; i++)
	{
		Sharpener* Sharpenertemp = SharpenerArray + i;
		Sharpenertemp->flag = FLAG_ACTIVE;
		AEVec2Set(&(Sharpenertemp->vel), 0, 0);
	}
	SharpenerAnim.Anim_Init(3, 0.5f);
}

/******************************************************************************/
/*!
	Sharpener Update
*/
/******************************************************************************/
void Sharpener::UpdateSharpener()
{
	SGROUND = -1000;
	BoundingBox();

	for (int i = 0; i < SharpenerNum; i++)
	{
		Sharpener* Sharpenertemp = SharpenerArray + i;

		if (Sharpenertemp->pos.y < SGROUND)
		{
			Sharpenertemp->pos.y = SGROUND;
			Sharpenertemp->vel.y = 0;
		}
		Sharpenertemp->vel.x = 0.f;

		SetGravity();

		/*===============================================================================
			PLAYER
		=================================================================================*/
		if (CollisionIntersection_RectRect(player.GetBoundingBoxPlayer(), player.GetVelPlayer(), Sharpenertemp->boundingBox, Sharpenertemp->vel))
		{
			/*======================================
			/ IF: LEVEL HAS NO ERASER
			=======================================*/
			if (GetEraserNum() == 0)
			{
				/*====================================================================
				/ RIGHT: check if Player BB max is within range of Sharpener BB min
				/ LEFT : check if Player BB min is within range of Sharpener BB max
				======================================================================*/
				if ((AEInputCheckCurr(AEVK_LSHIFT) && AEInputCheckCurr(AEVK_RIGHT)) 
					&& (player.GetBoundingBoxPlayer().max.x > (Sharpenertemp->boundingBox.min.x - 15.0f)) 
					&& (player.GetBoundingBoxPlayer().max.x < (Sharpenertemp->boundingBox.min.x + 40.0f)))
				{
					Sharpenertemp->vel.x = SPEED;
					right = 1;
					left = 0;
				}
				if ((AEInputCheckCurr(AEVK_LSHIFT) && AEInputCheckCurr(AEVK_LEFT)) 
					&& (player.GetBoundingBoxPlayer().min.x > (Sharpenertemp->boundingBox.max.x - 40.0f)) 
					&& (player.GetBoundingBoxPlayer().min.x < (Sharpenertemp->boundingBox.max.x + 15.0f)))
				{
					Sharpenertemp->vel.x = -SPEED;
					left = 1;
					right = 0;
				}
			}
			/*=====================================
			/ ELSE: LEVEL HAS ERASER
			=====================================*/
			else
			{
				for (int j = 0; j < GetEraserNum(); j++)
				{
					Eraser* Erasertemp = EraserArray + j;

					/*=================================================================
					/ IF: Eraser and Sharpener are NOT colliding
					/      -> Player can push Sharpener as per normal
					/
					/ RIGHT: check if player BB max is within range of Sharpener BB min
					/ LEFT: check if player BB min is within range of Sharpener BB max
					=================================================================*/
					if (CollisionIntersection_RectRect(Sharpenertemp->boundingBox, Sharpenertemp->vel, Erasertemp->GetEraserBoundingBox(j), Erasertemp->GetEraserVelocity(j)) == 0)
					{
						if ((AEInputCheckCurr(AEVK_LSHIFT) && AEInputCheckCurr(AEVK_RIGHT))
							&& (player.GetBoundingBoxPlayer().max.x > (Sharpenertemp->boundingBox.min.x - 15.0f))
							&& (player.GetBoundingBoxPlayer().max.x < (Sharpenertemp->boundingBox.min.x + 40.0f)))
						{
							Sharpenertemp->vel.x = SPEED;
							right = 1;
							left = 0;
						}
						if ((AEInputCheckCurr(AEVK_LSHIFT) && AEInputCheckCurr(AEVK_LEFT))
							&& (player.GetBoundingBoxPlayer().min.x > (Sharpenertemp->boundingBox.max.x - 40.0f))
							&& (player.GetBoundingBoxPlayer().min.x < (Sharpenertemp->boundingBox.max.x + 15.0f)))
						{
							Sharpenertemp->vel.x = -SPEED;
							left = 1;
							right = 0;
						}
					}
					/*==============================================================================
					/ IF: Eraser and Sharpener ARE colliding
					/      -> Player only can push Sharpener towards direction away from Eraser
					/         else cannot push
					/
					/ RIGHT: check if Player BB max is within range of Sharpener BB min
					/ LEFT: check if Player BB min is within range of Sharpener BB max
					===============================================================================*/
					if (CollisionIntersection_RectRect(Sharpenertemp->boundingBox, Sharpenertemp->vel, Erasertemp->GetEraserBoundingBox(j), Erasertemp->GetEraserVelocity(j)))
					{
						Sharpenertemp->vel.x = 0.f;
						if (AEInputCheckCurr(AEVK_RIGHT) && AEInputCheckCurr(AEVK_LSHIFT)
							&& (Erasertemp->GetEraserBoundingBox(j).max.x >= (Sharpenertemp->boundingBox.min.x - 15.0f))
							&& (Erasertemp->GetEraserBoundingBox(j).max.x <= (Sharpenertemp->boundingBox.min.x + 15.0f))
							&& (player.GetBoundingBoxPlayer().max.x > (Sharpenertemp->boundingBox.min.x - 15.0f))
							&& (player.GetBoundingBoxPlayer().max.x < (Sharpenertemp->boundingBox.min.x + 40.0f)))
						{
							Sharpenertemp->vel.x = SPEED;
							right = 1;
							left = 0;
						}
						else if (AEInputCheckCurr(AEVK_LEFT) && AEInputCheckCurr(AEVK_LSHIFT)
							&& (Erasertemp->GetEraserBoundingBox(j).min.x <= (Sharpenertemp->boundingBox.max.x + 15.0f))
							&& (Erasertemp->GetEraserBoundingBox(j).min.x >= (Sharpenertemp->boundingBox.max.x - 15.0f))
							&&(player.GetBoundingBoxPlayer().min.x > (Sharpenertemp->boundingBox.max.x - 40.0f))
							&& (player.GetBoundingBoxPlayer().min.x < (Sharpenertemp->boundingBox.max.x + 15.0f)))
						{
							Sharpenertemp->vel.x = -SPEED;
							left = 1;
							right = 0;
						}
						else
						{
							Sharpenertemp->vel.x = 0.f;
							Sharpenertemp->pos.x += Sharpenertemp->vel.x;
						}
					}
				}
			}
		}//End of Player for loop


		/*===============================================================================
			ERASER
		=================================================================================*/

		for (int j = 0; j < GetEraserNum(); j++)
		{
			Eraser* Erasertemp = EraserArray + j;
			if (CollisionIntersection_RectRect(Sharpenertemp->boundingBox, Sharpenertemp->vel, eraser.GetEraserBoundingBox(j), eraser.GetEraserVelocity(j)))
			{
				Sharpenertemp->vel.x = 0.f;

				/*=======================================================================================
				/ Player only can push Sharpener towards direction away from Eraser	else cannot push
				/		-> RIGHT: check if Player BB max is within range of Sharpener BB min
				/		-> LEFT : check if Player BB min is within range of Sharpener BB max
				=======================================================================================*/
				if ((AEInputCheckCurr(AEVK_RIGHT) && AEInputCheckCurr(AEVK_LSHIFT))
					&& (player.GetBoundingBoxPlayer().max.x <= Erasertemp->GetEraserBoundingBox(j).max.x)
					&& (player.GetBoundingBoxPlayer().max.x > Erasertemp->GetEraserBoundingBox(j).min.x)
					&& (player.GetBoundingBoxPlayer().max.x > (Sharpenertemp->boundingBox.min.x - 15.0f))
					&& (player.GetBoundingBoxPlayer().max.x < (Sharpenertemp->boundingBox.min.x + 40.0f)))
				{
					Sharpenertemp->vel.x = SPEED;
				}
				else if ((AEInputCheckCurr(AEVK_LEFT) && AEInputCheckCurr(AEVK_LSHIFT))
					&& (player.GetBoundingBoxPlayer().min.x >= Erasertemp->GetEraserBoundingBox(j).min.x)
					&& (player.GetBoundingBoxPlayer().min.x < Erasertemp->GetEraserBoundingBox(j).max.x)
					&& (player.GetBoundingBoxPlayer().min.x > (Sharpenertemp->boundingBox.max.x - 40.0f))
					&& (player.GetBoundingBoxPlayer().min.x < (Sharpenertemp->boundingBox.max.x + 15.0f)))
				{
					Sharpenertemp->vel.x = -SPEED;
				}
				else
				{
					Sharpenertemp->vel.x += 0.f;

				}
			}

		}//End of Eraser loop

		/*===============================================================================
			PENCIL
		=================================================================================*/
		for (int j = 0; j < GetPencilNum(); j++)
		{
			Pencil* Penciltemp = PencilArray + j;
			if (CollisionIntersection_RectRect(Sharpenertemp->boundingBox, Sharpenertemp->vel, Penciltemp->GetPencilBoundingBox(j), Penciltemp->GetPencilVelocity(j)))
			{
				Sharpenertemp->vel.x = 0.f;
			}
		}//End of Pencil for loop


		/*===============================================================================
			HIGHLIGHTER
		=================================================================================*/
		for (int x = 0; x < GetHighlighterNum(); x++)
		{
			Highlighter* highlightertemp = HighlighterArray + x;

			for (int j = 0; j < GetEraserNum(); j++)
			{
				for (int s = 0; s < GetPencilNum(); s++)
				{
					Pencil* Penciltemp = PencilArray + s;
					if (right == 1) {
						if (CollisionIntersection_RectRect(Sharpenertemp->boundingBox, Sharpenertemp->vel, highlightertemp->GetHighlighterBoundingBox(x), highlightertemp->GetHighlighterVelocity(x)))
						{
							if (CollisionIntersection_RectRect(Sharpenertemp->boundingBox, Sharpenertemp->vel, eraser.GetEraserBoundingBox(j), eraser.GetEraserVelocity(j)) == 0
								&& CollisionIntersection_RectRect(Sharpenertemp->boundingBox, Sharpenertemp->vel, Penciltemp->GetPencilBoundingBox(s), Penciltemp->GetPencilVelocity(s)) == 0)
							{
								Sharpenertemp->vel.x = SPEED;
							}
						}
					}
					else if (left == 1) {
						if (CollisionIntersection_RectRect(Sharpenertemp->boundingBox, Sharpenertemp->vel, highlightertemp->GetHighlighterBoundingBox(x), highlightertemp->GetHighlighterVelocity(x)))
						{
							if (CollisionIntersection_RectRect(Sharpenertemp->boundingBox, Sharpenertemp->vel, eraser.GetEraserBoundingBox(j), eraser.GetEraserVelocity(j)) == 0
								&& CollisionIntersection_RectRect(Sharpenertemp->boundingBox, Sharpenertemp->vel, Penciltemp->GetPencilBoundingBox(s), Penciltemp->GetPencilVelocity(s)) == 0)
							{
								Sharpenertemp->vel.x = -SPEED;
							}
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
			if (CollisionIntersection_RectRect(Sharpenertemp->boundingBox, Sharpenertemp->vel, Doortemp->GetDoorBoundingBox(j), Doortemp->GetDoorVelocity(j)))
			{
				if (j == 4)
				{
					Sharpenertemp->pos = Doortemp->GetDoorPosition(j + 1);
					Sharpenertemp->pos.y -= 120;
					Sharpenertemp->pos.x += 100;
				}
				else if (j % 2 == 0)
				{
					Sharpenertemp->pos = Doortemp->GetDoorPosition(j + 1);
					Sharpenertemp->pos.x += 150;
				}
				else
				{
					Sharpenertemp->pos = Doortemp->GetDoorPosition(j - 1);
					Sharpenertemp->pos.x += -150;
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

			if (CollisionIntersection_RectRect(Sharpenertemp->boundingBox, Sharpenertemp->vel, Walltemp->GetWallBoundingBox(j), { 0,0 }))
			{
				WallCollision = true;
				Sharpenertemp->vel.y = 0.f;
				/*----------------------------------
					WALLS
				----------------------------------*/
				if (Walltemp->GetType(j) == WALL)
				{
					/*----------------------------------
						PUSHED FROM THE RIGHT
					----------------------------------*/
					if (Sharpenertemp->pos.x >= Walltemp->GetWallBoundingBox(j).min.x)
					{
						Sharpenertemp->pos.x = (Walltemp->GetWallBoundingBox(j).max.x + Scale / 3);
					}
					/*----------------------------------
						PUSHED FROM THE LEFT
					----------------------------------*/
					else if (Sharpenertemp->pos.x <= Walltemp->GetWallBoundingBox(j).max.x)
					{
						Sharpenertemp->pos.x = (Walltemp->GetWallBoundingBox(j).min.x - Scale / 3);
					}
				}
				/*----------------------------------
					PLATFORM
				----------------------------------*/
				else if (Walltemp->GetType(j) == PLATFORM)
				{
					if (Sharpenertemp->pos.y >= Walltemp->GetWallBoundingBox(j).max.y + 40 && Sharpenertemp->vel.y < 0)
					{
						Sharpenertemp->vel.y = 0.f;
						Sharpenertemp->pos.y = Walltemp->GetWallBoundingBox(j).max.y + 40;
					}
				}
			}
		}//End of Wall for loop

		Sharpenertemp->pos.y += Sharpenertemp->vel.y * g_dt;
		Sharpenertemp->pos.x += Sharpenertemp->vel.x * g_dt;

	}//End of Sharpener for loop
}

/******************************************************************************/
/*!
	Sharpener Draw
*/
/******************************************************************************/
void Sharpener::DrawSharpener()
{
	/*AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);*/
	for (int i = 0; i < SharpenerNum; i++)
	{
		Sharpener* Sharpenertemp = SharpenerArray + i;
		SharpenerAnim.Anim_Update(pSharpener, Sharpenertemp->Transform);
		/*AEGfxSetPosition(Sharpenertemp->pos.x, Sharpenertemp->pos.y);
		AEGfxTextureSet(pSharpener->texture, 0, 0);
		AEGfxSetTransform(Sharpenertemp->Transform.m);
		AEGfxMeshDraw(pSharpener->pMesh, AE_GFX_MDM_TRIANGLES);*/
	}
}

/******************************************************************************/
/*!
	Sharpener Free
*/
/******************************************************************************/
void Sharpener::FreeSharpener()
{

}

/******************************************************************************/
/*!
	Sharpener Unload
*/
/******************************************************************************/
void Sharpener::UnloadSharpener() {

		/*AEGfxMeshFree(pSharpener->pMesh);
		AEGfxTextureUnload(pSharpener->texture);*/
	SharpenerAnim.Anim_Unload(pSharpener);
		SharpenerNum = 0;
}

/******************************************************************************/
/*!
	Sharpener Gravity
*/
/******************************************************************************/
void Sharpener::SetGravity()
{
	for (int i = 0; i < SharpenerNum; i++)
	{
		Sharpener* Sharpenertemp = SharpenerArray + i;
		Sharpenertemp->vel.y -= 450.f * g_dt;
	}
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

		Sharpenertemp->boundingBox.min.x = Sharpenertemp->pos.x - Scale / 2;
		Sharpenertemp->boundingBox.min.y = Sharpenertemp->pos.y - Scale / 2;
		Sharpenertemp->boundingBox.max.x = Sharpenertemp->pos.x + Scale / 2;
		Sharpenertemp->boundingBox.max.y = Sharpenertemp->pos.y + Scale / 2;
	}

}
/******************************************************************************/
/*!
	Sharpener Getter & Setter Functions
*/
/******************************************************************************/
AABB Sharpener::GetSharpenerBoundingBox(int i)	//Allow other files to use sharpener boundingbox without changing it.
{
	Sharpener* Sharpenertemp = SharpenerArray + i;
	return Sharpenertemp->boundingBox;
}
AEVec2 Sharpener::GetSharpenerVelocity(int i)	//Allow other files to use sharpener velocity without changing it.
{
	Sharpener* Sharpenertemp = SharpenerArray + i;
	return Sharpenertemp->vel;
}
AEVec2 Sharpener::GetSharpenerPosition(int i)	//Allow other files to use sharpener position without changing it.
{
	Sharpener* Sharpenertemp = SharpenerArray + i;
	return Sharpenertemp->pos;
}
void Sharpener::SetSharpenerPosition(int i, AEVec2 NewPos)	//Allow other files to set the sharpener position. [This is used for level design]
{
	Sharpener* Sharpenertemp = SharpenerArray + i;
	Sharpenertemp->pos = NewPos;
}

/******************************************************************************/
/*!
	Sharpener External Functions
*/
/******************************************************************************/
int GetSharpenerNum()	//Allow other files to run through a loop of all the sharpener. [E.g. to detect collision of all sharpener]
{
	return SharpenerNum;
}
void SetSharpenerNum(int Num)	//Set the number of sharpener object to be created. [This is used for level design]
{
	SharpenerNum = Num;
}

