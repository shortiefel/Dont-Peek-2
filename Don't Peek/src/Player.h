#pragma once

#pragma once

#include "Main.h"
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
	void SetGravity();
	void Player_Draw();
<<<<<<< HEAD
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
	
=======
	void Player_Init();
	void Player_Update();
	void Player_Exit();
	void SetGravity();
>>>>>>> origin/DontTouch
};


