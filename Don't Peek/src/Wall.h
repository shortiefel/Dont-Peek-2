#pragma once
/* Start Header ************************************************************************/
/*!
\file Wall.h
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

class Wall
{
private:
	AEVec2 Wallpos;
	AEVec2 Walldir;
	float Wallscale;
	AEMtx33	transform;	// object transformation matrix
	AABB boundingBox;
	GameObj* pWall;
	//AEGfxVertexList* wMesh;
public:

	void LoadWall();
	void InitWall();
	void UpdateWall();
	void DrawWall();
	void FreeWall();
	void UnloadWall();
	friend void CreateWall(AEVec2 pos, AEVec2 dir, int number, Wall* const WallArr, float scale);
};

//void CreateWall(AEVec2 pos, float dir, int number, Wall* const WallArr, float scale);