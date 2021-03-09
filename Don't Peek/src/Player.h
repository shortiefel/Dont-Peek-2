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
	float Scale;
	AEMtx33	Transform;

		//AEVec2 Position1;

public:
	void Player_Load();
	void Player_Init();
	void Player_Update();
	void Player_Draw();
	void Player_Unload();
	
	void BoundingBox();
	void SetGravity();
	

	AABB GetBoundingBoxPlayer() const;
	AEVec2 GetVelPlayer() const;
	const Player* GetPlayerObj() const;
	void SetPosition(AEVec2 NewPos);
};
extern Player player;