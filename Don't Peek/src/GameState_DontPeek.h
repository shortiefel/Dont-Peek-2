/* Start Header ************************************************************************/
/*!
\file GameState_DontPeek.h
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
#include "Main.h"
#include "Collision.h"

/******************************************************************************/
/*!
	DEFINES
*/
/******************************************************************************/

const unsigned int	GAME_OBJ_NUM_MAX = 32;					//The total number of different objects (Shapes)
const unsigned int	GAME_OBJ_INST_NUM_MAX = 2048;			//The total number of different game object instances
const unsigned int	MAX = 10;
//const float			PLAYER_ACCEL_FORWARD = 40.f;
//const float			PLAYER_ACCEL_BACKWARD = 40.f;
//const float			PLAYER_SPEED = 100.0f;
//const float			MAX_SPEED = 60.0f;
const float			SPEED = 5.0f;


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
	unsigned long		flag;		// bit flag or-ed together

};



/******************************************************************************/
/*!
	STATIC VARIABLES
*/
/******************************************************************************/
// list of original object
extern GameObj				sGameObjList[GAME_OBJ_NUM_MAX];				// Each element in this array represents a unique game object (shape)
extern unsigned long		sGameObjNum;

extern GameObjInst			sGameObjInstList[GAME_OBJ_INST_NUM_MAX];	// Each element in this array represents a unique game object instance (sprite)
extern unsigned long		sGameObjInstNum;

GameObjInst* gameObjInstCreate(unsigned long type, float scale,
	AEVec2* pPos, AEVec2* pVel, float dir);
void				gameObjInstDestroy(GameObjInst* pInst);




void GameStateDontPeekLoad(void);
void GameStateDontPeekInit(void);
void GameStateDontPeekUpdate(void);
void GameStateDontPeekDraw(void);
void GameStateDontPeekFree(void);
void GameStateDontPeekUnload(void);


