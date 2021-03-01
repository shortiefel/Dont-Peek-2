
#include "Wall.h"

void Tutorial(void)
{
	//TODO: code the wall you want
}

void Wall::Wall_Init(void)
{
	Tutorial();

	//load mesh
}

void Wall::Wall_Render(void)
{
	//tbc
	if (type == WALL)
	{
		//render certain mesh
	}
	else if (type == PLATFORM)
	{
		// render certain mesh
	}
}

void Wall::Wall_Update(void)
{
	Wall* wallPointer = NULL;
	int size = 0;


	if (currentStage == TUTORIAL) {

	}

	for (int i = 0; i < size; ++i)
	{
		if (wallPointer[i].GetActive() == false)
			continue;
		wallPointer[i].Wall_Render();
	}
}
void Wall::Wall_Exit(void)
{
	//free mesh
}