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
	void InitPlayer();
	void Player_Collision();
	void BoundingBoxPlayer();
	void UpdatePlayer();
	void ExitPlayer();

	AABB BoundingBox;
	unsigned long flag;
	AEVec2 Velocity;

private:
	AEVec2 Position;
	GameObj* pPlayer;
	
};


