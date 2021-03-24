/* Start Header ************************************************************************/
/*!
\file Level 1.h
\team name Don't Peak
\software name I don't want to do homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief <give a brief description of this file>


Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/
#pragma once
#include "Main.h"
#include "GameState_DontPeek.h"
#include "Wall.h"
#include "Tutorial.h"
/*
struct background
{
	AEVec2 Bgpos;
	AEVec2 Bgscale;
	AEMtx33	transform;	// object transformation matrix
	GameObj* pBg;
};*/

void Level1_Load();
void Level1_Init();
void Level1_Update();
void Level1_Draw();
void Level1_Free();
void Level1_Unload();