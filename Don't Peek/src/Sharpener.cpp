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
#include "GameState_DontPeek.h"

//AEGfxTexture* sharpeners;
GameObj* sharpenerObj;

void Sharpener::loadSharpener() {

	//memset(sGameObjList, 0, sizeof(GameObj) * GAME_OBJ_NUM_MAX);
	//sGameObjNum = 0;

	sharpenerObj = sGameObjList + sGameObjNum++;
	sharpenerObj->type = TYPE_SHARPENER;
	sharpenerObj->texture = AEGfxTextureLoad("Resources/Sharpener_Animation.png");
	AE_ASSERT_MESG(sharpenerObj->texture, "Failed to load sharpener!!");

	//sharpeners = AEGfxTextureLoad("Sharpener_Animation.png");

	//AEGfxVertexList* sharpener = 0;
	AEGfxMeshStart();
	AEGfxTriAdd(
		-30.0f, -30.0f, 0x00000000, 0.0f, 1.0f,
		45.0f, -30.0f, 0x00000000, 1.0f, 1.0f,
		-30.0f, 30.0f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		45.0f, -30.0f, 0x00000000, 1.0f, 1.0f,
		45.0f, 30.0f, 0x00000000, 1.0f, 0.0f,
		-30.0f, 30.0f, 0x00000000, 0.0f, 0.0f);

	sharpenerObj->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(sharpenerObj->pMesh, "Failed to create sharpener!!");

}

void Sharpener::drawSharpener() {

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(Position.x, Position.y);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(sharpenerObj->texture, 0, 0);
	AEGfxMeshDraw(sharpenerObj->pMesh, AE_GFX_MDM_TRIANGLES);
	AEGfxSetTransparency(1.0f);
}

void Sharpener::initSharpener() {

	Velocity.x = SPEED;
	//Position.x = 1.0f * AEGetWindowWidth() / 2;
	//Position.y = 1.0f * AEGetWindowHeight() / 2;
	Position.x = 50.0f;
	Position.y = -60.0f;
}

void Sharpener::updateSharpener() {

	//AEGfxSetPosition(Position.x, Position.y);

	//if ((AEInputCheckCurr(AEVK_LSHIFT) || AEInputCheckCurr(AEVK_RSHIFT)) &&
	//	AEInputCheckCurr(AEVK_LEFT)) //[]o player pushing left
	//{
	//	Position.x -= Velocity.x;
	//}

	//if ((AEInputCheckCurr(AEVK_LSHIFT) || AEInputCheckCurr(AEVK_RSHIFT)) &&
	//	AEInputCheckCurr(AEVK_RIGHT)) //o[] player pushing right
	//{
	//	Position.x += Velocity.x;
	//}
		 
	if (AEInputCheckCurr(AEVK_LEFT)) //[]o player pushing left
	{
		Position.x -= Velocity.x;
	}

	if (AEInputCheckCurr(AEVK_RIGHT)) //o[] player pushing right
	{
		Position.x += Velocity.x;
	}

}

void Sharpener::unloadSharpener() {

	AEGfxTextureUnload(sharpenerObj->texture);
	//AEGfxTextureUnload(sharpeners);
}


