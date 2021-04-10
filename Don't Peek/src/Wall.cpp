/* Start Header ************************************************************************/
/*!
\file Wall.cpp
\team name Don't Peek
\software name I Don't Wanna Do My Homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief 
This file contains all the functions that is required for our wall/ceiling/platform object.


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

//Initalization
#include "Wall.h"
#include "Collision.h"
#include "Player.h"
#include <iostream>
#include "GameStateMgr.h"

static int numberWalls = 0;
static Wall WallArr[1000];
Wall* Walltemp = nullptr;

/******************************************************************************/
/*!
	Wall Load
	\brief Loads mesh for walls
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
	Wall Init
	\brief Initialises bounding box for wall
*/
/******************************************************************************/
void Wall::InitWall()
{
	Walltemp = new Wall[1000];

	for (int i = 0; i < numberWalls; i++)
	{
		//printf("wall %d pos = (%f,%f)\n", i, WallArr[i].Wallpos.x, WallArr[i].Wallpos.y);
	}

	for (int i = 0; i < numberWalls; i++)
	{
		Wall* Walltemp = WallArr + i;

		Walltemp->boundingBox.min.x = Walltemp->Wallpos.x - Walltemp->Wallscale / 2;
		Walltemp->boundingBox.min.y = Walltemp->Wallpos.y - Walltemp->Wallscale / 2;
		Walltemp->boundingBox.max.x = Walltemp->Wallpos.x + Walltemp->Wallscale / 2;
		Walltemp->boundingBox.max.y = Walltemp->Wallpos.y + Walltemp->Wallscale / 2;

		//printf("bounding box max x %f \n", Walltemp->boundingBox.max.x);
		//printf("bounding box min x %f \n", Walltemp->boundingBox.min.x);
	
	}
}

/******************************************************************************/
/*!
	Wall Update
*/
/******************************************************************************/
void Wall::UpdateWall()
{
	
}

/******************************************************************************/
/*!
	Wall Draw
	\brief Draws walls to check position
*/
/******************************************************************************/
void Wall::DrawWall()
{	
	
	//AEGfxSetBlendMode(AE_GFX_BM_NONE);	
	//AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	//for (int i = 0; i < numberWalls; i++)
	//{
	//	//printf("print wall");
	//	// Drawing object 1
	//	if (WallArr[i].Walltype == WALL)
	//	{
	//		// Set the current object instance's transform matrix using "AEGfxSetTransform"
	//		AEGfxSetTransform(WallArr[i].transform.m);
	//		// Draw the shape used by the current object instance using "AEGfxMeshDraw"
	//		AEGfxSetBlendColor(0.f, 0.f, 0.f, 1.f);
	//		AEGfxMeshDraw(pWall->pMesh, AE_GFX_MDM_TRIANGLES);
	//	}
	//	else if (WallArr[i].Walltype == PLATFORM)
	//	{
	//		// Set the current object instance's transform matrix using "AEGfxSetTransform"
	//		AEGfxSetTransform(WallArr[i].transform.m);
	//		// Draw the shape used by the current object instance using "AEGfxMeshDraw"
	//		AEGfxSetBlendColor(1.0f, 0.f, 0.f, 1.f);
	//		AEGfxMeshDraw(pWall->pMesh, AE_GFX_MDM_TRIANGLES);
	//	}
	//	else if (WallArr[i].Walltype == CEILING)
	//	{
	//		// Set the current object instance's transform matrix using "AEGfxSetTransform"
	//		AEGfxSetTransform(WallArr[i].transform.m);
	//		// Draw the shape used by the current object instance using "AEGfxMeshDraw"
	//		AEGfxSetBlendColor(0.0f, 1.f, 0.f, 1.f);
	//		AEGfxMeshDraw(pWall->pMesh, AE_GFX_MDM_TRIANGLES);
	//	}
	//}
}

/******************************************************************************/
/*!
	Wall Free
	\brief Frees walls
*/
/******************************************************************************/
void Wall::FreeWall()
{
	numberWalls = 0; 
	if (Walltemp != NULL)
		delete[] Walltemp;
}

/******************************************************************************/
/*!
	Wall Unload
	\brief Unloads textures
*/
/******************************************************************************/
void Wall::UnloadWall()
{
	if (AEInputCheckCurr(AEVK_P))
	{
		gGameStateNext = GS_PAUSE;
	}
	else
	{
		if(pWall->pMesh)
			AEGfxMeshFree(pWall->pMesh);
		if(pWall->texture)
			AEGfxTextureUnload(pWall->texture);
		//printf("walls DESTROY\n");
	}

	
}

/******************************************************************************/
/*!
	Wall CreateWall
	\brief Creates a wall and stores position in wall array
	\param AEVec2 pos
	\param int number
	\param float scale
	\param wallType type
*/
/******************************************************************************/
void Wall::CreateWall(AEVec2 pos, AEVec2 dir, int number, float scale, wallType type)
{


	Walltemp = WallArr + numberWalls;
	AEMtx33	trans, sc;
	for (int i = 0; i <number; i++, Walltemp++)
	{

		Walltemp->Wallscale = scale;
		// new pos = old pos + (dir * 1/2 size) * number of walls
		Walltemp->Wallpos.x = pos.x + Walltemp->Wallscale * i * dir.x;
		Walltemp->Wallpos.y = pos.y + Walltemp->Wallscale * i * dir.y;
		Walltemp->Walltype = type;
		numberWalls++;

		// Compute the scaling matrix
		AEMtx33Scale(&sc, Walltemp->Wallscale, Walltemp->Wallscale);
		// Compute the translation matrix
		AEMtx33Trans(&trans, Walltemp->Wallpos.x, Walltemp->Wallpos.y);

		AEMtx33Concat(&(Walltemp->transform), &trans, &sc);
	}
}

/******************************************************************************/
/*!
	Wall Getter & Setter Functions
*/
/******************************************************************************/
AABB Wall::GetWallBoundingBox(int i)	//Allow other files to use wall boundingbox without changing it.
{
	Wall* Walltemp = WallArr + i;
	return Walltemp->boundingBox;
}

wallType Wall::GetType(int i)		//Allow other files to check wall type without changing it.
{
	Wall* Walltemp = WallArr + i;
	return Walltemp->Walltype;
}

/******************************************************************************/
/*!
	Wall External Functions
*/
/******************************************************************************/
int Get_NumWalls()	//Allow other files to run through a loop of all the walls. [E.g. to detect collision of all walls]
{
	return numberWalls;
}

Wall* Get_WallArr()	//Set the number of wall object to be created. [This is used for level design]
{
	return WallArr;
}