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






/******************************************************************************/
/*!
	"LOAD" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekLoad(void)
{

}

/******************************************************************************/
/*!
	"INIT" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekInit(void)
{

}

/******************************************************************************/
/*!
	"UPDATE" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekUpdate(void)
{
	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInst* pInst = sGameObjInstList + i;

		pInst->boundingBox.min.x = pInst->posCurr.x - pInst->scale * 0.5f;
		pInst->boundingBox.min.y = pInst->posCurr.y - pInst->scale * 0.5f;

		pInst->boundingBox.max.x = pInst->posCurr.x + pInst->scale * 0.5f;
		pInst->boundingBox.max.y = pInst->posCurr.y + pInst->scale * 0.5f;
	}
}

/******************************************************************************/
/*!
	"DRAW" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekDraw(void)
{

}

/******************************************************************************/
/*!
	"FREE" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekFree(void)
{

}

/******************************************************************************/
/*!
	"UNLOAD" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekUnload(void)
{

}
