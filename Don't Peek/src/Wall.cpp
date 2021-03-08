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
static Wall wall[100];

void Wall::LoadWall()
{
	pWall = sGameObjList + sGameObjNum++;
	pWall->type = TYPE_WALL;

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 0.0f,
		0.5f, -0.5f, 0x00000000, 0.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, 0.0f, 0.0f,
		0.5f, 0.5f, 0x00000000, 0.0f, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	pWall->pMesh = AEGfxMeshEnd();

}
void Wall::InitWall()
{
	AEVec2 pos{ 5,5 };
	AEVec2 dir{ 0,1 };
	CreateWall(pos, dir, 3, wall,30.f);

	pos={ 0,10 };
	dir={ 1,0 };
	CreateWall(pos, dir, 10, wall, 30.f);
	printf("drawing\n");
	printf("number %d \n", numberWalls);

	for (int i = 0; i < numberWalls; i++)
	{
		printf("wall %d pos = (%f,%f)\n", i, wall[i].Wallpos.x, wall[i].Wallpos.y);
	}

	for (int i = 0; i < numberWalls; i++)
	{
		Wall* Walltemp = wall + i;

		Walltemp->boundingBox.min.x = Wallpos.x - Wallscale / 2;
		Walltemp->boundingBox.min.y = Wallpos.y - Wallscale / 2;
		Walltemp->boundingBox.max.x = Wallpos.x + Wallscale / 2;
		Walltemp->boundingBox.max.y = Wallpos.y + Wallscale / 2;
		printf("collide with wall");
	}
}

void CreateWall(AEVec2 pos, AEVec2 dir, int number, Wall* const WallArr, float scale)
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
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);

	for (int i = 0; i < numberWalls; i++)
	{
		// Drawing object 1
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		// Set the current object instance's transform matrix using "AEGfxSetTransform"
		AEGfxSetTransform(wall[i].transform.m);
		// Draw the shape used by the current object instance using "AEGfxMeshDraw"
		AEGfxMeshDraw(pWall->pMesh, AE_GFX_MDM_TRIANGLES);
	}
}

void Wall::UpdateWall()
{
	for (int i = 0; i < 1; i++)
	{
		Wall* Walltemp = wall + i;
		for (int j = 0; j < numberWalls; j++)
		{
			/*Wall* Walltemp = wall + j;
			if (CollisionIntersection_RectRect(Walltemp->boundingBox, { 0,0 } , Walltemp->boundingBox, { 0,0 }))
			{
				pos.x += 5;
				printf("Collision True");
				printf("BB2 min x %f \n", Sharpenertemp->boundingBox.min.x);
				printf("BB2 min y %f \n", Sharpenertemp->boundingBox.min.y);
				printf("BB2 maX x %f \n", Sharpenertemp->boundingBox.max.x);
				printf("BB2 max y %f \n", Sharpenertemp->boundingBox.max.y);
				printf("BB min x %f \n", highlightertemp->boundingBox.min.x);
				printf("BB min y %f \n", highlightertemp->boundingBox.min.y);
				printf("BB maX x %f \n", highlightertemp->boundingBox.max.x);
				printf("BB max y %f \n", highlightertemp->boundingBox.max.y);
			}*/
		}
	}
}

void Wall::FreeWall()
{

}
void Wall::UnloadWall()
{
	// free all mesh data (shapes) of each object using "AEGfxTriFree"
	/*for (unsigned long i = 0; i < numberWalls; i++)
	{
		GameObj* Objects = sGameObjList + i;
		if (Objects->pMesh)
			AEGfxMeshFree(Objects->pMesh);
	}*/
}