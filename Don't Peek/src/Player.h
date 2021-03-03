#pragma once

#pragma once

#include "Main.h"
#include "AEVec2.h"
#include "AEInput.h"



enum MOVEMENT
{
	Movement_Jump = AEVK_UP,
	Movement_Down = AEVK_DOWN,
	Movement_Left = AEVK_LEFT,
	Movement_Right = AEVK_RIGHT,
	Movement_Slide = AEVK_LSHIFT
};

enum DIRECTIONS
{
	JUMP = 4,
	LEFT = -1,
	RIGHT = 1,
	DOWN = 1,
	NOACTION = 0
};





class Player
{
public:
	void Player_Character();
	//void Player_Input();
	//void Player_Movement();
	void Player_Draw();
	void Player_Init();
	void Player_Update();
	void Player_Exit();
private:
	AEVec2 Position;
	AEVec2 Velocity;
	//bool checker
	bool isPlayerMoveLeftRight, isPlayerJump, isPlayerGround, isPlayerWin, isPlayerAlive, isPlayerCreated;



};


