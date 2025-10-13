#pragma once
#include <entity/entity.h>
#include <memory>

struct AABB {
	float m_x;
	float m_y;
	float m_half_width;
	float m_half_height;
};

struct Vector2 {
	float m_x;
	float m_y;
};

bool PointCollideAABB(const Vector2 point, const AABB aabb);

AABB MinkowskiDifference(const AABB a, const AABB b);
bool AABBCollideAABB(const AABB a,const AABB b);
Vector2 AABBPenetrationVector(AABB aabb);
