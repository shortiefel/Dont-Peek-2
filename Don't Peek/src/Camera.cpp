#include "GameState_DontPeek.h"
#include "Camera.h"
#include "Player.h"

/******************************************************************************/
/*!
	Classes & Objects
*/
/******************************************************************************/

/******************************************************************************/
/*!
	Camera Init
*/
/******************************************************************************/
void Camera::initCamera()
{
	/*if (player.GetPosPlayer().x > (f32)AEGetWindowHeight() / 2)
	{
		if (player.GetPosPlayer().y)
	}*/
}

/******************************************************************************/
/*!
	Camera Update
*/
/******************************************************************************/
void Camera::updateCamera()
{
	AEGfxSetCamPosition(player.GetPosPlayer().x, player.GetPosPlayer().y);
}
/******************************************************************************/
/*!
	Camera Exit
*/
/******************************************************************************/
void Camera::exitCamera()
{
}
 