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

#include "GameState_DontPeek.h"
#include "Door.h"

Door DoorArray[MAX];
static int DoorNum = 0;

/******************************************************************************/
/*!
	Door Load
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
	Door Init
*/
/******************************************************************************/
void Door::InitDoor()
{	
	
	Scale = 100.0f;
	for (int i = 0; i < DoorNum; i++)
	{
		Door* Doortemp = DoorArray + i;
		Doortemp->flag = FLAG_ACTIVE;
		Doortemp->vel = {0,0};
	}
}

/******************************************************************************/
/*!
	Door Update
*/
/******************************************************************************/
void Door::UpdateDoor()
{
	BoundingBox();
}

/******************************************************************************/
/*!
	Door Draw
*/
/******************************************************************************/
void Door::DrawDoor()
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	for (int i = 0; i < DoorNum; i++)
	{

		Door* Doortemp = DoorArray + i;
		AEGfxSetPosition(Doortemp->pos.x, Doortemp->pos.y);
		AEGfxTextureSet(pDoor->texture, 0, 0);
		AEGfxSetTransform(Doortemp->Transform.m);
		AEGfxMeshDraw(pDoor->pMesh, AE_GFX_MDM_TRIANGLES);
	}
}

/******************************************************************************/
/*!
	Door Free
*/
/******************************************************************************/
void Door::FreeDoor()
{
	AEGfxMeshFree(pDoor->pMesh);
}

/******************************************************************************/
/*!
	Door Unload
*/
/******************************************************************************/
void Door::UnloadDoor()
{
	AEGfxTextureUnload(pDoor->texture);
	DoorNum = 0;
}

/******************************************************************************/
/*!
	Door Bounding Box
*/
/******************************************************************************/
void Door::BoundingBox()
{
	AEMtx33 Transform2, Size;
	for (int i = 0; i < DoorNum; i++)
	{
		Door* Doortemp = DoorArray + i;
		AEMtx33Scale(&Size, Scale, Scale);
		AEMtx33Trans(&Transform2, Doortemp->pos.x, Doortemp->pos.y);
		AEMtx33Concat(&(Doortemp->Transform), &Transform2, &Size);

		Doortemp->boundingBox.min.x = Doortemp->pos.x - Scale / 4;
		Doortemp->boundingBox.min.y = Doortemp->pos.y - Scale / 4;
		Doortemp->boundingBox.max.x = Doortemp->pos.x + Scale / 6;
		Doortemp->boundingBox.max.y = Doortemp->pos.y + Scale / 6;
	}
}

/******************************************************************************/
/*!
	Door Getter & Setter Functions
*/
/******************************************************************************/
AABB Door::GetDoorBoundingBox(int i)
{
	Door* Doortemp = DoorArray + i;
	return Doortemp->boundingBox;
}
AEVec2 Door::GetDoorVelocity(int i)
{
	Door* Doortemp = DoorArray + i;
	return Doortemp->vel;
}
AEVec2 Door::GetDoorPosition(int i)
{
	Door* Doortemp = DoorArray + i;
	return Doortemp->pos;
}
void Door::SetDoorPosition(int i, AEVec2 NewPos)
{
	Door* Doortemp = DoorArray + i;
	Doortemp->pos = NewPos;
}

/******************************************************************************/
/*!
	Door External Functions
*/
/******************************************************************************/
int GetDoorNum()
{
	return DoorNum;
}
void SetDoorNum(int Num)
{
	DoorNum = Num;
}