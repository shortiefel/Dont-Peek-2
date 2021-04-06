#pragma once
#include "Main.h"
#include "GameState_DontPeek.h"

class Sprite
{
private:
	int max_frame;
	int curr_frame;
	//float frame_width, frame_height;
	float duration;
	AEMtx33	Transform;
public:
	void Anim_Load();
	void Anim_Init();
	void Anim_Update();
	void Anim_Free();
	void Anim_Unload();
};
