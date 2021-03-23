/* Start Header ************************************************************************/
/*!
\file Highlighter.h
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


enum highlighterType
{
	VERTICAL,
	HORIZONTAL
};


class Highlighter
{
private:
	GameObj* pHighlighter;
	AEVec2 pos;
	unsigned long flag;
	float scaleX;
	float scaleY;
	float highlighterScaleX;
	float highlighterScaleY;
	AEMtx33	Transform;
	AEVec2 vel;
	AABB boundingBox;
	highlighterType Highlightertype;

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
	void SetHighlighter(int num, AEVec2 NewPos, float scaleX, float scaleY, highlighterType type);

};
extern Highlighter HighlighterArray[MAX];

int GetHighlighterNum();
void SetHighlighterNum(int Num);
