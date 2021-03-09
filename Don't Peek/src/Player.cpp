#include "GameState_DontPeek.h"
#include "Player.h"
#include "Sharpener.h"
#include "Door.h"
#include "Wall.h"



/******************************************************************************/
/*!
	Game Object
*/
/******************************************************************************/

const int Player_Gravity = 8;
bool Gravity = true;
float GROUND = 0.f;
bool Movement = false;
Player player;


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




void Player::Player_Init()
{
	player.flag = FLAG_ACTIVE;
	player.Scale = 100.0f;
	player.vel = { 0, 0 };
}

/******************************************************************************/
/*!
	Player Update
*/
/******************************************************************************/

void Player::Player_Update()
{
	BoundingBox();

	if (AEInputCheckCurr(AEVK_LEFT))
	{

		for (int i = 0; i < Get_NumWalls(); i++)
		{
			Wall* Walltemp = Get_WallArr() + i;
			if (CollisionIntersection_RectRect(player.boundingBox, player.vel, Walltemp->boundingBox, { 0,0 }))
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

	if (AEInputCheckTriggered(AEVK_UP) && CanJump == true)
	{
		//printf("jumping \n");
		CanJump = false;
		//Position.y += Velocity.y * 4;
		player.vel.y = 5.f;
		//printf("PosY: %f, %f\n", pos.x, pos.y);
	}


	if (player.pos.y < GROUND)
	{
		player.pos.y = GROUND;
		CanJump = true;
		player.vel.y = 0;
	}
	else {

		SetGravity();
	}

	player.pos.x += player.vel.x;
	player.pos.y += player.vel.y;


	for (int i = 0; i < GetSharpenerNum(); i++)
	{
		Sharpener* Sharpenertemp = SharpenerArray + i;
		if (CollisionIntersection_RectRect(player.boundingBox, player.vel, Sharpenertemp->GetSharpenerBoundingBox(i), Sharpenertemp->GetSharpenerVelocity(i)))
		{
			
		}
	}

	for (int i = 0; i < GetDoorNum(); i++)
	{
		Door* Doortemp = DoorArray + i;
		if (CollisionIntersection_RectRect(player.boundingBox, player.vel, Doortemp->GetDoorBoundingBox(i) , Doortemp->GetDoorVelocity(i)))
		{
			if (i % 2 == 0)
			{
				player.pos = Doortemp->GetDoorPosition(i + 1);
				player.pos.x += 50;
			}
			else
			{
				player.pos = Doortemp->GetDoorPosition(i - 1);
				player.pos.x += -50;
			}
			//printf("Collision True DOOR \n");
		}
	}

	for (int i = 0; i < Get_NumWalls(); i++)
	{
		Wall* Walltemp = Get_WallArr() + i;
		if (CollisionIntersection_RectRect(player.boundingBox, player.vel, Walltemp->boundingBox, { 0,0 }))
		{
			if (player.pos.x < -370)
			{
				player.pos.x = -370;
			}
		}
	}

}

void Player::Player_Draw()
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTransparency(1.0f);
	AEGfxSetPosition(player.pos.x, player.pos.y);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(pPlayer->texture, 0, 0);
	AEGfxSetTransform(player.Transform.m);
	AEGfxMeshDraw(pPlayer->pMesh, AE_GFX_MDM_TRIANGLES);
}

void Player::Player_Unload()
{
	AEGfxTextureUnload(pPlayer->texture);
}



/******************************************************************************/
/*!
	Player Bounding Box
*/
/******************************************************************************/
void Player::SetGravity()
{
	player.vel.y -= 0.15f;
}

void Player::BoundingBox()
{
	AEMtx33 Transform2, Size;
	AEMtx33Scale(&Size, player.Scale, player.Scale);
	AEMtx33Trans(&Transform2, player.pos.x, player.pos.y);
	AEMtx33Concat(&(player.Transform), &Transform2, &Size);

	player.boundingBox.min.x = player.pos.x - player.Scale / 6;
	player.boundingBox.min.y = player.pos.y - player.Scale / 2;
	player.boundingBox.max.x = player.pos.x + player.Scale / 6;
	player.boundingBox.max.y = player.pos.y + player.Scale / 2;
}

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

void Player::SetPosition(AEVec2 NewPos)
{
	player.pos = NewPos;
}
