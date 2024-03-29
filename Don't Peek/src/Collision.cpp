/* Start Header ************************************************************************/
/*!
\file Collision.cpp
\team name Don't Peek
\software name I Don't Wanna Do My Homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/02/2021
\brief 
This file contains all the functions that is required for our collision.
This is all AABB collision.
Collision between 2 rectangular object.
Collision between a point and a rectangular object.


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#include "GameState_DontPeek.h"
#include "Collision.h"


bool collideLeft = false;
bool collideRight = false;
bool collideTop = false;
bool collideBtm = false;


/******************************************************************************/
/*!
	Collision Between 2 Rectangular Object
*/
/******************************************************************************/
bool CollisionIntersection_RectRect(const AABB& aabb1, const AEVec2& vel1,
									const AABB& aabb2, const AEVec2& vel2)
{
	
	/*
	Implement the collision intersection over here.

	The steps are:
	Step 1: Check for static collision detection between rectangles (before moving).

	Step 2: Initialize and calculate the new velocity of Vb

	Step 3: Working with one dimension (x-axis).

	Step 4: Repeat step 3 on the y-axis

	Step 5: Otherwise the rectangles intersect
	*/

	//Check for static collision detection between rectangles, if collided return true
	if (aabb1.max.x < aabb2.min.x || aabb1.max.y < aabb2.min.y ||
		aabb1.min.x > aabb2.max.x || aabb1.min.y > aabb2.max.y)
	{
		return 0;
	}
	else
	{

		// Initialize and calculate the new velocity of Vb, tFirst = 0, tLast = dt
		float tFirst = 0.0f;
		float tLast = g_dt;
		float velocity = vel2.x - vel1.x;

		//cases for x-axis
		if (velocity < 0)
		{
			// if it is moving away
			if (aabb1.min.x > aabb2.max.x)
				return 0;

			if (aabb1.max.x < aabb2.min.x)
				tFirst = max((aabb1.max.x - aabb2.min.x) / velocity, tFirst);

			if (aabb1.min.x < aabb2.max.x)
				tLast = min((aabb1.min.x - aabb2.max.x) / velocity, tLast);
		}

		else if (velocity > 0)
		{
			// if it is moving away
			if (aabb1.max.x < aabb2.min.x)
				return 0;

			if (aabb1.min.x > aabb2.max.x)
				tFirst = max((aabb1.min.x - aabb2.max.x) / velocity, tFirst);

			if (aabb1.max.x > aabb2.min.x)
				tLast = min((aabb1.max.x - aabb2.min.x) / velocity, tLast);
		}


		//cases for y-axis

		velocity = vel2.y - vel1.y;

		if (velocity < 0)
		{
			// if it is moving away
			if (aabb1.min.y > aabb2.max.y)
				return 0;

			if (aabb1.max.y < aabb2.min.y)
				tFirst = max((aabb1.max.y - aabb2.min.y) / velocity, tFirst);

			if (aabb1.min.y < aabb2.max.y)
				tLast = min((aabb1.min.y - aabb2.max.y) / velocity, tLast);
		}

		else if (velocity > 0)
		{
			// if it is moving away
			if (aabb1.max.y < aabb2.min.y)
				return 0;

			if (aabb1.min.y > aabb2.max.y)
				tFirst = max((aabb1.min.y - aabb2.max.y) / velocity, tFirst);

			if (aabb1.max.y > aabb2.min.y)
				tLast = min((aabb1.max.y - aabb2.min.y) / velocity, tLast);
		}

		//if the rectangles intersects
		if (tFirst > tLast)
			return 0;

		return 1;

	}
}

/******************************************************************************/
/*!
	Collision Between A Point And A Rectangular Object [Used for mouse clicking]
*/
/******************************************************************************/
bool CollisionIntersection_PointRect(const AEVec2& point, const AEVec2& vel1,
	const AABB& Rect, const AEVec2& vel2)
{
	if ((point.x < Rect.min.x || point.x > Rect.max.x) || (point.y < Rect.min.y || point.y > Rect.max.y))
	{
		return 0;
	}
	else
		return 1;
}