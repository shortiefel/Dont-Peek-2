/* Start Header ************************************************************************/
/*!
\file Door.h
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
#pragma once
#include "Main.h"
#include "GameState_DontPeek.h"
class Door
{
private:

	GameObj* pDoor;
	AEVec2 pos;
	unsigned long flag;
	float Scale;
	AEMtx33	Transform;
	//void BoundingBox();

public:
	AABB boundingBox;
	AEVec2 vel;

	void LoadDoor();
	void InitDoor();
	void UpdateDoor();
	void DrawDoor();
	void CreateWall(AEVec2 pos, int number, Door* const DoorArr);
	void BoundingBox();
};

extern Door DoorArray[2];