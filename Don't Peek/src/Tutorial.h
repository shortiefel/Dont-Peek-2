#pragma once
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
/******************************************************************************/
/*!
	Tutorial Load
	/brief loads background for level
*/
/******************************************************************************/
void Tutorial_Load();
/******************************************************************************/
/*!
	Tutorial Init
	/brief inits all objects for level
*/
/******************************************************************************/
void Tutorial_Init();
/******************************************************************************/
/*!
	Tutorial Update
	/brief updates timer
*/
/******************************************************************************/
void Tutorial_Update();
/******************************************************************************/
/*!
	Tutorial Draw
	\brief draws background
*/
/******************************************************************************/
void Tutorial_Draw();
/******************************************************************************/
/*!
	Tutorial Free
	\brief free background
*/
/******************************************************************************/
void Tutorial_Free();
/******************************************************************************/
/*!
	Tutorial Unload
	\brief unload background
*/
/******************************************************************************/
void Tutorial_Unload();
//void CreateWall(AEVec2 pos, AEVec2 dir, int number, float scale);