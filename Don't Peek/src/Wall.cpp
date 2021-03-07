
#include "Wall.h"

static GameObj* pObj;
static int numberWalls = 0;
static Wall wall[100];

void Wall::LoadWall()
{
	pObj = sGameObjList + sGameObjNum++;
	pObj->type = TYPE_WALL;

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	pObj->pMesh = AEGfxMeshEnd();

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
		AEGfxMeshDraw(pObj->pMesh, AE_GFX_MDM_TRIANGLES);
	}
}

void Wall::FreeWall()
{

}
void Wall::UnloadWall()
{
	// free all mesh data (shapes) of each object using "AEGfxTriFree"
	for (unsigned long i = 0; i < numberWalls; i++)
	{
		GameObj* Objects = sGameObjList + i;
		if (Objects->pMesh)
			AEGfxMeshFree(Objects->pMesh);
	}
}