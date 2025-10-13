#pragma once
#include <memory>
#include <render/window.h>

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
	float collision_time;
	Vector2 collision_point;
	Vector2 normal;
};

struct Collision {
	bool hit;
	Hit A;
	Hit B;
};

bool PointCollideAABB(const Vector2 point, const AABB aabb);

AABB MinkowskiDifference(const AABB a, const AABB b);
//Hit AABBCollideAABB(const AABB a,const AABB b);
Vector2 AABBPenetrationVector(AABB aabb);
Collision SweepMovingAABB(AABB first_moving, Vector2 first_velocity, AABB second_moving, Vector2 second_velocity);
Hit SweepStaticMovingAABB(AABB moving_aabb, Vector2 velocity, AABB static_aabb);

void ShowAABB(const std::unique_ptr<Window> &window ,AABB aabb, int r, int g, int b, int a);

