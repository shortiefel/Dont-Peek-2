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
/******************************************************************************/
/*!
	Level 1 Load
	/brief loads background for level
*/
/******************************************************************************/
void Level1_Load();
/******************************************************************************/
/*!
	Level 1 Init
	/brief inits all objects for level
*/
/******************************************************************************/
void Level1_Init();
/******************************************************************************/
/*!
	Level 1 Update
	/brief updates timer
*/
/******************************************************************************/
void Level1_Update();
/******************************************************************************/
/*!
	Level 1 Draw
	\brief draws background
*/
/******************************************************************************/
void Level1_Draw();
/******************************************************************************/
/*!
	Level 1 Free
	\brief frees level
*/
/******************************************************************************/
void Level1_Free();
/******************************************************************************/
/*!
	Level 1 Unload
	\ unloads textures
*/
/******************************************************************************/
void Level1_Unload();