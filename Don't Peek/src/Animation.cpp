#include"Animation.h"
#include<iostream>

void Sprite::Anim_Load(GameObj* txtObj, const char* filename, float spritesheetWidth, TYPE type)
{
	txtObj->type = type;
	spritesheet_width = spritesheetWidth;

	txtObj->texture = AEGfxTextureLoad(filename);
	AE_ASSERT_MESG(txtObj->texture, "Failed to load Player!");

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
void Sprite::Anim_Init(int maxframe, float time)
{
	max_frame = maxframe;
	duration = time;
	curr_frame = 0;
	counter = 0.f;
}
void Sprite::Anim_Update(GameObj* txtObj, AEMtx33 transform)
{
	counter += g_dt;
	Transform = transform;
	if (curr_frame < max_frame && txtObj)
	{
		std::cout << "print" << std::endl;
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
void Sprite::Anim_Unload(GameObj* txtObj)
{
	AEGfxTextureUnload(txtObj->texture);
	AEGfxMeshFree(txtObj->pMesh);
}