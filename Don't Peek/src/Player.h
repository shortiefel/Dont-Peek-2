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

//create instance 


class Player
{
public:
	void Player_Character();
	void Player_Movement();
	void Player_Collision();
	void Player_Init();
	void Player_Update();
	void Player_Exit();
private:
	AEVec2 Position;
	AEVec2 Velocity;



};


