#include "GameState_DontPeek.h"

#include "Wall.h"

#include "Door.h"


/******************************************************************************/
/*!
	DEFINES
*/
/******************************************************************************/

GameObjInst* gameObjInstCreate(unsigned long type, float scale,
	AEVec2* pPos, AEVec2* pVel, float dir);
void gameObjInstDestroy(GameObjInst* pInst);

Door door;
Wall wall;

/******************************************************************************/
/*!
	"LOAD" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekLoad(void)
{

	memset(sGameObjList, 0, sizeof(GameObj) * GAME_OBJ_NUM_MAX);
	// No game objects (shapes) at this point
	sGameObjNum = 0;
	door.LoadDoor();
	wall.LoadWall();

}

/******************************************************************************/
/*!
	"INIT" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekInit(void)
{
	//AEVec2 a = door.InitDoor();
	//gameObjInstCreate(TYPE_DOOR, 10.0f, nullptr, nullptr, 0.0f);
	wall.InitWall();

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
		if ((pInst->flag & FLAG_ACTIVE) == 0)
			continue;

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

	door.DrawDoor();
	wall.DrawWall();

}

/******************************************************************************/
/*!
	"FREE" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekFree(void)
{
	wall.FreeWall();
}

/******************************************************************************/
/*!
	"UNLOAD" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekUnload(void)
{
	wall.UnloadWall();
}


/******************************************************************************/
/*!
	\brief creates a new instance in the object instance list with paramaters
		   given
	\param type
		   type of object from enum TYPE
	\param scale
		   size of object.
	\param pPos
		   position of object
	\param pVel
		   velocity of object
	\param dir
		   direction of object
*/
/******************************************************************************/


GameObjInst* gameObjInstCreate(unsigned long type,
	float scale,
	AEVec2* pPos,
	AEVec2* pVel,
	float dir)
{
	AEVec2 zero;
	AEVec2Zero(&zero);

	AE_ASSERT_PARM(type < sGameObjNum);

	// loop through the object instance list to find a non-used object instance
	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInst* pInst = sGameObjInstList + i;

		// check if current instance is not used
		if (pInst->flag == 0)
		{
			// it is not used => use it to create the new instance
			pInst->pObject = sGameObjList + type;
			pInst->flag = FLAG_ACTIVE;
			pInst->scale = scale;
			pInst->posCurr = pPos ? *pPos : zero;
			pInst->velCurr = pVel ? *pVel : zero;
			pInst->dirCurr = dir;

			// return the newly created instance
			return pInst;
		}
	}

	// cannot find empty slot => return 0
	return 0;
}


/******************************************************************************/
/*!
	\brief destroys a new instance in the object instance list
	\param pInst
		   pointer to object to destroy.
*/
/******************************************************************************/
void gameObjInstDestroy(GameObjInst* pInst)
{
	// if instance is destroyed before, just return
	if (pInst->flag == 0)
		return;

	// zero out the flag
	pInst->flag = 0;
}

