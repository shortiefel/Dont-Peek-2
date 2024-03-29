/* Start Header ************************************************************************/
/*!
\file Highlighter.h
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
functions found in Highlighter.cpp


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#include "Main.h"
#include "AEVec2.h"
#include "AEInput.h"

class Highlighter
{
private:
	GameObj* pHighlighter;
	AEVec2 pos;
	unsigned long flag;
	float scaleX;
	float scaleY;
	AEMtx33	Transform;
	AEVec2 vel;
	AABB boundingBox;

public:
	void LoadHighlighter();
	void InitHighlighter();
	void UpdateHighlighter();
	void DrawHighlighter();
	void FreeHighlighter();
	void UnloadHighlighter();

	void BoundingBox();

	AABB GetHighlighterBoundingBox(int i);
	AEVec2 GetHighlighterVelocity(int i);
	AEVec2 GetHighlighterPosition(int i);
	void SetHighlighterPosition(int i, AEVec2 NewPos);

};
extern Highlighter HighlighterArray[MAX];

int GetHighlighterNum();
void SetHighlighterNum(int Num);

extern Highlighter highlighter;