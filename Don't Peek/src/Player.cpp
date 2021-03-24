/* Start Header ************************************************************************/
/*!
\file Player.cpp
\team name Don't Peak
\software name I don't want to do homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu
\date 22/01/2021
\brief This is the player file. It contains all the player function
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/
#include "GameState_DontPeek.h"
#include "Player.h"
#include "Sharpener.h"
#include "Eraser.h"
#include "Pencil.h"
#include "Door.h"
#include "Wall.h"
#include "GameStateMgr.h"
#include "Menu.h"
#include <math.h>


/******************************************************************************/
/*!
	Game Object
*/
/******************************************************************************/

const int Player_Gravity = 8;
bool Gravity = true;
float GROUND = 0.f;
bool Movement = false;
float CameraPosX = 0;
float CameraPosY = 0;
AEVec2 WinPos;
Wall* wall_player;

/******************************************************************************/
/*!
	Player Load
*/
/******************************************************************************/
void Player::Player_Load() //drawing of character
{

	pPlayer = sGameObjList + sGameObjNum++;
	pPlayer->type = TYPE_PLAYER;

	pPlayer->texture = AEGfxTextureLoad("Resources/Player.png");
	AE_ASSERT_MESG(pPlayer->texture, "Failed to load Player!");


	//Drawing of Player
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	pPlayer->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pPlayer->pMesh, "fail to create object!!");
}

/******************************************************************************/
/*!
	Player Init
*/
/******************************************************************************/
void Player::Player_Init()
{
	Scale = 130.0f;
	flag = FLAG_ACTIVE;
	AEVec2Set(&(player.vel), 0, 0);
	AEVec2Set(&(player.pos), -100.0f, 30.f);
}

