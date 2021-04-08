/* Start Header ************************************************************************/
/*!
\file Pause.h
\team name Don't Peek
\software name I Don't Wanna Do My Homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief 
In this file,  it contains the declaration of 
functions found in Pause.cpp contains


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

