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
Door DoorArray[2];

//This function is responsible for creating Mesh and loading texture for door.
void Door::LoadDoor()
{
	pDoor = sGameObjList + sGameObjNum++ ;
	pDoor->type = TYPE_DOOR;

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	pDoor->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pDoor->pMesh, "fail to create object!!");

	pDoor->texture = AEGfxTextureLoad("Resources/Door.png");
	AE_ASSERT_MESG(pDoor->texture, "Failed to create texture1!!");

}
void Door::InitDoor()
{	
	Scale = 50.0f;
	AEVec2Set(&pos, 50, 80);
	//AEVec2Set(&vel, 0, 0);
	AEVec2* pPos = &pos;
	AEVec2* pVel = &vel;
	for (int i = 0; i < 2; i++)
	{
		Door* Doortemp = DoorArray + i;
		Doortemp->flag = FLAG_ACTIVE;
		Doortemp->pos = *pPos;
		Doortemp->vel = *pVel;
	}


}

void Door::UpdateDoor()
{
	BoundingBox();
}

void Door::DrawDoor()
{
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(pos.x, pos.y);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(pDoor->texture, 0, 0);
	AEGfxSetTransform(Transform.m);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(pDoor->pMesh, AE_GFX_MDM_TRIANGLES);
	
}

void Door::BoundingBox()
{
	AEMtx33 Transform2, Size;
	for (int i = 0; i < 1; i++)
	{
		Door* Doortemp = DoorArray + i;
		AEMtx33Scale(&Size, Scale, Scale);
		AEMtx33Trans(&Transform2, pos.x, pos.y);
		AEMtx33Concat(&Transform, &Transform2, &Size);

		Doortemp->boundingBox.min.x = pos.x - Scale / 2;
		Doortemp->boundingBox.min.y = pos.y - Scale / 2;
		Doortemp->boundingBox.max.x = pos.x + Scale / 2;
		Doortemp->boundingBox.max.y = pos.y + Scale / 2;
	}

}

