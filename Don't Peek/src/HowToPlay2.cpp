/* Start Header************************************************************************ /
/*!
\file HowToPlay2.cpp
\team name Don't Peek
\software name I Don't Wanna Do My Homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu
\date 22/01/2021
\brief <give a brief description of this file>

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#include "Howtoplay2.h"
#include "Door.h"
#include "Player.h"
#include "Sharpener.h"
#include "Eraser.h"
#include "Highlighter.h"
#include "Pencil.h"
#include "Wall.h"
#include "Tutorial.h"
#include "Win.h"
#include "Pause.h"
#include "Music.h"

void HowtoplayLoad(void)
{
	PauseLoad();
	Tutorial_Load();
	wall.LoadWall();
	sharpener.LoadSharpener();
	eraser.LoadEraser();
	highlighter.LoadHighlighter();
	pencil.LoadPencil();
	door.LoadDoor();
	player.Player_Load();
}

void HowtoplayInit(void)
{
	SoundSystem_Init();
	SoundSystem_SFX();
	Tutorial_Init();
	wall.InitWall();
	sharpener.InitSharpener();
	eraser.InitEraser();
	highlighter.InitHighlighter();
	pencil.InitPencil();
	door.InitDoor();
	player.Player_Init();
}

void HowtoplayUpdate(void)
{
	if (AEInputCheckCurr(AEVK_P))
	{
		CheckPause = true;
	}

	if (CheckPause == true)
	{
		PauseUpdate();
	}
	else if (CheckPause == false)
	{
		Tutorial_Update();
		wall.UpdateWall();
		sharpener.UpdateSharpener();
		eraser.UpdateEraser();
		highlighter.UpdateHighlighter();
		pencil.UpdatePencil();
		door.UpdateDoor();
		player.Player_Update();
	}
}

void HowtoplayDraw(void)
{
	if (CheckPause == true)
	{
		PauseDraw();
	}
	else if (CheckPause == false)
	{
		Tutorial_Draw();
		wall.DrawWall();
		highlighter.DrawHighlighter();
		pencil.DrawPencil();
		sharpener.DrawSharpener();
		eraser.DrawEraser();
		door.DrawDoor();
		player.Player_Draw();
	}
}

void HowtoplayFree(void)
{
	SoundSystem_Destroy();
	//printf("TUT IS FREEING\n");
	Tutorial_Free();
	wall.FreeWall();
	sharpener.FreeSharpener();
	eraser.FreeEraser();
	highlighter.FreeHighlighter();
	pencil.FreePencil();
	door.FreeDoor();
	player.Player_Free();
	
}

void HowtoplayUnload(void)
{
	
	PauseUnload();
	//printf("TUT IS UNLOADING\n");
	Tutorial_Unload();
	wall.UnloadWall();
	sharpener.UnloadSharpener();
	eraser.UnloadEraser();
	highlighter.UnloadHighlighter();
	pencil.UnloadPencil();
	door.UnloadDoor();
	player.Player_Unload();
}
