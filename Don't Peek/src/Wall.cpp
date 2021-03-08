/* Start Header ************************************************************************/
/*!
\file Wall.cpp
\team name Don't Peak
\software name I don't want to do homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief <give a brief description of this file>


Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#include "Wall.h"
#include "Collision.h"
#include "Player.h"

//static GameObj* pObj;
static int numberWalls = 0;
static Wall WallArr[40];

void Wall::LoadWall()
{
	pWall = sGameObjList + sGameObjNum++;
	pWall->type = TYPE_WALL;

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x0000000, 0.0f, 0.0f,
		0.5f, -0.5f, 0x0000000, 0.0f, 0.0f,
		-0.5f, 0.5f, 0x0000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x0000000, 0.0f, 0.0f,
		0.5f, 0.5f, 0x0000000, 0.0f, 0.0f,
		-0.5f, 0.5f, 0x0000000, 0.0f, 0.0f);

	pWall->pMesh = AEGfxMeshEnd();

}
void Wall::InitWall()
{
	/*AEVec2 pos{ 5,5 };
	AEVec2 dir{ 0,1 };
	CreateWall(pos, dir, 3, wall,30.f);*/

	/*pos={ 0,10 };
	dir={ 1,0 };
	CreateWall(pos, dir, 10, wall, 30.f);*/
	printf("drawing\n");
	printf("number %d \n", numberWalls);

	for (int i = 0; i < numberWalls; i++)
	{
		printf("wall %d pos = (%f,%f)\n", i, WallArr[i].Wallpos.x, WallArr[i].Wallpos.y);
	}

	for (int i = 0; i < numberWalls; i++)
	{
		Wall* Walltemp = WallArr + i;

		Walltemp->boundingBox.min.x = Walltemp->Wallpos.x - Walltemp->Wallscale / 2;
		Walltemp->boundingBox.min.y = Walltemp->Wallpos.y - Walltemp->Wallscale / 2;
		Walltemp->boundingBox.max.x = Walltemp->Wallpos.x + Walltemp->Wallscale / 2;
		Walltemp->boundingBox.max.y = Walltemp->Wallpos.y + Walltemp->Wallscale / 2;

		printf("bounding box max x %f \n", Walltemp->boundingBox.max.x);
	
	}
	
}

void Wall::CreateWall(AEVec2 pos, AEVec2 dir, int number, float scale)
{
	Wall *temp = WallArr + numberWalls;
	AEMtx33	trans, sc;
	for (int i = 0; i <number; i++, temp++)
	{
		temp->Wallscale = scale;
		// new pos = old pos + (dir * 1/2 size) * number of walls
		temp->Wallpos.x = pos.x + temp->Wallscale * i * dir.x;
		temp->Wallpos.y = pos.y + temp->Wallscale * i * dir.y;
		numberWalls++;

		// Compute the scaling matrix
		AEMtx33Scale(&sc, temp->Wallscale, temp->Wallscale);
		// Compute the translation matrix
		AEMtx33Trans(&trans, temp->Wallpos.x, temp->Wallpos.y);

		AEMtx33Concat(&(temp->transform), &trans, &sc);
	}
}

void Wall::DrawWall()
{	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	
	for (int i = 0; i < numberWalls; i++)
	{
		//printf("print wall");
		// Drawing object 1
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		// Set the current object instance's transform matrix using "AEGfxSetTransform"
		AEGfxSetTransform(WallArr[i].transform.m);
		// Draw the shape used by the current object instance using "AEGfxMeshDraw"
		AEGfxMeshDraw(pWall->pMesh, AE_GFX_MDM_TRIANGLES);
	}
}

void Wall::UpdateWall()
{
	
}

void Wall::FreeWall()
{

}
void Wall::UnloadWall()
{
}

int Get_NumWalls()
{
	return numberWalls;
}

Wall* Get_WallArr()
{
	return WallArr;
}