#pragma once
/* Start Header ************************************************************************/
/*!
\file Animation.h
\team name Don't Peak
\software name I don't want to do homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief
In this file, it contains the declaration of
functions found in Animation.cpp


Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/
#include "Main.h"
#include "GameState_DontPeek.h"

class Sprite
{
private:
	float spritesheet_width;
	int max_frame;
	int curr_frame;
	float duration;
	float counter;
	AEMtx33	Transform;
public:
	/******************************************************************************/
	/*!
		Animation Load
		\brief Loads textures into the game based on their spritesheet
		\param GameObj* txtObj
			This pointer holds the texture and type of the object
		\param const char* filename
			This is the direction to the spritesheet in the folder
		\param float spritesheetWidth
			This is the width
		\param TYPE type of object
	*/
	/******************************************************************************/
	void Anim_Load( GameObj* txtObj ,const char* filename, float spritesheetWidth, TYPE type);
	/******************************************************************************/
	/*!
		Animation Init
		\brief Initialises variables in the class
		\param int maxframe
			This holds the maximum number of frames
		\param float time
			This is the direction to the spritesheet in the folder
	*/
	/******************************************************************************/
	void Anim_Init(int maxframe, float time);
	/******************************************************************************/
	/*!
		Animation Update
		\brief Updates frames based on a timer
		\param GameObj* txtObj
			This holds the textures
		\param AEMtx33 transform
			This holds the transform matrix
	*/
	/******************************************************************************/
	void Anim_Update(GameObj* txtObj, AEMtx33 transform);
	/******************************************************************************/
	/*!
		Animation Free
	*/
	/******************************************************************************/
	void Anim_Free();
	/******************************************************************************/
	/*!
		Animation Unload
		\brief Unloads textures
		\param GameObj* txtObj
			This holds the textures
	*/
	/******************************************************************************/
	void Anim_Unload(GameObj* txtObj);
};
