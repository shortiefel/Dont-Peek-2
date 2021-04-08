/* Start Header ************************************************************************/
/*!
\file Pencil.cpp
\team name Don't Peak
\software name I don't want to do homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu
\date 22/01/2021
\brief 
This file contains all the functions that is required for our object pencil.
The pencil is a temporary wall that can be removed when eraser collides with it.


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#include "GameStateMgr.h"
#include "GameState_DontPeek.h"
#include "Pencil.h"
#include "Eraser.h"

//Initialization
Pencil PencilArray[MAX];
static int PencilNum = 0;

/******************************************************************************/
/*!
	Pencil Load
*/
/******************************************************************************/
void Pencil::LoadPencil()
{
	pPencil = sGameObjList + sGameObjNum++;
	pPencil->type = TYPE_PENCIL;

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00AAAAAA, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00AAAAAA, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00AAAAAA, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00AAAAAA, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00AAAAAA, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00AAAAAA, 0.0f, 0.0f);

	pPencil->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pPencil->pMesh, "Failed to create pencil!!");

}

/******************************************************************************/
/*!
	Pencil Init
*/
/******************************************************************************/
void Pencil::InitPencil() 
{
	for (int i = 0; i < PencilNum; i++)
	{
		Pencil* Penciltemp = PencilArray + i;

		Penciltemp->flag = FLAG_ACTIVE;
		Penciltemp->vel = { 0,0 };
		Penciltemp->collisionFlag = 1;
	}
}

/******************************************************************************/
/*!
	Pencil Update
*/
/******************************************************************************/
void Pencil::UpdatePencil()
{
	
	BoundingBox();

	for (int i = 0; i < PencilNum; i++)
	{
		Pencil* Penciltemp = PencilArray + i;

		/*===============================================================================
			ERASER
		=================================================================================*/
		for (int j = 0; j < GetEraserNum(); j++)
		{
			Eraser* Erasertemp = EraserArray + j;

			if (CollisionIntersection_RectRect(Penciltemp->boundingBox, Penciltemp->vel, Erasertemp->GetEraserBoundingBox(j), Erasertemp->GetEraserVelocity(j)))
			{
				Penciltemp->collisionFlag = 0;
				Penciltemp->flag = 0;
			}

		}//End of Eraser for loop
	}
}

/******************************************************************************/
/*!
	Pencil Draw
*/
/******************************************************************************/
void Pencil::DrawPencil()
{
	for (int i = 0; i < PencilNum; i++)
	{
		Pencil* Penciltemp = PencilArray + i;
		if (Penciltemp->collisionFlag == 0)
		{
			continue;
		}
		AEGfxSetBlendMode(AE_GFX_BM_NONE);
		AEGfxSetTransparency(1.0f);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetPosition(Penciltemp->pos.x, Penciltemp->pos.y);
		AEGfxSetTransform(Penciltemp->Transform.m);
		AEGfxMeshDraw(pPencil->pMesh, AE_GFX_MDM_TRIANGLES);
	}
}

/******************************************************************************/
/*!
	Pencil Free
*/
/******************************************************************************/
void Pencil::FreePencil()
{
	
}

/******************************************************************************/
/*!
	Pencil Unload
*/
/******************************************************************************/
void Pencil::UnloadPencil()
{
		if (pPencil->texture)
			AEGfxTextureUnload(pPencil->texture);

		if (pPencil->pMesh)
			AEGfxMeshFree(pPencil->pMesh);

		PencilNum = 0;
}

/******************************************************************************/
/*!
	Pencil Bounding Box
*/
/******************************************************************************/
void Pencil::BoundingBox()
{
	AEMtx33 Transform2, Size;
	for (int i = 0; i < PencilNum; i++)
	{
		Pencil* Penciltemp = PencilArray + i;
		if (Penciltemp->flag == FLAG_ACTIVE)
		{
			AEMtx33Scale(&Size, Penciltemp->scaleX, Penciltemp->scaleY);
			AEMtx33Trans(&Transform2, Penciltemp->pos.x, Penciltemp->pos.y);
			AEMtx33Concat(&(Penciltemp->Transform), &Transform2, &Size);

			Penciltemp->boundingBox.min.x = Penciltemp->pos.x - Penciltemp->scaleX / 2;
			Penciltemp->boundingBox.min.y = Penciltemp->pos.y - Penciltemp->scaleY / 2;
			Penciltemp->boundingBox.max.x = Penciltemp->pos.x + Penciltemp->scaleX / 2;
			Penciltemp->boundingBox.max.y = Penciltemp->pos.y + Penciltemp->scaleY / 2;
		}
		else
		{
			Penciltemp->boundingBox.min.x = 1000;
			Penciltemp->boundingBox.min.y = 1000;
			Penciltemp->boundingBox.max.x = 1000;
			Penciltemp->boundingBox.max.y = 1000;
		}
	}
}

/******************************************************************************/
/*!
	Pencil Getter & Setter Functions
*/
/******************************************************************************/
AABB Pencil::GetPencilBoundingBox(int i)	//Allow other files to use pencil boundingbox without changing it.
{
	Pencil* Penciltemp = PencilArray + i;
	return Penciltemp->boundingBox;
}

AEVec2 Pencil::GetPencilVelocity(int i)		//Allow other files to use pencil velocity without changing it.
{
	Pencil* Penciltemp = PencilArray + i;
	return Penciltemp->vel;
}

AEVec2 Pencil::GetPencilPosition(int i)		//Allow other files to use pencil position without changing it.
{
	Pencil* Penciltemp = PencilArray + i;
	return Penciltemp->pos;
}
void Pencil::SetPencil(int i, AEVec2 NewPos, float scale_X, float scale_Y)	//Allow other files to set the pencil position. [This is used for level design]
{
	Pencil* Penciltemp = PencilArray + i;
	Penciltemp->pos = NewPos;
	Penciltemp->scaleX = scale_X;
	Penciltemp->scaleY = scale_Y;
}

/******************************************************************************/
/*!
	Pencil External Functions
*/
/******************************************************************************/
int GetPencilNum()	//Allow other files to run through a loop of all the pencil. [E.g. to detect collision of all pencil]
{
	return PencilNum;
}
void SetPencilNum(int Num)	//Set the number of pencil object to be created. [This is used for level design]
{
	PencilNum = Num;
}
