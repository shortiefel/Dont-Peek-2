
/* Start Header ************************************************************************/
/*!
\file Eraser.h
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
functions found in Eraser.cpp


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#include "Main.h"

class Eraser
{
private:
	GameObj* pEraser;
	AEVec2 pos;
	unsigned long flag;
	float Scale;
	AEMtx33	Transform;
	AEVec2 vel;
	AABB boundingBox;
	bool WallCollision = false;
	bool Left = false;

public:
	void LoadEraser();
	void InitEraser();
	void UpdateEraser();
	void DrawEraser();
	void FreeEraser();
	void UnloadEraser();

	void BoundingBox();
	void SetGravity();

	AABB GetEraserBoundingBox(int i);
	AEVec2 GetEraserVelocity(int i);
	AEVec2 GetEraserPosition(int i);
	void SetEraserPosition(int i, AEVec2 NewPos);

};
extern Eraser EraserArray[MAX];


int GetEraserNum();
void SetEraserNum(int Num);


extern Eraser eraser;