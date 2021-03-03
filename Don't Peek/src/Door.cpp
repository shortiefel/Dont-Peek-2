/* Start Header ************************************************************************/
/*!
\file Door.cpp
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

#include "Door.h"
#include "GameState_DontPeek.h"

GameObj* pObj;

void Door::LoadDoor()
{
	pObj = sGameObjList + sGameObjNum++;
	pObj->type = TYPE_DOOR;

	pObj->texture = AEGfxTextureLoad("Door.png");
	AEGfxMeshStart();
	AEGfxTriAdd(
		-30.0f, -30.0f, 0x00000000, 0.0f, 0.0f,
		45.0f, -30.0f, 0x00000000, 0.0f, 0.0f,
		-30.0f, 30.0f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		45.0f, -30.0f, 0x00000000, 0.0f, 0.0f,
		45.0f, 30.0f, 0x00000000, 0.0f, 0.0f,
		-30.0f, 30.0f, 0x00000000, 0.0f, 0.0f);
	pObj->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pObj->pMesh, "fail to create object!!");

}
AEVec2 Door::InitDoor()
{
	Doorpos.x = 5;
	Doorpos.y = 5;
	return Doorpos;
}
void UpdateDoor()
{

}
void ExitDoor()
{

}
