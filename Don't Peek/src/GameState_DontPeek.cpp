#include "GameState_DontPeek.h"
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

void gameObjInstDestroy(GameObjInst* pInst)
{
	// if instance is destroyed before, just return
	if (pInst->flag == 0)
		return;

	// zero out the flag
	pInst->flag = 0;
}

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
