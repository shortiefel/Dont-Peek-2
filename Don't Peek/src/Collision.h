/* Start Header ************************************************************************/
/*!
\file Collision.h
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
#pragma once

#include "Main.h"



struct AABB
{
	AEVec2	min;
	AEVec2	max;
};

bool CollisionIntersection_RectRect(const AABB& aabb1, const AEVec2& vel1,
	const AABB& aabb2, const AEVec2& vel2);
//void BoundingBox();

//bool CollisionIntersection_PointLine(const AEVec2& point, const AEVec2& vel1,
	//const AEVec2& line, const AEVec2& vel2);

bool CollisionIntersection_PointRect(const AEVec2& point, const AEVec2& vel1,
	const AABB& Rect, const AEVec2& vel2);