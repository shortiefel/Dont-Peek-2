#pragma once
/* Start Header ************************************************************************/
/*!
\file Tutorial.h
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
#include "Main.h"
#include "GameState_DontPeek.h"
#include "Wall.h"

struct background
{
	AEVec2 Bgpos;
	AEVec2 Bgscale;
	AEMtx33	transform;	// object transformation matrix
	GameObj* pBg;
};
extern background bg;
void Tutorial_Load();
void Tutorial_Init();
void Tutorial_Update();
void Tutorial_Draw();
void Tutorial_Free();
void Tutorial_Unload();
//void CreateWall(AEVec2 pos, AEVec2 dir, int number, float scale);