/* Start Header ************************************************************************/
/*!
\file Sharpener.cpp
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

#include "Sharpener.h"

const float	SPEED = 50.0f;
AEVec2 sharpenerPos;
AEVec2 velocity;

void sharpener::loadSharpener() {

	AEGfxTexture* image;
	image = AEGfxTextureLoad("Sharpener_Animation.png");

	AEGfxVertexList* sharpener = 0;
	AEGfxMeshStart();

	//rectangle sharpener (?)
	AEGfxTriAdd(
		-30.0f, -30.0f, 0x00000000, 0.0f, 0.0f,
		45.0f, -30.0f, 0x00000000, 0.0f, 0.0f,
		-30.0f, 30.0f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		45.0f, -30.0f, 0x00000000, 0.0f, 0.0f,
		45.0f, 30.0f, 0x00000000, 0.0f, 0.0f,
		-30.0f, 30.0f, 0x00000000, 0.0f, 0.0f);

	sharpener = AEGfxMeshEnd();
}

void sharpener::initSharpener() {

	sharpenerPos.x = 1.0f * AEGetWindowWidth() / 2;
	sharpenerPos.y = 1.0f * AEGetWindowHeight() / 2;
	velocity.x = SPEED;
}

void sharpener::updateSharpener() {

	if (AEInputCheckCurr(AEVK_UP))
	{
		//?????
	}

	if ((AEInputCheckCurr(AEVK_LSHIFT) || AEInputCheckCurr(AEVK_RSHIFT)) &&
		AEInputCheckCurr(AEVK_LEFT)) //[]o player pushing left
	{
		sharpenerPos.x -= velocity.x;
	}

	if ((AEInputCheckCurr(AEVK_LSHIFT) || AEInputCheckCurr(AEVK_RSHIFT)) &&
		AEInputCheckCurr(AEVK_RIGHT)) //o[] player pushing right
	{
		sharpenerPos.x += velocity.x;
	}

}

void sharpener::unloadSharpener() {

	AEGfxTextureUnload(image);
}