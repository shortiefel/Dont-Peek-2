/* Start Header ************************************************************************/
/*!
\file GameState_DontPeek.h
\team name Don't Peek
\software name I Don't Wanna Do My Homework
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
#pragma once
#include "Main.h"
#include "Collision.h"

/******************************************************************************/
/*!
	DEFINES
*/
/******************************************************************************/

const unsigned int	GAME_OBJ_NUM_MAX = 50;					//The total number of different objects (Shapes)
const unsigned int	MAX = 10;
const float			SPEED = 300.f;

const f32			WORLD_SCALE_X = 40;
const f32			WORLD_SCALE_Y = 50;

enum TYPE
{
	// list of game object types
	TYPE_SHARPENER = 1,

	TYPE_HIGHLIGHTER,
	TYPE_ERASER,
	TYPE_PENCIL,
	TYPE_DOOR,
	TYPE_PLAYER,
	TYPE_WALL,
	TYPE_BOXES,
	TYPE_CAMERA,

	TYPE_NUM
};
// -----------------------------------------------------------------------------
// object flag definition

const unsigned long FLAG_ACTIVE = 0x00000001;

/******************************************************************************/
/*!
	STRUCTS AND CLASS DEFINITIONS
*/
/******************************************************************************/
struct GameObj
{
	unsigned long		type;		// object type
	AEGfxVertexList*	pMesh;		// This will hold the triangles which will form the shape of the object
	AEGfxTexture*		texture;
};

struct GameObjInst
{
	GameObj*			pObject;	// pointer to the 'original' shape

	AABB				boundingBox;	// object bouding box that encapsulates the object
	AEMtx33				transform;	// object transformation matrix: Each frame, 
	float				scale;		// scaling value of the object instance
	AEVec2				posCurr;	// object current position
	AEVec2				velCurr;	// obj velocity
	float				dirCurr;	// object current direction
	unsigned int		flag;		// bit flag or-ed together
	int					gridCollisionFlag; //hold current

};



/******************************************************************************/
/*!
	EXTERN VARIABLES / FUNCTIONS
*/
/******************************************************************************/
// list of original object
extern GameObj				sGameObjList[GAME_OBJ_NUM_MAX];				// Each element in this array represents a unique game object (shape)
extern unsigned long		sGameObjNum;

void GameStateDontPeekLoad(void);
void GameStateDontPeekInit(void);
void GameStateDontPeekUpdate(void);
void GameStateDontPeekDraw(void);
void GameStateDontPeekFree(void);
void GameStateDontPeekUnload(void);