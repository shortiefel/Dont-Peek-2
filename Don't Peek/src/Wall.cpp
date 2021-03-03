
#include "Wall.h"

/*static WallObj				WallObjList[GAME_OBJ_NUM_MAX];			// Each element in this array represents a unique game object (shape)
static unsigned long		WallObjNum;								// The number of defined game objects

static Wall					WallObjInstList[GAME_OBJ_NUM_MAX];			// Each element in this array represents a unique game object (shape)
static unsigned long		WallObjInstNum;								// The number of defined game objects

void Tutorial(void)
{
	//TODO: code the wall you want
}

void Wall_Load(void)
{
	// zero the game object array
	memset(WallObjList, 0, sizeof(WallObj) * GAME_OBJ_NUM_MAX);
	// No game objects (shapes) at this point
	WallObjNum = 0;

	// zero the game object instance array
	memset(WallObjInstList, 0, sizeof(Wall) * GAME_OBJ_NUM_MAX);
	// No game object instances (sprites) at this point
	WallObjInstNum = 0;

	// list of original object
	WallObj* wObj;

	wObj = WallObjList + WallObjNum ++;
	wObj->type = WALL;

	AEGfxMeshStart();

	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	wObj->wMesh = AEGfxMeshEnd();

}

void Wall_Init(void)
{
	Tutorial();
	//load mesh
	CreateWall(WALL, 100, nullptr, nullptr, 0.0f);
}

Wall* Wall::CreateWall(unsigned long tpe, float scale, AEVec2* pPos, float dir)
{
	AEVec2 zero;
	AEVec2Zero(&zero);

	AE_ASSERT_PARM(tpe < WallObjNum);

	// loop through the object instance list to find a non-used object instance
	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		Wall* wInst = WallObjInstList + i;

		// check if current instance is not used
		if (flag == 0)
		{
			// it is not used => use it to create the new instance
			wInst->wObj = WallObjList + tpe;
			wInst->flag = FLAG_ACTIVE;
			wInst->height = scale;
			wInst->width = scale;
			wInst->position = pPos ? *pPos : zero;
			wInst->direction = dir;

			// return the newly created instance
			return wInst;
		}
	}

	// cannot find empty slot => return 0
	return 0;
}

void Wall_Render(void)
{
	//tbc
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);

	// draw all object instances in the list
	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInst* pInst = sGameObjInstList + i;

		// skip non-active object
		if ((pInst->flag & FLAG_ACTIVE) == 0)
			continue;

		// Set the current object instance's transform matrix using "AEGfxSetTransform"
		AEGfxSetTransform(pInst->transform.m);
		// Draw the shape used by the current object instance using "AEGfxMeshDraw"
		AEGfxMeshDraw(pInst->pObject->pMesh, AE_GFX_MDM_TRIANGLES);
	}
}

void Wall_Update(void)
{
	//Wall* wallPointer = nullptr;
	int size = 0;


	//if (currentStage == TUTORIAL)

	for (int i = 0; i < size; ++i)
	{
		//if (wallPointer[i].GetActive() == false)
			//continue;
		//wallPointer[i].Wall_Render();
	}
}
void Wall_Exit(void)
{
	//free mesh
}
*/