/* Start Header ************************************************************************/
/*!
\file Pencil.h
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
#include "AEVec2.h"
#include "AEInput.h"

class Pencil
{
private:
	GameObj* pPencil;
	AEVec2 pos;
	unsigned long flag;
	float scaleX;
	float scaleY;
	AEMtx33	Transform;
	AEVec2 vel;
	AABB boundingBox;
	bool collisionFlag;

public:
	void LoadPencil();
	void InitPencil();
	void UpdatePencil();
	void DrawPencil();
	void FreePencil();
	void UnloadPencil();

	void BoundingBox();

	AABB GetPencilBoundingBox(int i);
	AEVec2 GetPencilVelocity(int i);
	AEVec2 GetPencilPosition(int i);
	void SetPencil(int i, AEVec2 NewPos, float scale_X, float scale_Y);

};
extern Pencil PencilArray[MAX];
extern Pencil pencil;

int GetPencilNum();
void SetPencilNum(int Num);

extern Pencil pencil;