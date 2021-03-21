/* Start Header ************************************************************************/
/*!
\file Menu.h
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
enum BUTTON
{
	// list of button types
	TYPE_PLAY = 10,

	TYPE_LEVEL,
	TYPE_OPTIONS,
	TYPE_RESTART,
	TYPE_RESUME,
	TYPE_CREDITS
};
struct Menu
{
	AEVec2 pos;
	AEVec2 scale;
	AEMtx33	transform;	// object transformation matrix
	GameObj* pObj;
	//AEVec2 cursorPos;
};

struct Button
{
	AEVec2 pos;
	AEVec2 scale;
	AEMtx33	transform;	// object transformation matrix
	GameObj* pButton;
	AABB boundingBox;
};

void MenuLoad();
void MenuInit();
void MenuUpdate();
void MenuDraw();
void MenuFree();
void MenuUnload();

void BoundingBox();