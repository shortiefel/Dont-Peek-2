#include "GameState_DontPeek.h"
#include "Player.h"
#include "Sharpener.h"
#include "Collision.h"



/******************************************************************************/
/*!
	Game Objects
*/
/******************************************************************************/

const int Player_Gravity = 8;
bool Gravity = true;
float GROUND = 0.f;
bool CanJump = false;



/******************************************************************************/
/*!
	Player Character
*/
/******************************************************************************/


void Player::Player_Character() //drawing of character
{
	pPlayer = sGameObjList + sGameObjNum++;
	pPlayer->type = TYPE_PLAYER;

	pPlayer->texture = AEGfxTextureLoad("Resources/Player.png");
	AE_ASSERT_MESG(pPlayer->texture, "Failed to load Player!");


	//Drawing of Player
	AEGfxMeshStart();
	AEGfxTriAdd(
		-60.0f, -60.0f, 0x00000000, 0.0f, 1.0f,
		100.0f, -60.0f, 0x00000000, 1.0f, 1.0f,
		-60.0f, 60.0f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		100.0f, -60.0f, 0x00000000, 1.0f, 1.0f,
		100.0f, 60.0f, 0x00000000, 1.0f, 0.0f,
		-60.0f, 60.0f, 0x00000000, 0.0f, 0.0f);
	pPlayer->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pPlayer->pMesh, "fail to create object!!");

}

/******************************************************************************/
/*!
	Player Draw
*/
/******************************************************************************/

void Player::Player_Draw()
{
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(Position.x, Position.y);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(pPlayer->texture, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxMeshDraw(pPlayer->pMesh, AE_GFX_MDM_TRIANGLES);
	AEGfxSetTransparency(1.0f);
}

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



void Player::Player_Collision()
{
	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		//decalre new instance 
		GameObjInst* pInst_1 = sGameObjInstList + i;

		//if object is instance and not active,skip
		if ((pInst_1->flag & FLAG_ACTIVE) == 0)
			continue;

		//if object is sharpner
		if ((pInst_1->pObject->type == TYPE_SHARPENER))
		{
			//setting object instance
			for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
			{
				//declaring variable
				GameObjInst* pInst_2 = sGameObjInstList + i;

				//if object is instance and not active or is sharpner, skip
				if (((pInst_2->flag && FLAG_ACTIVE) == 0) || pInst_2->pObject->type == TYPE_SHARPENER)
					continue;

				if (pInst_2->pObject->type == TYPE_PLAYER)
				{
					if (CollisionIntersection_RectRect(pInst_1->boundingBox, pInst_1->velCurr, pInst_2->boundingBox, pInst_2->velCurr))
					{
						//i not sure?
					}
				}

				else if (pInst_2->pObject->type == TYPE_SHARPENER)
				{
					if (CollisionIntersection_RectRect(pInst_1->boundingBox, pInst_1->velCurr, pInst_2->boundingBox, pInst_2->velCurr))
					{
						//i not sure?
					}
				}

				else if (pInst_2->pObject->type == TYPE_HIGHLIGHTER)
				{
					if (CollisionIntersection_RectRect(pInst_1->boundingBox, pInst_1->velCurr, pInst_2->boundingBox, pInst_2->velCurr))
					{
						//i not sure?
					}
				}

				else if (pInst_2->pObject->type == TYPE_DOOR)
				{
					if (CollisionIntersection_RectRect(pInst_1->boundingBox, pInst_1->velCurr, pInst_2->boundingBox, pInst_2->velCurr))
					{
						//i not sure?
					}
				}


			}
		}
	}
}

/******************************************************************************/
/*!
	Player Bounding Box
*/
/******************************************************************************/

void Player::BoundingBoxPlayer()
{
	AEMtx33 Transform, Scale, Concat;
	AEMtx33Scale(&Scale, Position.x, Position.y);
	AEMtx33Trans(&Transform, Position.x, Position.y);
	AEMtx33Concat(&Concat, &Transform, &Scale);

	BoundingBox.min.x = Position.x;
	BoundingBox.min.y = Position.y;
	BoundingBox.max.x = Position.x;
	BoundingBox.max.y = Position.y;
}


/******************************************************************************/
/*!
	Player Init
*/
/******************************************************************************/

void Player::InitPlayer()
{
	flag = FLAG_ACTIVE;
	AEVec2Set(&Velocity, SPEED, SPEED);
	AEVec2Set(&Position, 40.0f, -50.0f);
}


/******************************************************************************/
/*!
	Player Update
*/
/******************************************************************************/

void Player::UpdatePlayer()
{
	
	if (AEInputCheckCurr(AEVK_LEFT))
	{
		Position.x -= Velocity.x;
	}
	if (AEInputCheckCurr(AEVK_RIGHT))
	{
		Position.x += Velocity.x;
	}
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

	BoundingBoxPlayer();
}

/******************************************************************************/
/*!
	Player Exit
*/
/******************************************************************************/
void Player::ExitPlayer()
{
}