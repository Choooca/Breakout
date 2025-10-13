#pragma once
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

struct Hit {
	bool is_hit;
	Vector2 penetration_vector;
};

bool PointCollideAABB(const Vector2 point, const AABB aabb);

AABB MinkowskiDifference(const AABB a, const AABB b);
Hit AABBCollideAABB(const AABB a,const AABB b);
Vector2 AABBPenetrationVector(AABB aabb);
