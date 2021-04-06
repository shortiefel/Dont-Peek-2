#include"Animation.h"
#include<iostream>

GameObj* txtObj;
static float counter;
static float width = 1.f / 3.f;

void Sprite::Anim_Load()
{
	txtObj = sGameObjList + sGameObjNum++;
	txtObj->type = TYPE_PLAYER;

	txtObj->texture = AEGfxTextureLoad("Resources/idle sprite sheet 1800 x 600 72dpi.png");
	AE_ASSERT_MESG(txtObj->texture, "Failed to load Player!");

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00000000, width, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00000000, width, 1.0f,
		0.5f, 0.5f, 0x00000000, width, 0.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f);
	txtObj->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(txtObj->pMesh, "fail to create object!!");
}
void Sprite::Anim_Init()
{
	max_frame = 3;
	duration = .2f;
	curr_frame = 0;
	counter = 0.f;

	AEMtx33 Transform2, Size;
	AEMtx33Scale(&Size, 130, 130);
	AEMtx33Trans(&Transform2, 0, 0);
	AEMtx33Concat(&(Transform), &Transform2, &Size);
}
void Sprite::Anim_Update()
{
	counter += g_dt;
	if (curr_frame < max_frame)
	{
		std::cout << "print" << std::endl;
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);

		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(0.f, 0.f);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxTextureSet(txtObj->texture, curr_frame * width, 0);		// Same object, different texture
		AEGfxSetTransform(Transform.m);

		AEGfxSetTransparency(1.0f);
		AEGfxMeshDraw(txtObj->pMesh, AE_GFX_MDM_TRIANGLES);
	}
	if (counter > duration)
	{
		std::cout << "curr frame: " << curr_frame << std::endl;
		curr_frame++;
		counter = 0.f;
	}

	if (curr_frame == max_frame)
		curr_frame = 0;
}
void Sprite::Anim_Free()
{

}
void Sprite::Anim_Unload()
{
	AEGfxTextureUnload(txtObj->texture);
	AEGfxMeshFree(txtObj->pMesh);
}