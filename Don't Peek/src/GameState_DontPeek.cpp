#include "GameState_DontPeek.h"
<<<<<<< HEAD
#include "Door.h"
#include "Player.h"
#include "Sharpener.h"
=======
#include "Sharpener.h"
#include "Highlighter.h"
>>>>>>> origin/Highlighter


/******************************************************************************/
/*!
	DEFINES
*/
/******************************************************************************/

<<<<<<< HEAD

=======
>>>>>>> origin/Highlighter
GameObjInst* gameObjInstCreate(unsigned long type, float scale,
	AEVec2* pPos, AEVec2* pVel, float dir);
void gameObjInstDestroy(GameObjInst* pInst);

<<<<<<< HEAD
//individual classes
Door door;
Player player;
Sharpener sharpener;



=======
Sharpener sharpener;
Highlighter highlighter;
>>>>>>> origin/Highlighter
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
<<<<<<< HEAD
	memset(sGameObjInstList, 0, sizeof(GameObjInst) * GAME_OBJ_INST_NUM_MAX);
	// No game object instances (sprites) at this point
	sGameObjInstNum = 0;

	//function calls
	door.LoadDoor();
	sharpener.loadSharpener();
	door.LoadDoor();
	player.Player_Character();
=======

	sharpener.loadSharpener();
	highlighter.loadHighlighter();
>>>>>>> origin/Highlighter



}

/******************************************************************************/
/*!
	"INIT" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekInit(void)
{
	sharpener.initSharpener();
<<<<<<< HEAD
	door.initDoor();
	player.InitPlayer();
	
=======
	highlighter.initHighlighter();
>>>>>>> origin/Highlighter
}

/******************************************************************************/
/*!
	"UPDATE" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekUpdate(void)
{

	//function calls
	player.UpdatePlayer();
	sharpener.updateSharpener();

<<<<<<< HEAD
	
=======
		pInst->boundingBox.max.x = pInst->posCurr.x + pInst->scale * 0.5f;
		pInst->boundingBox.max.y = pInst->posCurr.y + pInst->scale * 0.5f;
	}
	sharpener.updateSharpener();

	//for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	//{
	//	GameObjInst* pInst_1 = sGameObjInstList + i;
	//	if ((pInst_1->pObject->type == TYPE_SHARPENER))
	//	{
	//		//setting object instance
	//		for (unsigned long j = 0; j < GAME_OBJ_INST_NUM_MAX; j++)
	//		{
	//			GameObjInst* pInst_2 = sGameObjInstList + j;

	//			if (pInst_2->pObject->type == TYPE_HIGHLIGHTER)
	//			{
	//				if (CollisionIntersection_RectRect(pInst_1->boundingBox, pInst_1->velCurr, pInst_2->boundingBox, pInst_2->velCurr))
	//				{
	//					printf("test");
	//				}
	//			}
	//		}
	//	}
	//}


>>>>>>> origin/Highlighter
}

/******************************************************************************/
/*!
	"DRAW" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekDraw(void)
{
<<<<<<< HEAD
	
	door.DrawDoor();
	player.Player_Draw();
=======
	highlighter.drawHighlighter();
>>>>>>> origin/Highlighter
	sharpener.drawSharpener();

}

/******************************************************************************/
/*!
	"FREE" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekFree(void)
{
<<<<<<< HEAD
	//killing all object instances in the array 
	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInst* pInst = sGameObjInstList + i;
=======
	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInst* pInst = sGameObjInstList + i;

		//ignoring non-active object
		if ((pInst->flag & FLAG_ACTIVE) == 0)
			continue;
		gameObjInstDestroy(pInst);
	}
>>>>>>> origin/Highlighter

		//ignoring non-active object
		if ((pInst->flag & FLAG_ACTIVE) == 0)
			continue;
		gameObjInstDestroy(pInst);
	}
}

/******************************************************************************/
/*!
	"UNLOAD" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekUnload(void)
{
<<<<<<< HEAD
	//freeing all mesh data of each object
=======
>>>>>>> origin/Highlighter
	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObj* Objects = sGameObjList + i;
		if (Objects->pMesh)
			AEGfxMeshFree(Objects->pMesh);
	}
<<<<<<< HEAD
=======
	highlighter.unloadHighlighter();
	sharpener.unloadSharpener();
>>>>>>> origin/Highlighter
}

void gameObjInstDestroy(GameObjInst* pInst)
{
	// if instance is destroyed before, just return
	if (pInst->flag == 0)
		return;
<<<<<<< HEAD

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
=======

	// zero out the flag
	pInst->flag = 0;
>>>>>>> origin/Highlighter
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