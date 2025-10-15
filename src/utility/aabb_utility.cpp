#include "aabb_utility.h"
#include <graphics/window.h>
#include <cmath>

bool PointCollideAABB(const Vector2 point, const AABB aabb) {
	if (point.x > aabb.x - aabb.m_half_width &&
		point.x < aabb.x + aabb.m_half_width &&
		point.y > aabb.y - aabb.m_half_height &&
		point.y < aabb.y + aabb.m_half_height) return true;

	return false;
}
//
//Hit AABBCollideAABB(const AABB a, const AABB b) {
//	Hit ret = { false, {0,0} };
//
//	AABB minkownski_aabb = MinkowskiDifference(a, b);
//
//	if (!PointCollideAABB({ 0, 0 }, minkownski_aabb)) return ret;
//
//	ret.is_hit = true;
//	ret.penetration_vector = AABBPenetrationVector(minkownski_aabb);
//
//	return ret;
//}

Vector2 AABBPenetrationVector(AABB aabb) {
	Vector2 min, max;
	min.x = aabb.x - aabb.m_half_width;
	max.x = aabb.x + aabb.m_half_width;
	min.y = aabb.y - aabb.m_half_height;
	max.y = aabb.y + aabb.m_half_height;

	Vector2 pv;

	float min_dist = std::abs(min.x);
	pv = { min.x, 0.0f };

	if (std::abs(max.x) < min_dist) {
		min_dist = std::abs(max.x);
		pv = { max.x, 0.0f };
	}

	if (std::abs(min.y) < min_dist) {
		min_dist = std::abs(min.y);
		pv = { 0.0f, min.y };
	}

	if (std::abs(max.y) < min_dist) {
		min_dist = std::abs(max.y);
		pv = { 0.0f, max.y };
	}

	return pv;
}

AABB MinkowskiDifference(const AABB a, const AABB b) {
	AABB ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;

	ret.m_half_width = a.m_half_width + b.m_half_width;
	ret.m_half_height = a.m_half_height + b.m_half_height;

	return ret;
}


Hit SweepStaticMovingAABB(AABB moving_aabb, Vector2 velocity, AABB static_aabb) {
	if (velocity.x == 0 && velocity.y == 0) {
		return { 0 };
	}

	AABB sum_aabb = MinkowskiDifference(static_aabb, moving_aabb);

	float x_entry, x_exit, y_entry, y_exit;

	if (velocity.x > 0) {
		x_entry = (sum_aabb.x - sum_aabb.m_half_width) / velocity.x;
		x_exit = (sum_aabb.x + sum_aabb.m_half_width) / velocity.x;
	}
	else if (velocity.x < 0) {
		x_entry = (sum_aabb.x + sum_aabb.m_half_width) / velocity.x;
		x_exit = (sum_aabb.x - sum_aabb.m_half_width) / velocity.x;
	}
	else {
		if (std::abs(sum_aabb.x) > sum_aabb.m_half_width) return{ 0 };
		x_entry = -INFINITY;
		x_exit = INFINITY;
	}

	if (velocity.y > 0) {
		y_entry = (sum_aabb.y - sum_aabb.m_half_height) / velocity.y;
		y_exit = (sum_aabb.y + sum_aabb.m_half_height) / velocity.y;
	}
	else if (velocity.y < 0) {
		y_entry = (sum_aabb.y + sum_aabb.m_half_height) / velocity.y;
		y_exit = (sum_aabb.y - sum_aabb.m_half_height) / velocity.y;
	}
	else {
		if (std::abs(sum_aabb.y) > sum_aabb.m_half_height) return{ 0 };
		y_entry = -INFINITY;
		y_exit = INFINITY;
	}

	float last_entry = std::max(x_entry, y_entry);
	float first_exit = std::min(x_exit, y_exit);

	if (last_entry >= first_exit ||
		(x_entry <= 0 && y_entry <= 0) ||
		last_entry >= 1 ||
		last_entry <= 0) return { 0 };

	Vector2 normal;
	if (x_entry > y_entry) {
		normal.y = 0;
		normal.x = velocity.x > 0 ? -1 : 1;
	}
	else {
		normal.x = 0;
		normal.y = velocity.y > 0 ? -1 : 1;
	}

	return {
		true,
		last_entry,
		{moving_aabb.x + velocity.x * last_entry, moving_aabb.y + velocity.y * last_entry},
		normal
	};
}

Collision SweepMovingAABB(AABB first_moving, Vector2 first_velocity, AABB second_moving, Vector2 second_velocity) {
	Vector2 relative_velocity = {
		first_velocity.x - second_velocity.x,
		first_velocity.y - second_velocity.y
	};

	Hit hit = SweepStaticMovingAABB(first_moving, relative_velocity, second_moving);

	Collision collision = {0};
	if (hit.is_hit) {
		collision.hit = true;
		collision.A = {
			true,
			hit.collision_time,
			{first_moving.x + first_velocity.x * hit.collision_time, first_moving.y + first_velocity.y * hit.collision_time},
			{hit.normal.x * -1.0f, hit.normal.y * -1.0f}
		};
		collision.B = {
			true,
			hit.collision_time,
			{second_moving.x + second_velocity.x * hit.collision_time, second_moving.y + second_velocity.y * hit.collision_time},
			hit.normal
		};
	}

	return collision;
}

void ShowAABB(const std::unique_ptr<Window>& window, AABB aabb, int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(window->GetRenderer(), r, g, b, a);
	SDL_FRect rect = { aabb.x - aabb.m_half_width, aabb.y - aabb.m_half_height, aabb.m_half_width * 2.0f, aabb.m_half_height * 2.0f };
	SDL_RenderFillRect(window->GetRenderer(), &rect);
}