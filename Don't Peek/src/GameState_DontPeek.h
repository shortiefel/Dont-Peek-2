#pragma once
#include "Main.h"
#include "Collision.h"

/******************************************************************************/
/*!
	DEFINES
*/
/******************************************************************************/

const unsigned int	GAME_OBJ_NUM_MAX = 32;					//The total number of different objects (Shapes)
const unsigned int	GAME_OBJ_INST_NUM_MAX = 2048;			//The total number of different game object instances

<<<<<<< HEAD
//const float			PLAYER_ACCEL_FORWARD = 40.f;
//const float			PLAYER_ACCEL_BACKWARD = 40.f;
//const float			PLAYER_SPEED = 100.0f;
//const float			MAX_SPEED = 60.0f;
const float			SPEED = 10.0f;

=======
>>>>>>> origin/Highlighter

enum TYPE
{
	// list of game object types
<<<<<<< HEAD
	TYPE_SHARPENER = 1,
=======
	TYPE_SHARPENER = 0,
>>>>>>> origin/Highlighter

	TYPE_HIGHLIGHTER,
	TYPE_ERASER,
	TYPE_PENCIL,
	TYPE_DOOR,
<<<<<<< HEAD
	TYPE_PLAYER,
=======
>>>>>>> origin/Highlighter

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
<<<<<<< HEAD
	AEGfxVertexList*	pMesh;		// This will hold the triangles which will form the shape of the object
	AEGfxTexture*		texture;
=======
	AEGfxVertexList* pMesh;		// This will hold the triangles which will form the shape of the object
	AEGfxTexture* texture;
>>>>>>> origin/Highlighter
};

struct GameObjInst
{
<<<<<<< HEAD
	GameObj*			pObject;	// pointer to the 'original' shape
=======
	GameObj* pObject;	// pointer to the 'original' shape
>>>>>>> origin/Highlighter
	unsigned long		flag;
	AABB				boundingBox;	// object bouding box that encapsulates the object
	AEMtx33				transform;	// object transformation matrix: Each frame, 
	float				scale;		// scaling value of the object instance
	AEVec2				posCurr;	// object current position
	AEVec2				velCurr;	// obj velocity
	float				dirCurr;	// object current direction

};



<<<<<<< HEAD
=======



>>>>>>> origin/Highlighter
/******************************************************************************/
/*!
	STATIC VARIABLES
*/
/******************************************************************************/
// list of original object
static GameObj				sGameObjList[GAME_OBJ_NUM_MAX];				// Each element in this array represents a unique game object (shape)
static unsigned long		sGameObjNum;

static GameObjInst			sGameObjInstList[GAME_OBJ_INST_NUM_MAX];	// Each element in this array represents a unique game object instance (sprite)
static unsigned long		sGameObjInstNum;



void GameStateDontPeekLoad(void);
void GameStateDontPeekInit(void);
void GameStateDontPeekUpdate(void);
void GameStateDontPeekDraw(void);
void GameStateDontPeekFree(void);
void GameStateDontPeekUnload(void);