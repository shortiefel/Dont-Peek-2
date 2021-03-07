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

public:
	void loadSharpener();
	void drawSharpener();
	void initSharpener();
	void updateSharpener();
	void unloadSharpener();
	void BoundingBox();


	AABB boundingBox;
	unsigned long flag;
	AEVec2 vel;



};

extern Sharpener SharpenerArray[1];

