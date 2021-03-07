#include "GameState_DontPeek.h"
#include "Player.h"
#include "Sharpener.h"



/******************************************************************************/
/*!
	Game Object 
*/
/******************************************************************************/

static GameObjInst* player;
const int Player_Gravity = 8;
bool Gravity = true;
float GROUND = 0.f;

Sharpener sharpener2;

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

void Player::Player_Draw()
{
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(pos.x, pos.y);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(pPlayer->texture, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxMeshDraw(pPlayer->pMesh, AE_GFX_MDM_TRIANGLES);
	AEGfxSetTransparency(1.0f);
}


void Player::Player_Init()
{
	flag = FLAG_ACTIVE;
	AEVec2Set(&vel, SPEED, SPEED);
	AEVec2Set(&pos, 100.0f, -100.f);
	printf("Init Player \n");
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
	else {

		SetGravity();
	}

	pos.x += vel.x;
	pos.y +=vel.y;

	BoundingBoxPlayer();
	

	if (CollisionIntersection_RectRect(boundingBox, vel, sharpener2.boundingBox, sharpener2.vel))
	{
		
		printf("Collision True");
		printf("BB2 min x %f \n", sharpener2.boundingBox.min.x);
		printf("BB2 min y %f \n", sharpener2.boundingBox.min.y);
		printf("BB2 maX x %f \n", sharpener2.boundingBox.max.x);
		printf("BB2 max y %f \n", sharpener2.boundingBox.max.y);
		
	}

	
	
	

}

void Player::SetGravity()
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
	AEMtx33 Transform, Scale, Concat;
	AEMtx33Scale(&Scale, pos.x, pos.y);
	AEMtx33Trans(&Transform, pos.x, pos.y);
	AEMtx33Concat(&Concat, &Transform, &Scale);

	boundingBox.min.x = pos.x;
	boundingBox.min.y = pos.y;
	boundingBox.max.x = pos.x;
	boundingBox.max.y = pos.y;
}





