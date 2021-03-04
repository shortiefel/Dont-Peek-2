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

class Highlighter
{
private:
	//const float	SPEED = 100.0f;
	AEVec2 SPEED;
	AEVec2 Position;

public:
	void loadHighlighter();
	void drawHighlighter();
	void initHighlighter();
	void updateHighlighter();
	void unloadHighlighter();

};