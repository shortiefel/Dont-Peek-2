/* Start Header ************************************************************************/
/*!
\file Win.h
\team name Don't Peak
\software name I don't want to do homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief 
In this file, it contains the declaration of 
functions found in win.cpp 


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/
#pragma once

#include "Main.h"
#include "GameState_DontPeek.h"

//Win screen background variables
struct Win
{
	AEVec2 pos;
	AEVec2 scale;
	AEMtx33 transform; //object transformation matrix
	GameObj* pObj;
};

//Button variables
struct ButtonW
{
	AEVec2 pos;
	AEVec2 scale;
	AEMtx33	transform;	// object transformation matrix
	GameObj* pButton;
	AABB boundingBox;
};

void WinLoad();
void WinInit();
void WinUpdate();
void WinDraw();
void WinFree();
void WinUnload();

void BoundingBoxWin();
