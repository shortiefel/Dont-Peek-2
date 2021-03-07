#include "Player.h"
#include "GameState_DontPeek.h"



/******************************************************************************/
/*!
	Game Object 
*/
/******************************************************************************/



static GameObj* pObj;
static GameObjInst* player;
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
	
	pObj = sGameObjList + sGameObjNum++;
	pObj->type = TYPE_PLAYER;


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
	pObj->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pObj->pMesh, "fail to create object!!");

	pObj->texture = AEGfxTextureLoad("Resources/Player.png");
	AE_ASSERT_MESG(pObj->texture, "Failed to create texture1!!");

	
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

/******************************************************************************/
/*!
	Player Draw
*/
/******************************************************************************/

void Player::Player_Draw()
{
	// Drawing object 2 - (first) - No tint
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	// Set position for object 2
	AEGfxSetPosition(Position.x, Position.y);
	// No tint
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

	AEGfxTextureSet(pObj->texture, 0, 0);		// Same object, different texture

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(pObj->pMesh, AE_GFX_MDM_TRIANGLES);
	// Set Transparency
	AEGfxSetTransparency(1.0f);
}

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
	Player Init
*/
/******************************************************************************/

void Player::Player_Init()
{
	Velocity.x = SPEED;
	Velocity.y = SPEED;
	Position.x = 40.0f;
	Position.y = -50.f;


}


/******************************************************************************/
/*!
	Player Update
*/
/******************************************************************************/

void Player::Player_Update()
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
	
	
	




}

/******************************************************************************/
/*!
	Player Exit
*/
/******************************************************************************/
void Player::Player_Exit()
{
}