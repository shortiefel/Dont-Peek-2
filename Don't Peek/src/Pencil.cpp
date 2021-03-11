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
\brief <give a brief description of this file>
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#include "GameState_DontPeek.h"
#include "Pencil.h"
#include "Eraser.h"

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
void Pencil::InitPencil() {

	scaleX = 20.0f;
	scaleY = 150.0f;
	for (int i = 0; i < 1; i++)
	{
		Pencil* Penciltemp = PencilArray + i;

		Penciltemp->flag = FLAG_ACTIVE;
		Penciltemp->vel = { 0,0 };
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

		/******************************************************************************/
		/*!
			ERASER
		*/
		/******************************************************************************/
		for (int j = 0; j < GetEraserNum(); j++)
		{
			Eraser* Erasertemp = EraserArray + j;

			if (CollisionIntersection_RectRect(Penciltemp->boundingBox, Penciltemp->vel, Erasertemp->GetEraserBoundingBox(j), Erasertemp->GetEraserVelocity(j)))
			{
				printf("remove the pencil pls");
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
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetTransparency(1.0f);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	for (int i = 0; i < PencilNum; i++)
	{
		Pencil* Penciltemp = PencilArray + i;
		AEGfxSetPosition(Penciltemp->pos.x, Penciltemp->pos.y);
		AEGfxSetTransform(Penciltemp->Transform.m);
		//AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxMeshDraw(pPencil->pMesh, AE_GFX_MDM_TRIANGLES);
	}
}

/******************************************************************************/
/*!
	Pencil Unload
*/
/******************************************************************************/
void Pencil::UnloadPencil()
{
	AEGfxTextureUnload(pPencil->texture);
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
		AEMtx33Scale(&Size, scaleX, scaleY);
		AEMtx33Trans(&Transform2, Penciltemp->pos.x, Penciltemp->pos.y);
		AEMtx33Concat(&(Penciltemp->Transform), &Transform2, &Size);

		Penciltemp->boundingBox.min.x = Penciltemp->pos.x - scaleX / 2;
		Penciltemp->boundingBox.min.y = Penciltemp->pos.y - scaleY / 2;
		Penciltemp->boundingBox.max.x = Penciltemp->pos.x + scaleX / 2;
		Penciltemp->boundingBox.max.y = Penciltemp->pos.y + scaleY / 2;
	}
}

/******************************************************************************/
/*!
	Pencil Getter & Setter Functions
*/
/******************************************************************************/
AABB Pencil::GetPencilBoundingBox(int i)
{
	Pencil* Penciltemp = PencilArray + i;
	return Penciltemp->boundingBox;
}

AEVec2 Pencil::GetPencilVelocity(int i)
{
	Pencil* Penciltemp = PencilArray + i;
	return Penciltemp->vel;
}

AEVec2 Pencil::GetPencilPosition(int i)
{
	Pencil* Penciltemp = PencilArray + i;
	return Penciltemp->pos;
}
void Pencil::SetPencilPosition(int i, AEVec2 NewPos)
{
	Pencil* Penciltemp = PencilArray + i;
	Penciltemp->pos = NewPos;
}

/******************************************************************************/
/*!
	Pencil External Functions
*/
/******************************************************************************/
int GetPencilNum()
{
	return PencilNum;
}
void SetPencilNum(int Num)
{
	PencilNum = Num;
}
