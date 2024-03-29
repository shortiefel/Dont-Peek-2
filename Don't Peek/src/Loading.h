/* Start Header ************************************************************************/
/*!
\file loading.h
\team name Don't Peek
\software name I don't want to do homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu
\date 22/01/2021
\brief This file contains a struct with functions that is needed to loading
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/
#pragma once
#include "Main.h"
#include "GameState_DontPeek.h"

struct Loading
{
	AEVec2 pos;
	AEVec2 scale;
	AEMtx33	transform;	// object transformation matrix
	GameObj* pObj;
};