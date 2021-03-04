#pragma once

#pragma once

#include "Main.h"
#include "AEVec2.h"
#include "AEInput.h"


class Player
{
public:
	void Player_Character();
	void Player_Draw();
	void Player_Init();
	void Player_Update();
	void Player_Exit();
	void SetGravity();
private:
	AEVec2 Position;
	AEVec2 Velocity;
};


