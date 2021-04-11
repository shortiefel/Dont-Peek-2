
/* Start Header ************************************************************************/
/*!
\file Sharpener.h
\team name Don't Peek
\software name I Don't Wanna Do My Homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief 
In this file, it contains the declaration of
functions found in Sharpener.cpp


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#include "Main.h"

class Sharpener
{
private:
	GameObj* pSharpener;
	AEVec2 pos;
	unsigned long flag;
	float Scale;
	AEMtx33	Transform;
	AEVec2 vel;
	AABB boundingBox;
	bool WallCollision = false;

public:
	void LoadSharpener();
	void InitSharpener();
	void UpdateSharpener();
	void DrawSharpener();
	void FreeSharpener();
	void UnloadSharpener();

	void BoundingBox();
	void SetGravity();

	AABB GetSharpenerBoundingBox(int i);
	AEVec2 GetSharpenerVelocity(int i);
	AEVec2 GetSharpenerPosition(int i);
	void SetSharpenerPosition(int i, AEVec2 NewPos);
};

extern Sharpener SharpenerArray[MAX];


int GetSharpenerNum();
void SetSharpenerNum(int Num);

extern Sharpener sharpener;