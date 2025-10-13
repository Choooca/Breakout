#include "aabb_utility.h"
#include <cmath>

bool PointCollideAABB(const Vector2 point, const AABB aabb) {
	if (point.m_x > aabb.m_x - aabb.m_half_width &&
		point.m_x < aabb.m_x + aabb.m_half_width &&
		point.m_y > aabb.m_y - aabb.m_half_height &&
		point.m_y < aabb.m_y + aabb.m_half_height) return true;

	return false;
}

Hit AABBCollideAABB(const AABB a, const AABB b) {
	Hit ret = { false, {0,0} };

	AABB minkownski_aabb = MinkowskiDifference(a, b);

	if (!PointCollideAABB({ 0, 0 }, minkownski_aabb)) return ret;

	ret.is_hit = true;
	ret.penetration_vector = AABBPenetrationVector(minkownski_aabb);

	return ret;
}

Vector2 AABBPenetrationVector(AABB aabb) {
	Vector2 min, max;
	min.m_x = aabb.m_x - aabb.m_half_width;
	max.m_x = aabb.m_x + aabb.m_half_width;
	min.m_y = aabb.m_y - aabb.m_half_height;
	max.m_y = aabb.m_y + aabb.m_half_height;

	Vector2 pv;

	float min_dist = std::abs(min.m_x);
	pv = { min.m_x, 0.0f };

	if (std::abs(max.m_x) < min_dist) {
		min_dist = std::abs(max.m_x);
		pv = { max.m_x, 0.0f };
	}

	if (std::abs(min.m_y) < min_dist) {
		min_dist = std::abs(min.m_y);
		pv = { 0.0f, min.m_y };
	}

	if (std::abs(max.m_y) < min_dist) {
		min_dist = std::abs(max.m_y);
		pv = { 0.0f, max.m_y };
	}

	return pv;
}

AABB MinkowskiDifference(const AABB a, const AABB b) {
	AABB ret;
	ret.m_x = a.m_x - b.m_x;
	ret.m_y = a.m_y - b.m_y;

	ret.m_half_width = a.m_half_width + b.m_half_width;
	ret.m_half_height = a.m_half_height + b.m_half_height;

	return ret;
}


Hit SweepStaticMovingAABB(AABB moving_aabb, Vector2 velocity, AABB static_aabb) {
	if (velocity.m_x == 0 && velocity.m_y == 0) {
		return { 0 };
	}

	AABB sum_aabb = MinkowskiDifference(static_aabb, moving_aabb);

	float x_entry, x_exit, y_entry, y_exit;

	if (velocity.m_x > 0) {
		x_entry = (sum_aabb.m_x - sum_aabb.m_half_width) / velocity.m_x;
		x_exit = (sum_aabb.m_x + sum_aabb.m_half_width) / velocity.m_x;
	}
	else if (velocity.m_x < 0) {
		x_entry = (sum_aabb.m_x + sum_aabb.m_half_width) / velocity.m_x;
		x_exit = (sum_aabb.m_x - sum_aabb.m_half_width) / velocity.m_x;
	}
	else {
		x_entry = -INFINITY;
		x_exit = INFINITY;
	}

	if (velocity.m_y > 0) {
		y_entry = (sum_aabb.m_y - sum_aabb.m_half_height) / velocity.m_y;
		y_exit = (sum_aabb.m_y + sum_aabb.m_half_height) / velocity.m_y;
	}
	else if (velocity.m_y < 0) {
		y_entry = (sum_aabb.m_y + sum_aabb.m_half_height) / velocity.m_y;
		y_exit = (sum_aabb.m_y - sum_aabb.m_half_height) / velocity.m_y;
	}
	else {
		y_entry = -INFINITY;
		y_exit = INFINITY;
	}

	float last_entry = std::max(x_entry, y_entry);
	float first_exit = std::min(x_exit, y_exit);

	if (last_entry > first_exit ||
		(x_entry < 0 && y_entry < 0) ||
		last_entry > 1 ||
		last_entry < 0) return { 0 };

	Vector2 normal;
	if (x_entry > y_entry) {
		normal.m_y = 0;
		normal.m_x = velocity.m_x > 0 ? -1 : 1;
	}
	else {
		normal.m_x = 0;
		normal.m_y = velocity.m_y > 0 ? -1 : 1;
	}

	return {
		true,
		last_entry,
		{moving_aabb.m_x + velocity.m_x * last_entry, moving_aabb.m_y + velocity.m_y * last_entry},
		normal
	};
}

Collision SweepMovingAABB(AABB first_moving, Vector2 first_velocity, AABB second_moving, Vector2 second_velocity) {
	Vector2 relative_velocity = {
		first_velocity.m_x - second_velocity.m_x,
		first_velocity.m_y - second_velocity.m_y
	};

	Hit hit = SweepStaticMovingAABB(first_moving, relative_velocity, second_moving);

	Collision collision = {0};
	if (hit.is_hit) {
		collision.hit = true;
		collision.A = {
			true,
			hit.collision_time,
			{first_moving.m_x + first_velocity.m_x * hit.collision_time, first_moving.m_y + first_velocity.m_y * hit.collision_time},
			hit.normal
		};
		collision.B = {
			true,
			hit.collision_time,
			{second_moving.m_x + second_velocity.m_x * hit.collision_time, second_moving.m_y + second_velocity.m_y * hit.collision_time},
			{hit.normal.m_x * -1.0f, hit.normal.m_y * -1.0f}
		};
	}

	return collision;
}

void ShowAABB(const std::unique_ptr<Window>& window, AABB aabb, int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(window->GetRenderer(), r, g, b, a);
	SDL_FRect rect = { aabb.m_x - aabb.m_half_width, aabb.m_y - aabb.m_half_height, aabb.m_half_width * 2.0f, aabb.m_half_height * 2.0f };
	SDL_RenderFillRect(window->GetRenderer(), &rect);
}