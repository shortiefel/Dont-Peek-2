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
<<<<<<< HEAD

=======
#include "AEVec2.h"
>>>>>>> origin/Highlighter

class Sharpener
{
private:
<<<<<<< HEAD
	GameObj* pSharpener;
	AEVec2 pos;
=======
	//const float	SPEED = 10.0f;
	AEVec2 SPEED; 
	AEVec2 Position;
	AEVec2 Velocity;
>>>>>>> origin/Highlighter

public:
	void loadSharpener();
	void drawSharpener();
	void initSharpener();
	void updateSharpener();
	void unloadSharpener();
<<<<<<< HEAD
	void BoundingBox();


	AABB boundingBox;
	unsigned long flag;
	AEVec2 vel;



};

extern Sharpener SharpenerArray[1];

=======
};
>>>>>>> origin/Highlighter
