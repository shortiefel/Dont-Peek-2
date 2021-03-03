#include "Player.h"



/******************************************************************************/
/*!

*/
/******************************************************************************/

void Player::Player_Character() //drawing of character
{
	static GameObjInst* player;

	//setting player position, velocity
	Position.x = 100;
	Position.y = 100;
	Velocity.x = 0;
	Velocity.y = 0;

	//Drawing of Player
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, 0.5f, 0xbbbbbb, 0.0f, 0.0f,
		-0.5f, -0.5f, 0xbbbbbb, 0.0f, 0.0f,
		0.5f, -0.5f, 0xbbbbbb, 0.0f, 0.0f);

	AEGfxTriAdd(
		-0.5f, 0.5f, 0xbbbbbb, 0.0f, 0.0f,
		0.5f, 0.5f, 0xbbbbbb, 0.0f, 0.0f,
		0.5f, -0.5f, 0xbbbbbb, 0.0f, 0.0f);

	AEGfxTexture* Player_Image;
	Player_Image = AEGfxTextureLoad("Resource\Player.png");
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
}

void Player::Player_Update()
{
}

void Player::Player_Exit()
{
}