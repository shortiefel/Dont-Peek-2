#include "GameState_DontPeek.h"
#include "Player.h"
#include "Sharpener.h"
#include "Door.h"



/******************************************************************************/
/*!
	Game Object 
*/
/******************************************************************************/

static GameObjInst* player;
const int Player_Gravity = 8;
bool Gravity = true;
float GROUND = 0.f;
<<<<<<< HEAD
bool CanJump = false;



/******************************************************************************/
/*!
	Player Character
*/
/******************************************************************************/
=======
>>>>>>> Player-IMSODONE


void Player::Player_Character() //drawing of character
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

<<<<<<< HEAD
void Player::SetGravity()
{
	//printf("you shit");
	Position.y -= 2;
		//Velocity.y = sqrt((2 * Player_Gravity) * (Position.y - Position.x));

}

//void Player::Player_Movement()
//{
//	if (isPlayerAlive == TRUE && isPlayerWin == FALSE)
//	{
//		player->velCurr.y += 3.0f * g_dt; //constant gravity for falling 
//		player->velCurr.x = player->velCurr.x * Speed * 1.25f * 100.0f;
//		player->velCurr.y = player->velCurr.y * Speed * 1.25f * 100.f;
//		Speed_Overall = (player->velCurr.x, player->velCurr.y);
//	}
//}

/******************************************************************************/
/*!
	Player Draw
*/
/******************************************************************************/

=======
>>>>>>> Player-IMSODONE
void Player::Player_Draw()
{
	
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(pos.x, pos.y);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(pPlayer->texture, 0, 0);
	AEGfxSetTransform(Transform.m);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(pPlayer->pMesh, AE_GFX_MDM_TRIANGLES);
	
}

/******************************************************************************/
/*!
	Player Init
*/
/******************************************************************************/

void Player::Player_Init()
{
<<<<<<< HEAD
	Velocity.x = SPEED;
	Velocity.y = SPEED;
	Position.x = 40.0f;
	Position.y = -50.f;


=======
	Scale = 100.0f;
	flag = FLAG_ACTIVE;
	AEVec2Set(&vel, SPEED, SPEED);
	AEVec2Set(&pos, 80.0f, -10.f);
	printf("Init Player \n");
>>>>>>> Player-IMSODONE
}

/******************************************************************************/
/*!
	Player Update
*/
/******************************************************************************/

void Player::Player_Update()
{
<<<<<<< HEAD
	
=======


>>>>>>> Player-IMSODONE
	if (AEInputCheckCurr(AEVK_LEFT))
	{
		//Position.x -= Velocity.x;
		vel.x = -SPEED;
	}
	else if (AEInputCheckCurr(AEVK_RIGHT))
	{
		vel.x = SPEED;
	}
	else
	{
		vel.x = 0.f;
	}

	if (AEInputCheckTriggered(AEVK_UP) && CanJump == true)
	{
		printf("jumping \n");
		CanJump = false;
		//Position.y += Velocity.y * 4;
		vel.y = 5.f;
		printf("PosY: %f, %f\n",pos.x, pos.y);
	}


	if (pos.y < GROUND)
	{
		pos.y = GROUND;
		CanJump = true;
		vel.y = 0;
	}
<<<<<<< HEAD
	if (AEInputCheckTriggered(AEVK_UP) && CanJump == true)
	{
		CanJump = false;
		Position.y += Velocity.y * 4;
		printf("PosY: %f, %f\n", Position.x, Position.y);
	}
	else
	{
		Position.x += 0.f;
		Position.y += 0.f;
	}
	SetGravity();
	if (Position.y < GROUND)
	{
		Position.y = GROUND;
		CanJump = true;
	}
	
	

=======
	else {

		SetGravity();
	}

	pos.x += vel.x;
	pos.y += vel.y;

	BoundingBoxPlayer();
	
	for (int i = 0; i < 1; i++)
	{
		Sharpener* Sharpenertemp = SharpenerArray + i;
		if (CollisionIntersection_RectRect(boundingBox, vel, Sharpenertemp->boundingBox, Sharpenertemp->vel))
		{
			printf("Collision Sharpener\n");
			printf("BB2 Door min x %f \n", Sharpenertemp->boundingBox.min.x);
			printf("BB2 Door min y %f \n", Sharpenertemp->boundingBox.min.y);
			printf("BB2 Door max x %f \n", Sharpenertemp->boundingBox.max.x);
			printf("BB2 Door max y %f \n", Sharpenertemp->boundingBox.max.y);

			printf("|| \n");
			printf("BBP min x %f \n", boundingBox.min.x);
			printf("BBP min y %f \n", boundingBox.min.y);
			printf("BBP max x %f \n", boundingBox.max.x);
			printf("BBP max y %f \n", boundingBox.max.y);
		}

	}

	

	for (int i = 0; i < 1; i++)
	{
		Door* Doortemp = DoorArray + i;
		if (CollisionIntersection_RectRect(boundingBox, vel, Doortemp->boundingBox, Doortemp->vel))
		{
			printf("Collision True----------------------------------------------- \n");
			printf("BB2 Door min x %f \n", Doortemp->boundingBox.min.x);
			printf("BB2 Door min y %f \n", Doortemp->boundingBox.min.y);
			printf("BB2 Door maX x %f \n", Doortemp->boundingBox.max.x);
			printf("BB2 Door max y %f \n", Doortemp->boundingBox.max.y);

			printf("|| \n");
			printf("BBP min x %f \n", boundingBox.min.x);
			printf("BBP min y %f \n", boundingBox.min.y);
			printf("BBP max x %f \n", boundingBox.max.x);
			printf("BBP max y %f \n", boundingBox.max.y);

		}
	}
	
>>>>>>> Player-IMSODONE

	

	
	
	

}

<<<<<<< HEAD
/******************************************************************************/
/*!
	Player Exit
*/
/******************************************************************************/
void Player::Player_Exit()
=======
void Player::SetGravity()
>>>>>>> Player-IMSODONE
{
	//printf("you shit");
	//Position.y -= 2;
	//Velocity.y = sqrt((2 * Player_Gravity) * (Position.y - Position.x));
	vel.y -= 0.15f;

}

/******************************************************************************/
/*!
	Player Bounding Box
*/
/******************************************************************************/

void Player::BoundingBoxPlayer()
{
	AEMtx33 Transform2, Size;
	AEMtx33Scale(&Size, Scale, Scale);
	AEMtx33Trans(&Transform2, pos.x, pos.y);
	AEMtx33Concat(&Transform, &Transform2, &Size);

	boundingBox.min.x = pos.x - Scale/2;
	boundingBox.min.y = pos.y - Scale/2;
	boundingBox.max.x = pos.x + Scale/2;
	boundingBox.max.y = pos.y + Scale/2;
}







