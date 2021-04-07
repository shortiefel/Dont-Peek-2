#pragma once
#include "Main.h"
#include "GameState_DontPeek.h"

class Sprite
{
private:
	float spritesheet_width;
	int max_frame;
	int curr_frame;
	//float frame_width, frame_height;
	float duration;
	float counter;
	AEMtx33	Transform;
public:
	void Anim_Load( GameObj* txtObj ,const char* filename, float spritesheetWidth, TYPE type);
	void Anim_Init(int maxframe, float time);
	void Anim_Update(GameObj* txtObj, AEMtx33 transform);
	void Anim_Free();
	void Anim_Unload(GameObj* txtObj);
};