/******************************************************************************/
/*!
	Player Update
*/
/******************************************************************************/
void Player::Player_Update()
{
	//FAKE GROUND
	GROUND = -1000; //For Player To Fall
	/******************************************************************************/
	/*!
		INPUTS
	*/
	/******************************************************************************/
	if (AEInputCheckCurr(AEVK_LEFT))
	{
		for (int i = 0; i < Get_NumWalls(); i++)
		{
			Wall* Walltemp = Get_WallArr() + i;
			if (CollisionIntersection_RectRect(player.boundingBox, player.vel, Walltemp->GetWallBoundingBox(i), { 0,0 }))
			{
				player.vel.x = 0.f;

			}
			else
				player.vel.x = -SPEED;
		}

	}
	else if (AEInputCheckCurr(AEVK_RIGHT))
	{
		
		player.vel.x = SPEED;
	}
	else
	{
		player.vel.x = 0.f;
	}

	if (AEInputCheckTriggered(AEVK_SPACE) && CanJump == true)
	{
		printf("jump \n");
		//printf("jumping \n");
		CanJump = false;
		//Position.y += Velocity.y * 4;
		float g = 65.f * g_dt;
		player.vel.y = static_cast<double>((2 * g) * (500 - 440));
		//printf("PosY: %f, %f\n", pos.x, pos.y);
	}
	else if (player.pos.y < GROUND)
	{
		printf("ground \n");
		player.pos.y = GROUND;
		CanJump = true;
		player.vel.y = 0;
	}
		SetGravity();


	if (AEInputCheckCurr(AEVK_B))
		gGameStateNext = GS_MENU;

	if (AEInputCheckCurr(AEVK_ESCAPE))
		gGameStateNext = GS_QUIT;

	BoundingBox();
	/******************************************************************************/
	/*!
		SHARPENERS
	*/
	/******************************************************************************/
	for (int i = 0; i < GetSharpenerNum(); i++)
	{
		Sharpener* Sharpenertemp = SharpenerArray + i;
		//BoundingBox();
		if (CollisionIntersection_RectRect(player.boundingBox, player.vel, Sharpenertemp->GetSharpenerBoundingBox(i), Sharpenertemp->GetSharpenerVelocity(i)))
		{
			if (player.pos.y >= Sharpenertemp->GetSharpenerBoundingBox(i).max.y + (Scale / 6) && player.vel.y < 0)
			{
				player.vel.y = 0;
				player.pos.y = Sharpenertemp->GetSharpenerBoundingBox(i).max.y + (Scale/6);
				CanJump = true;
			}
		}
		
	}//End of Sharpener for loop

	/******************************************************************************/
	/*!
		ERASERS
	*/
	/******************************************************************************/
	for (int i = 0; i < GetSharpenerNum(); i++)
	{
		Eraser* Erasertemp = EraserArray + i;
		if (CollisionIntersection_RectRect(player.boundingBox, player.vel, Erasertemp->GetEraserBoundingBox(i), Erasertemp->GetEraserVelocity(i)))
		{
			if (player.pos.y >= Erasertemp->GetEraserBoundingBox(i).max.y + (Scale / 6) && player.vel.y < 0)
			{
				player.vel.y = 0;
				player.pos.y = Erasertemp->GetEraserBoundingBox(i).max.y + (Scale / 6);
				CanJump = true;
			}
		}

	}//End of Sharpener for loop

	/******************************************************************************/
	/*!
		DOORS
	*/
	/******************************************************************************/
	for (int i = 0; i < GetDoorNum(); i++)
	{
		Door* Doortemp = DoorArray + i;
		if (CollisionIntersection_RectRect(player.boundingBox, player.vel, Doortemp->GetDoorBoundingBox(i), Doortemp->GetDoorVelocity(i)))
		{
			if (i % 2 == 0)
			{
				player.pos = Doortemp->GetDoorPosition(i + 1);
				player.pos.x += Scale / 2 + 30;
				if (i + 2 < GetDoorNum())
				{
					CameraPosX = (Doortemp->GetDoorPosition(i + 1).x + Doortemp->GetDoorPosition(i + 2).x) / 2;
					CameraPosY = (Doortemp->GetDoorPosition(i + 1).y + Doortemp->GetDoorPosition(i + 2).y) / 2;
				}
				else
				{
					CameraPosX = player.pos.x;
					CameraPosY = player.pos.y;
				}
				
			}
			else
			{
				player.pos = Doortemp->GetDoorPosition(i - 1);
				player.pos.x -= Scale / 2 + 30;
				if (i - 2 >= 0)
				{
					CameraPosX = (Doortemp->GetDoorPosition(i - 1).x + Doortemp->GetDoorPosition(i - 2).x) / 2;
					CameraPosY = (Doortemp->GetDoorPosition(i - 1).y + Doortemp->GetDoorPosition(i - 2).y) / 2;
				}
				else
				{
					CameraPosX = player.pos.x;
					CameraPosY = player.pos.y;
				}
			}
				AEGfxSetCamPosition(CameraPosX, CameraPosY);
		}

	}//End of Door for loop

	/******************************************************************************/
	/*!
		PENCIL
	*/
	/******************************************************************************/
	for (int i =0; i< GetPencilNum(); i++)
	{
		Pencil* Penciltemp = PencilArray + i;
		if (CollisionIntersection_RectRect(player.boundingBox, player.vel, Penciltemp->GetPencilBoundingBox(i), { 0,0 }))
		{
			if (player.pos.x >= Penciltemp->GetPencilBoundingBox(i).max.x)
			{
				player.pos.x = (Penciltemp->GetPencilBoundingBox(i).max.x + (Scale / 5));
			}
			else if (player.pos.x <= Penciltemp->GetPencilBoundingBox(i).min.x)
			{
				player.pos.x = (Penciltemp->GetPencilBoundingBox(i).min.x - (Scale / 5));
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
		BoundingBox();
		if (CollisionIntersection_RectRect(player.boundingBox, player.vel, Walltemp->GetWallBoundingBox(i), { 0,0 }))
		{	
			WallCollision = true;
			if (Walltemp->GetType(i) == WALL)
			{
				if (player.pos.x >= Walltemp->GetWallBoundingBox(i).min.x)
				{
					player.pos.x = (Walltemp->GetWallBoundingBox(i).max.x + Scale / 3 );
				}
				else if (player.pos.x <= Walltemp->GetWallBoundingBox(i).max.x)
				{
					player.pos.x = (Walltemp->GetWallBoundingBox(i).min.x - player.Scale / 3);
				}
			}
			else if (Walltemp->GetType(i) == PLATFORM)
			{

				if (player.pos.y >= Walltemp->GetWallBoundingBox(i).max.y + player.Scale/2 - 10 && player.vel.y < 0)
				{
					//GROUND = 
					player.vel.y = 0;
					player.pos.y = Walltemp->GetWallBoundingBox(i).max.y + player.Scale / 2 - 10;
					CanJump = true;
				}
			}
			else if (Walltemp->GetType(i) == CEILING)
			{
				if (player.pos.y < Walltemp->GetWallBoundingBox(i).max.y)
				{
					vel.y -= 50.f * g_dt;
					player.pos.y = Walltemp->GetWallBoundingBox(i).min.y - player.Scale / 2;
				}
				else if(player.pos.y >= Walltemp->GetWallBoundingBox(i).max.y + player.Scale / 2 - 10 && player.vel.y < 0)
				{
					player.vel.y = 0;
					player.pos.y = Walltemp->GetWallBoundingBox(i).max.y + player.Scale / 2 - 10;
					CanJump = true;
				}
			}
		}
	}//End of Wall for loop
	/******************************************************************************/
	/*!
		WIN CHECK
	*/
	/******************************************************************************/
	if (CollisionIntersection_PointRect(WinPos, {0,0}, player.boundingBox, player.vel))
	{
		gGameStateNext = GS_WIN;
	}

	player.pos.x += player.vel.x * g_dt;
	player.pos.y += player.vel.y * g_dt;

}

/******************************************************************************/
/*!
	Player Draw
*/
/******************************************************************************/
void Player::Player_Draw()
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(pos.x, pos.y);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(pPlayer->texture, 0, 0);
	AEGfxSetTransform(Transform.m);
	
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(pPlayer->pMesh, AE_GFX_MDM_TRIANGLES);

}

/******************************************************************************/
/*!
	Player Free
*/
/******************************************************************************/
void Player::Player_Free()
{
	AEGfxMeshFree(pPlayer->pMesh);
}

/******************************************************************************/
/*!
	Player Unload
*/
/******************************************************************************/
void Player::Player_Unload()
{
	AEGfxTextureUnload(pPlayer->texture);
}



/******************************************************************************/
/*!
	Player Gravity
*/
/******************************************************************************/
void Player::SetGravity()
{
	vel.y -= 65.f * g_dt;
}

/******************************************************************************/
/*!
	Player Bounding Box
*/
/******************************************************************************/
void Player::BoundingBox()
{
	AEMtx33 Transform2, Size;
	AEMtx33Scale(&Size, Scale, Scale);
	AEMtx33Trans(&Transform2, pos.x, pos.y);
	AEMtx33Concat(&(player.Transform), &Transform2, &Size);

	player.boundingBox.min.x = player.pos.x - Scale / 4;// 5;
	player.boundingBox.min.y = player.pos.y - Scale / 2;
	player.boundingBox.max.x = player.pos.x + Scale / 4;// 5;
	player.boundingBox.max.y = player.pos.y + Scale / 2;
}

/******************************************************************************/
/*!
	Player Getter & Setter Functions
*/
/******************************************************************************/
AABB Player::GetBoundingBoxPlayer() const
{
	return player.boundingBox;
}

AEVec2 Player::GetVelPlayer() const
{
	return player.vel;
}

const Player* Player::GetPlayerObj() const
{
	return this;
}

AEVec2 Player::GetPosPlayer() const
{
	return player.pos;
}

bool Player::GetCanJump()
{
	return true;
}

void SetWin(AEVec2 Pos)
{
	WinPos = Pos;
}
