#include "Player.h"
#include "GameState_DontPeek.h"



/******************************************************************************/
/*!
	Game Object 
*/
/******************************************************************************/

GameObj* pObj2;

void Player::Player_Character() //drawing of character
{
	memset(sGameObjList, 0, sizeof(GameObj) * GAME_OBJ_INST_NUM_MAX);
	//no game object at this point
	sGameObjNum = 0;
	pObj2 = sGameObjList + sGameObjNum++;
	pObj2->type = TYPE_PLAYER;
	pObj2->texture = AEGfxTextureLoad("Player.png");


	//Drawing of Player
	AEGfxMeshStart();
	AEGfxTriAdd(
		-30.0f, -30.0f, 0x00000000, 0.0f, 0.0f,
		45.0f, -30.0f, 0x00000000, 0.0f, 0.0f,
		-30.0f, 30.0f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		45.0f, -30.0f, 0x00000000, 0.0f, 0.0f,
		45.0f, 30.0f, 0x00000000, 0.0f, 0.0f,
		-30.0f, 30.0f, 0x00000000, 0.0f, 0.0f);

	pObj2->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pObj2->pMesh, "fail to create object!!");

	
}

void Player::Player_Movement()
{
	if (Movement_Down)
	{
		Velocity.x = 0;
		Velocity.y = 1;
	}
	else if (Movement_Jump)
	{
		Velocity.x = 0;
		Velocity.y = -1;
	}
	else if (Movement_Left)
	{
		Velocity.x = -1;
		Velocity.y = 0;
	}
	else if (Movement_Right)
	{
		Velocity.x = 1;
		Velocity.y = 0;
	}
	else if (Movement_Slide && Movement_Right)
	{
		//call for shaperner
	}
	else if (Movement_Slide & Movement_Left)
	{
		//call for sharpner
	}

}

void Player::Player_Collision()
{

}

void Player::Player_Init()
{
	Player_Character();
	//setting player position, velocity
	Position.x = 100;
	Position.y = 100;
	Velocity.x = 0;
	Velocity.y = 0;
}

void Player::Player_Update()
{
}

void Player::Player_Exit()
{
}