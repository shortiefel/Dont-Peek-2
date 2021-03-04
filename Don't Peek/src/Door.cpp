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
\brief This file is contains all the functions required to create door.


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#include "Door.h"
#include "GameState_DontPeek.h"

GameObj* dObj;
//This function is responsible for creating Mesh and loading texture for door.
void Door::LoadDoor()
{
	dObj = sGameObjList + sGameObjNum++;
	dObj->type = TYPE_DOOR;

	AEGfxMeshStart();
	AEGfxTriAdd(
		-30.0f, -30.0f, 0x00000000, 0.0f, 1.0f,
		45.0f, -30.0f, 0x00000000, 1.0f, 1.0f,
		-30.0f, 30.0f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		45.0f, -30.0f, 0x00000000, 1.0f, 1.0f,
		45.0f, 30.0f, 0x00000000, 1.0f, 0.0f,
		-30.0f, 30.0f, 0x00000000, 0.0f, 0.0f);
	dObj->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(dObj->pMesh, "fail to create object!!");

	dObj->texture = AEGfxTextureLoad("Resources/Door.png");
	AE_ASSERT_MESG(dObj->texture, "Failed to create texture1!!");

}
void Door::CreateDoor()
{
	AEVec2Set(&Doorpos, 0, 100);
	// loop through the object instance list to find a non-used object instance
	AEVec2 zero;
	AEVec2Zero(&zero);
	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInst* pInst = sGameObjInstList + i;

		// check if current instance is not used
		if (pInst->flag == 0)
		{
			// it is not used => use it to create the new instance
			pInst->pObject = sGameObjList + TYPE_DOOR;
			pInst->flag = FLAG_ACTIVE;
			pInst->scale = 1.0f;
			pInst->posCurr = Doorpos;
			pInst->velCurr = zero;
			pInst->dirCurr = 0;
			printf("Door Slot %lu\n", i);
			break;
		}
	}
}
void Door::DrawDoor()
{
	// Drawing object 2 - (first) - No tint
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	// Set position for object 2
	AEGfxSetPosition(Doorpos.x, Doorpos.y);
	// No tint
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

	AEGfxTextureSet(dObj->texture, 0, 0);		// Same object, different texture

	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(dObj->pMesh, AE_GFX_MDM_TRIANGLES);
	// Set Transparency
	AEGfxSetTransparency(0.0f);

}
