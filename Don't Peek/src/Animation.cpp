/* Start Header ************************************************************************/
/*!
\file Animation.cpp
\team name Don't Peak
\software name I don't want to do homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief
This file contains all the functions that is required for our animations.


Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/
#include"Animation.h"
#include<iostream>

/******************************************************************************/
/*!
	Animation Load
*/
/******************************************************************************/
void Sprite::Anim_Load(GameObj* txtObj, const char* filename, float spritesheetWidth, TYPE type)
{
	txtObj->type = type;
	spritesheet_width = spritesheetWidth;

	txtObj->texture = AEGfxTextureLoad(filename);
	AE_ASSERT_MESG(txtObj->texture, "Failed to load Texture!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, spritesheet_width, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, spritesheet_width, 1.0f,
		0.5f, 0.5f, 0x00000000, spritesheet_width, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	txtObj->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(txtObj->pMesh, "fail to create object!!");
}

/******************************************************************************/
/*!
	Animation Init
*/
/******************************************************************************/
void Sprite::Anim_Init(int maxframe, float time)
{
	max_frame = maxframe;
	duration = time;
	curr_frame = 0;
	counter = 0.f;
}

/******************************************************************************/
/*!
	Animation Update
*/
/******************************************************************************/
void Sprite::Anim_Update(GameObj* txtObj, AEMtx33 transform)
{
	counter += g_dt;
	Transform = transform;
	if (curr_frame < max_frame && txtObj)
	{
		//std::cout << "print" << std::endl;
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);

		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(0.f, 0.f);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxTextureSet(txtObj->texture, curr_frame * spritesheet_width, 0);		// Same object, different texture
		AEGfxSetTransform(Transform.m);

		AEGfxSetTransparency(1.0f);
		AEGfxMeshDraw(txtObj->pMesh, AE_GFX_MDM_TRIANGLES);
	}
	if (counter > duration)
	{
		//std::cout << "curr frame: " << curr_frame << std::endl;
		curr_frame++;
		counter = 0.f;
	}

	if (curr_frame == max_frame)
		curr_frame = 0;
}

/******************************************************************************/
/*!
	Animation Free
*/
/******************************************************************************/
void Sprite::Anim_Free()
{

}

/******************************************************************************/
/*!
	Animation Unload
*/
/******************************************************************************/
void Sprite::Anim_Unload(GameObj* txtObj)
{
	AEGfxTextureUnload(txtObj->texture);
	AEGfxMeshFree(txtObj->pMesh);
}