
#pragma once
#include "Main.h"
#include "GameState_DontPeek.h"

struct Lose
{
	AEVec2 pos;
	AEVec2 scale;
	AEMtx33 transform; //object transformation matrix
	GameObj* pObj;
};

struct ButtonL
{
	AEVec2 pos;
	AEVec2 scale;
	AEMtx33	transform;	// object transformation matrix
	GameObj* pButton;
	AABB boundingBox;
};

void LoseLoad();
void LoseInit();
void LoseUpdate();
void LoseDraw();
void LoseFree();
void LoseUnload();

void BoundingBoxLose();
