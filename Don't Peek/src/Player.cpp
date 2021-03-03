#include "Player.h"
#include "GameState_DontPeek.h"



/******************************************************************************/
/*!
	Game Object 
*/
/******************************************************************************/



GameObj* pObj2;
static GameObjInst* player;

void Player::Player_Character() //drawing of character
{
	
	pObj2 = sGameObjList + sGameObjNum++;
	pObj2->type = TYPE_PLAYER;


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
	pObj2->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pObj2->pMesh, "fail to create object!!");

	pObj2->texture = AEGfxTextureLoad("Resources/Player.png");
	AE_ASSERT_MESG(pObj2->texture, "Failed to create texture1!!");

	
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


void Player::Player_Draw()
{
	// Drawing object 2 - (first) - No tint
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	// Set position for object 2
	AEGfxSetPosition(Position.x, Position.y);
	// No tint
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

	AEGfxTextureSet(pObj2->texture, 0, 0);		// Same object, different texture

	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(pObj2->pMesh, AE_GFX_MDM_TRIANGLES);
	// Set Transparency
	AEGfxSetTransparency(1.0f);
}


void Player::Player_Init()
{
	Velocity.x = SPEED;
	Position.x = 40.0f;
	Position.y = -50.f;
	
	
}

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


}

void Player::Player_Exit()
{
}