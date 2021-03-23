/* Start Header ************************************************************************/
/*!
\file Player.h
\team name Don't Peak
\software name I don't want to do homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief <give a brief description of this file>


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
	AEVec2 GetPosPlayer() const;
	bool GetCanJump();
};
extern Player player;