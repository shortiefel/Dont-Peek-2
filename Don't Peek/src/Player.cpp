/* Start Header ************************************************************************/
/*!
\file Player.cpp
\team name Don't Peak
\software name I don't want to do homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 04/03/2021
\brief <give a brief description of this file>


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#include "Player.h"
#include "GameState_DontPeek.h"



/******************************************************************************/
/*!
	Game Object 
*/
/******************************************************************************/

static GameObj* pObj;
static GameObjInst* player;
const int Player_Gravity = 8;
bool Gravity = true;
float GROUND = 0.f;
bool CanJump = false;

/******************************************************************************/
/*!
	Player Character
*/
/******************************************************************************/


void Player::Player_Character() //drawing of character
{
	
	pObj = sGameObjList + sGameObjNum++;
	pObj->type = TYPE_PLAYER;


	//Drawing of Player
	AEGfxMeshStart();
	AEGfxTriAdd(
		-60.0f, -60.0f, 0x00000000, 0.0f, 1.0f,
		100.0f, -60.0f, 0x00000000, 1.0f, 1.0f,
		-60.0f, 60.0f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		100.0f, -60.0f, 0x00000000, 1.0f, 1.0f,
		100.0f, 60.0f, 0x00000000, 1.0f, 0.0f,
		-60.0f, 60.0f, 0x00000000, 0.0f, 0.0f);
	pObj->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pObj->pMesh, "fail to create object!!");

	pObj->texture = AEGfxTextureLoad("Resources/Player.png");
	AE_ASSERT_MESG(pObj->texture, "Failed to create texture1!!");

	
}

void Player::SetGravity()
{
	//printf("you shit");
	//Position.y -= 2;
	//Velocity.y = sqrt((2 * Player_Gravity) * (Position.y - Position.x));
	Velocity.y -= 0.15f;

}

/******************************************************************************/
/*!
	Player Draw
*/
/******************************************************************************/

void Player::Player_Draw()
{
	// Drawing object 2 - (first) - No tint
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	// Set position for object 2
	AEGfxSetPosition(Position.x, Position.y);
	// No tint
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

	AEGfxTextureSet(pObj->texture, 0, 0);		// Same object, different texture

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(pObj->pMesh, AE_GFX_MDM_TRIANGLES);
	// Set Transparency
	AEGfxSetTransparency(1.0f);
}

/******************************************************************************/
/*!
	Player Init
*/
/******************************************************************************/

void Player::Player_Init()
{
	Velocity.x = 0;
	Velocity.y = 0;
	Position.x = 40.0f;
	Position.y = -50.f;


}

/******************************************************************************/
/*!
	Player Update
*/
/******************************************************************************/

void Player::Player_Update()
{
	
	if (AEInputCheckCurr(AEVK_LEFT))
	{
		//Position.x -= Velocity.x;
		Velocity.x = -SPEED;
	}
	else if (AEInputCheckCurr(AEVK_RIGHT))
	{
		Velocity.x = SPEED;
	}
	else
	{
		Velocity.x = 0.f;
	}
	if (AEInputCheckTriggered(AEVK_UP) && CanJump == true)
	{
		printf( "jumping \n");
		CanJump = false;
		//Position.y += Velocity.y * 4;
		Velocity.y = 5.f;
		printf("PosY: %f, %f\n", Position.x, Position.y);
	}
	
	
	if (Position.y < GROUND)
	{
		Position.y = GROUND;
		CanJump = true;
		Velocity.y = 0;
	}
	else {
		
		SetGravity();
	}

	Position.x += Velocity.x;
	Position.y += Velocity.y;
	
	
}

/******************************************************************************/
/*!
	Player Exit
*/
/******************************************************************************/
void Player::Player_Exit()
{
}