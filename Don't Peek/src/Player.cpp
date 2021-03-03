#include "Player.h"
#include "GameState_DontPeek.h"



/******************************************************************************/
/*!
	Game Object 
*/
/******************************************************************************/

GameObj* pObj2;

void Player::Player_Character() //drawing of character
{
	//memset(sGameObjList, 0, sizeof(GameObj) * GAME_OBJ_INST_NUM_MAX);
	//no game object at this point
	sGameObjNum = 0;
	pObj2 = sGameObjList + sGameObjNum++;
	pObj2->type = TYPE_PLAYER;


	//Drawing of Player
	AEGfxMeshStart();
	AEGfxTriAdd(
		-30.0f, -30.0f, 0x00000000, 0.0f, 1.0f,
		45.0f, -30.0f, 0x00000000, 1.0f, 1.0f,
		-30.0f, 30.0f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		45.0f, -30.0f, 0x00000000, 1.0f, 1.0f,
		45.0f, 30.0f, 0x00000000, 1.0f, 0.0f,
		-30.0f, 30.0f, 0x00000000, 0.0f, 0.0f);
	pObj2->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pObj2->pMesh, "fail to create object!!");

	pObj2->texture = AEGfxTextureLoad("Resources/Player.png");
	AE_ASSERT_MESG(pObj2->texture, "Failed to create texture1!!");

	
}

void Player::Player_Movement()
{
	if (Movement_Down)
	{
		Velocity.x = 0;
		Velocity.y = 1;
	}
	else if (Movement_Jump)
	{
		Velocity.x = 0;
		Velocity.y = -1;
	}
	else if (Movement_Left)
	{
		Velocity.x = -1;
		Velocity.y = 0;
	}
	else if (Movement_Right)
	{
		Velocity.x = 1;
		Velocity.y = 0;
	}
	else if (Movement_Slide && Movement_Right)
	{
		//call for shaperner
	}
	else if (Movement_Slide & Movement_Left)
	{
		//call for sharpner
	}

}

void Player::Player_Draw()
{
	// Drawing object 2 - (first) - No tint
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	// Set position for object 2
	AEGfxSetPosition(100.0f, -60.0f);
	// No tint
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

	AEGfxTextureSet(pObj2->texture, 0, 0);		// Same object, different texture

	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(pObj2->pMesh, AE_GFX_MDM_TRIANGLES);
	// Set Transparency
	AEGfxSetTransparency(1.0f);
}


void Player::Player_Init()
{
	
	//setting player position, velocity
	Position.x = 10;
	Position.y = 10;
	Velocity.x = 0;
	Velocity.y = 0;
	
}

void Player::Player_Update()
{
}

void Player::Player_Exit()
{
}