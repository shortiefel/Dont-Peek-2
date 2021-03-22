/* Start Header ************************************************************************/
/*!
\file GameState_DontPeek.cpp
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

#include "GameState_DontPeek.h"
#include "Door.h"
#include "Player.h"
#include "Sharpener.h"
#include "Eraser.h"
#include "Highlighter.h"
#include "Pencil.h"
#include "Wall.h"
#include "Tutorial.h"
#include "Camera.h"


/******************************************************************************/
/*!
	DEFINES
*/
/******************************************************************************/
GameObj				sGameObjList[GAME_OBJ_NUM_MAX];				// Each element in this array represents a unique game object (shape)
unsigned long		sGameObjNum;

GameObjInst			sGameObjInstList[GAME_OBJ_INST_NUM_MAX];	// Each element in this array represents a unique game object instance (sprite)
unsigned long		sGameObjInstNum;


GameObjInst* gameObjInstCreate(unsigned long type, float scale,
	AEVec2* pPos, AEVec2* pVel, float dir);
void gameObjInstDestroy(GameObjInst* pInst);

//individual classes

static Door door;
Player player;
Sharpener sharpener;
Eraser eraser;
Pencil pencil;
static Highlighter highlighter;
Wall wwall;
Camera camera;


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
	memset(sGameObjInstList, 0, sizeof(GameObjInst) * GAME_OBJ_INST_NUM_MAX);
	// No game object instances (sprites) at this point
	sGameObjInstNum = 0;

	Tutorial_Load();
	wwall.LoadWall();
	sharpener.LoadSharpener();
	eraser.LoadEraser();
	highlighter.LoadHighlighter();
	pencil.LoadPencil();
	door.LoadDoor();
	player.Player_Load();
	
}

/******************************************************************************/
/*!
	"INIT" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekInit(void)
{
	Tutorial_Init();
	wwall.InitWall();
	sharpener.InitSharpener();
	eraser.InitEraser();
	highlighter.InitHighlighter();
	pencil.InitPencil();
	door.InitDoor();
	player.Player_Init();
	camera.initCamera();
}

/******************************************************************************/
/*!
	"UPDATE" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekUpdate(void)
{
	
	Tutorial_Update();
	sharpener.UpdateSharpener();
	eraser.UpdateEraser();
	highlighter.UpdateHighlighter();
	pencil.UpdatePencil();
	door.UpdateDoor();
	wwall.UpdateWall();
	player.Player_Update();
	camera.updateCamera();
	
}


/******************************************************************************/
/*!
	"DRAW" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekDraw(void)
{
	Tutorial_Draw();
	player.Player_Draw();
	wwall.DrawWall();
	highlighter.DrawHighlighter();
	pencil.DrawPencil();
	sharpener.DrawSharpener();
	eraser.DrawEraser();
	door.DrawDoor();
	
}

/******************************************************************************/
/*!
	"FREE" FUNCTION OF THE STATE
*/
/******************************************************************************/
void GameStateDontPeekFree(void)
{
	//killing all object instances in the array 
	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInst* pInst = sGameObjInstList + i;

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
	sharpener.UnloadSharpener();
	eraser.UnloadEraser();
	highlighter.UnloadHighlighter();
	pencil.UnloadPencil();
	door.UnloadDoor();
	player.Player_Unload();
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
