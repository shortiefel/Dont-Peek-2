#pragma once
/* Start Header ************************************************************************/
/*!
\file Wall.h
\team name Don't Peek
\software name I Don't Wanna Do My Homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief
In this file, it contains the declaration of 
functions found in Wall.cpp


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#include "Main.h"
#include "GameState_DontPeek.h"

enum wallType
{
	WALL,
	PLATFORM,
	CEILING
};

class Wall
{
private:
	GameObj* pWall;
	AEVec2 Wallpos;
	AEVec2 Walldir;
	float Wallscale;
	AEMtx33	transform;	// object transformation matrix
	AABB boundingBox;
	wallType Walltype;
	//AEGfxVertexList* wMesh;
public:
	/******************************************************************************/
	/*!
		Wall Load
		\brief Loads mesh for walls
	*/
	/******************************************************************************/
	void LoadWall();
	/******************************************************************************/
	/*!
		Wall Init
		\brief Initialises bounding box for wall
	*/
	/******************************************************************************/
	void InitWall();
	/******************************************************************************/
	/*!
		Wall Update
	*/
	/******************************************************************************/
	void UpdateWall();
	/******************************************************************************/
	/*!
		Wall Draw
		\brief Draws walls to check position
	*/
	/******************************************************************************/
	void DrawWall();
	/******************************************************************************/
	/*!
		Wall Free
		\brief Frees walls
	*/
	/******************************************************************************/
	void FreeWall();
	/******************************************************************************/
	/*!
		Wall Unload
		\brief Unloads textures
	*/
	/******************************************************************************/
	void UnloadWall();
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
	void CreateWall(AEVec2 pos, AEVec2 dir, int number, float scale, wallType type);
	/******************************************************************************/
	/*!
		Wall Getter & Setter Functions
	*/
	/******************************************************************************/
	wallType GetType(int i);

	AABB GetWallBoundingBox(int i);
};

//functions for other people

int Get_NumWalls();
Wall* Get_WallArr();
extern Wall wall;
extern Wall* Walltemp;