#pragma once
#include "Main.h"
#include "Collision.h"

/******************************************************************************/
/*!
	DEFINES
*/
/******************************************************************************/

const unsigned int	GAME_OBJ_NUM_MAX = 32;			//The total number of different objects (Shapes)
const unsigned int	GAME_OBJ_INST_NUM_MAX = 2048;			//The total number of different game object instances

// -----------------------------------------------------------------------------
// object flag definition

const unsigned long FLAG_ACTIVE = 0x00000001;

/******************************************************************************/
/*!
	STRUCTS AND CLASS DEFINITIONS
*/
/******************************************************************************/
struct GameObjInst
{
	AABB boundingBox;// object bouding box that encapsulates the object
	AEMtx33				transform;	// object transformation matrix: Each frame, 
	float				scale;		// scaling value of the object instance
	AEVec2				posCurr;	// object current position

};




/******************************************************************************/
/*!
	STATIC VARIABLES
*/
/******************************************************************************/
static GameObjInst			sGameObjInstList[GAME_OBJ_INST_NUM_MAX];	// Each element in this array represents a unique game object instance (sprite)
static unsigned long		sGameObjInstNum;


void GameStateDontPeekLoad(void);
void GameStateDontPeekInit(void);
void GameStateDontPeekUpdate(void);
void GameStateDontPeekDraw(void);
void GameStateDontPeekFree(void);
void GameStateDontPeekUnload(void);


