#pragma once

#pragma once

#include "Main.h"
#include "AEVec2.h"
#include "AEInput.h"
#include "Math.h"


class Player
{
public:
	void Player_Character();
	void SetGravity();
	void Player_Draw();
	void Player_Init();
	void Player_Velocity();
	void Player_Update();
	void Player_Exit();

private:
	AEVec2 Position;
	AEVec2 Velocity;
};


