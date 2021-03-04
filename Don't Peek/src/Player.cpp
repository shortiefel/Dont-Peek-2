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
bool Gravity = TRUE;
float GROUND = 0.f;



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
	if (Position.y > GROUND)
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

	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(pObj->pMesh, AE_GFX_MDM_TRIANGLES);
	// Set Transparency
	AEGfxSetTransparency(1.0f);
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
	if (AEInputCheckTriggered(AEVK_UP))
	{
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