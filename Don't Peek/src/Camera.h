#pragma once

#include "Main.h"


class Camera
{
public:
	void initCamera();
	void updateCamera();
	void exitCamera();
	int MinX = AEGfxGetWinMinX();
	int MinY = AEGfxGetWinMinY();
	int MaxX = AEGfxGetWinMaxX();
	int MaxY = AEGfxGetWinMaxY();

private:
	AEVec2 pos{ 0, 0 };
	AEVec2 movement;
	


	
};