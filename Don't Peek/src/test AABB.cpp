#include "test AABB.h"

static GameObj* ptesting;

void loadtesting()
{
	AEGfxMeshStart();
	AEGfxTriAdd(
		5.f, -5.f, 0x0000000, 0.0f, 0.0f,
		5.f, -5.f, 0x0000000, 0.0f, 0.0f,
		-5.f, 5.f, 0x0000000, 0.0f, 0.0f);
	ptesting->pMesh = AEGfxMeshEnd();
}

void drawbox(AABB boundingbox)
{
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	// Set the current object instance's transform matrix using "AEGfxSetTransform"
	AEGfxSetPosition(boundingbox.min.x, boundingbox.min.y);
	// Draw the shape used by the current object instance using "AEGfxMeshDraw"
	AEGfxMeshDraw(ptesting->pMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	// Set the current object instance's transform matrix using "AEGfxSetTransform"
	AEGfxSetPosition(boundingbox.max.x, boundingbox.max.y);
	// Draw the shape used by the current object instance using "AEGfxMeshDraw"
	AEGfxMeshDraw(ptesting->pMesh, AE_GFX_MDM_TRIANGLES);
}