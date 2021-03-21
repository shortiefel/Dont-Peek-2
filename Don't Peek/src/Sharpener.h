
/* Start Header ************************************************************************/
/*!
\file Sharpener.h
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
	void UnloadSharpener();

	void BoundingBox();

	AABB GetSharpenerBoundingBox(int i);
	AEVec2 GetSharpenerVelocity(int i);
	AEVec2 GetSharpenerPosition(int i);
	void SetSharpenerPosition(int i, AEVec2 NewPos);
	
};
extern Sharpener SharpenerArray[MAX];


int GetSharpenerNum();
void SetSharpenerNum(int Num);

extern Sharpener sharpener;