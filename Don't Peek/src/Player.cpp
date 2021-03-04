#include "Player.h"
#include "GameState_DontPeek.h"



/******************************************************************************/
/*!
	Game Object 
*/
/******************************************************************************/

 GameObj* pObj;
static GameObjInst* player;
const int Player_Gravity = 8;
bool Gravity = true;
float GROUND = 0.f;
bool CanJump = false;


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
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 0.0f);

	AEGfxTextureSet(pObj->texture, 0, 0);		// Same object, different texture

	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(pObj->pMesh, AE_GFX_MDM_TRIANGLES);
	// Set Transparency
	AEGfxSetTransparency(1.0f);
}


void Player::Player_Init()
{

	AEVec2Set(&Velocity, SPEED, SPEED);
	AEVec2Set(&Position, 40.f, -50.f);
	AEVec2 zero;
	AEVec2Zero(&zero);

	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInst* pInst = sGameObjInstList + i;

		// check if current instance is not used
		if (pInst->flag == 0)
		{
			// it is not used => use it to create the new instance
			pInst->pObject = sGameObjList + TYPE_HIGHLIGHTER;
			pInst->flag = FLAG_ACTIVE;
			pInst->scale = 1.0f;
			pInst->posCurr = Position;
			pInst->velCurr = Velocity;
			pInst->dirCurr = 0;
			printf("Player Slot %lu\n", i);
			break;
		}

	}
	
}


/*!
	Player Update
*/
/******************************************************************************/

void Player::Player_Update()
{

	if (AEInputCheckCurr(AEVK_LEFT))
	{
		//Position.x -= Velocity.x;
		Velocity.x = -SPEED;
	}
	else if (AEInputCheckCurr(AEVK_RIGHT))
	{
		Velocity.x = SPEED;
	}
	else
	{
		Velocity.x = 0.f;
	}
	if (AEInputCheckTriggered(AEVK_UP) && CanJump == true)
	{
		printf("jumping \n");
		CanJump = false;
		//Position.y += Velocity.y * 4;
		Velocity.y = 5.f;
		printf("PosY: %f, %f\n", Position.x, Position.y);
	}


	if (Position.y < GROUND)
	{
		Position.y = GROUND;
		CanJump = true;
		Velocity.y = 0;
	}
	else {

		SetGravity();
	}

	Position.x += Velocity.x;
	Position.y += Velocity.y;


}

void Player::SetGravity()
{
	//printf("you shit");
	//Position.y -= 2;
	//Velocity.y = sqrt((2 * Player_Gravity) * (Position.y - Position.x));
	Velocity.y -= 0.15f;

}
