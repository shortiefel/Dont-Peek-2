#pragma once

#include "Main.h"


class Camera
{
public:
	void initCamera();
	void updateCamera();
	void exitCamera();

private:
	AEVec2 pos{ 0, 0 };
	AEVec2 movement;
	
};