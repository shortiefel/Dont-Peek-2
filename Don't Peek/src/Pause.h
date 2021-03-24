/* Start Header ************************************************************************/
/*!
\file Pause.cpp
\team name Don't Peak
\software name I don't want to do homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu
\date 24/03/2021
\brief This is the player file. It contains all the player function
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/
#pragma once

#include "Main.h"
#include "GameState_DontPeek.h"

struct Pause
{
	AEVec2 pos;
	AEVec2 scale;
	AEMtx33 transform; //object transformation matrix
	GameObj* pObj;
};

struct ButtonP
{
	AEVec2 pos;
	AEVec2 scale;
	AEMtx33	transform;	// object transformation matrix
	GameObj* pButton;
	AABB boundingBox;
};


void PauseLoad();
void PauseInit();
void PauseUpdate();
void PauseDraw();
void PauseFree();
void PauseUnload();

void BoundingBoxPause();

