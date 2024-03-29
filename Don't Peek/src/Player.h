/* Start Header ************************************************************************/
/*!
\file Player.h
\team name Don't Peek
\software name I Don't Wanna Do My Homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief  
In this file, it contains the declaration of
functions found in Player.cpp


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

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
	bool SharpenerCollision = false;
	bool WallCollision = false;
	bool Left = false;
	float Scale;
	AEMtx33	Transform;

		//AEVec2 Position1;

public:
	void Player_Load();
	void Player_Init();
	void Player_Update();
	void Player_Draw();
	void Player_Free();
	void Player_Unload();
	
	void BoundingBox();
	void SetGravity();

	AABB GetBoundingBoxPlayer() const;
	AEVec2 GetVelPlayer() const;
	const Player* GetPlayerObj() const;
	AEVec2 GetPosPlayer() const;
	bool GetCanJump();
};


void SetWin(AEVec2 Pos);

extern Player player;