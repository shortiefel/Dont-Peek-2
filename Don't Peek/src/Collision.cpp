/* Start Header ************************************************************************/
/*!
\file Collision.cpp
\team name Don't Peak
\software name I don't want to do homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/02/2021
\brief <give a brief description of this file>


Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#include "Collision.h"
#include "GameState_DontPeek.h"


bool CollisionIntersection_RectRect(const AABB& aabb1, const AEVec2& vel1,
	const AABB& aabb2, const AEVec2& vel2)
{
	/*
	Step 1: Check for static collision detection between rectangles (before moving).
				If the check returns no overlap you continue with the following next steps (dynamics).
				Otherwise you return collision true
	*/
	if (aabb1.max.x < aabb2.min.x || aabb1.max.y < aabb2.min.y ||
		aabb1.min.x > aabb2.max.x || aabb1.min.y > aabb2.max.y)
	{
	}
	else
		return 1;
	/*
	Step 2: Initialize and calculate the new velocity of Vb
			tFirst = 0
			tLast = dt
	*/
	float tfirst{ 0.0f };
	float tLast{ g_dt };
	/*
	Step 3: Working with one dimension (x-axis).
			if(Vb < 0)
				case 1
				case 4
			if(Vb > 0)
				case 2
				case 3

			case 5
	*/
	float velocity = vel2.x - vel1.x;
	if (velocity < 0)
	{
		if (aabb1.min.x > aabb2.max.x)
			return 0;
		if (aabb1.max.x < aabb2.min.x)
			tfirst = AEMax((aabb1.max.x - aabb2.min.x) / velocity, tfirst);
		if (aabb1.min.x < aabb2.max.x)
			tLast = AEMin((aabb1.min.x - aabb2.max.x) / velocity, tLast);
	}

	else if (velocity > 0)
	{
		if (aabb1.max.x < aabb2.min.x)
			return 0;
		if (aabb1.min.x > aabb2.max.x)
			tfirst = AEMax((aabb1.min.x - aabb2.max.x) / velocity, tfirst);
		if (aabb1.max.x > aabb2.min.x)
			tLast = AEMin((aabb1.max.x - aabb2.min.x) / velocity, tLast);
	}
	//Step 4: Repeat step 3 on the y-axis
	velocity = vel2.y - vel1.y;

	if (velocity < 0)
	{
		if (aabb1.min.y > aabb2.max.y)
			return 0;
		if (aabb1.max.y < aabb2.min.y)
			tfirst = AEMax((aabb1.max.y - aabb2.min.y) / velocity, tfirst);
		if (aabb1.min.y < aabb2.max.y)
			tLast = AEMin((aabb1.min.y - aabb2.max.y) / velocity, tLast);
	}
	else if (velocity > 0)
	{
		if (aabb1.max.y < aabb2.min.y)
			return 0;
		if (aabb1.min.y > aabb2.max.y)
			tfirst = AEMax((aabb1.min.y - aabb2.max.y) / velocity, tfirst);
		if (aabb1.max.y > aabb2.min.y)
			tLast = AEMin((aabb1.max.y - aabb2.min.y) / velocity, tLast);
	}
	//Step 5: Otherwise the rectangles intersect
	if (tfirst > tLast)
		return 0;

	return 1;
}
void BoundingBox()
{
	for (unsigned int i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInst* pInst = sGameObjInstList + i;

		if ((pInst->flag & FLAG_ACTIVE) == 0)
			continue;

		pInst->boundingBox.min.x = pInst->posCurr.x - pInst->scale / 2;
		pInst->boundingBox.min.y = pInst->posCurr.y - pInst->scale / 2;
		pInst->boundingBox.max.x = pInst->posCurr.x + pInst->scale / 2;
		pInst->boundingBox.max.y = pInst->posCurr.y + pInst->scale / 2;
		//printf("Create %lu", i);
	}
}