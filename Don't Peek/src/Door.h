/* Start Header ************************************************************************/
/*!
\file Door.h
\team name Don't Peek
\software name I Don't Wanna Do My Homework
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
	AABB boundingBox;
	AEVec2 vel;

public:

	void LoadDoor();
	void InitDoor();
	void UpdateDoor();
	void DrawDoor();
	void FreeDoor();
	void UnloadDoor();

	void BoundingBox();

	AABB GetDoorBoundingBox(int i);
	AEVec2 GetDoorVelocity(int i);
	AEVec2 GetDoorPosition(int i);
	void SetDoorPosition(int i, AEVec2 NewPos);
	
};
extern Door DoorArray[MAX];

	int GetDoorNum();
	void SetDoorNum(int Num);

	extern Door door;