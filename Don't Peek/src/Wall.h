#pragma once
/* Start Header ************************************************************************/
/*!
\file Walls.h
\team name Don't Peak
\software name I don't want to do homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief <give a brief description of this file>


Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/


/*enum for stages*/
enum gStage {
	TUTORIAL
} currentStage;

/*enum for Wall type*/
enum WallType {
	WALL,
	PLATFORM,
	UNUSED
} WallType;

//use for vectors
struct Vec
{
	float x, y;
};

//things needed for walls
class Wall
{
	//GameObj* pObject;	// pointer to the 'original' shape
	unsigned long flag;		// bit flag or-ed together
	Vec position;
	Vec direction;
	float width;
	float height;
	bool active;
	size_t collider;
	int type;

public:
	Wall(); // default constructor
	~Wall(); // destructor

	bool GetActive();
	void CreateWall(int count, Wall wallArr[], Vec direction, Vec pos, int type); // creates wall based on how many ya wan

	//void Wall_Load(void);
	void Wall_Init(void);
	void Wall_Render(void);
	void Wall_Update(void);
	void Wall_Exit(void);
};
