/* Start Header ************************************************************************/
/*!
\file Restart.h
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

struct Restart
{
	AEVec2 pos;
	AEVec2 scale;
	AEMtx33 transform; //object transformation matrix
	GameObj* pObj;
};

void RestartLoad();
void RestartInit();
void RestartUpdate();
void RestartDraw();
void RestartFree();
void RestartUnload();
