#pragma once

#include "Main.h"
#include "AEVec2.h"
#include "AEInput.h"
#include "Math.h"


class Player
{
private:
	GameObj* pPlayer;
	unsigned long flag;
	AABB boundingBox;
	AEVec2 pos;
	AEVec2 vel;
	bool CanJump = false;

public:
	void Player_Character();
	void Player_Draw();
	void Player_Init();
	void Player_Update();
	//void Player_Exit();
	void SetGravity();
	void BoundingBoxPlayer();
};


