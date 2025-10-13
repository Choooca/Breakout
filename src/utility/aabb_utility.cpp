#include "aabb_utility.h"
#include <cmath>

bool PointCollideAABB(const Vector2 point, const AABB aabb) {
	if (point.m_x >= aabb.m_x - aabb.m_half_width &&
		point.m_x <= aabb.m_x + aabb.m_half_width &&
		point.m_y >= aabb.m_y - aabb.m_half_height &&
		point.m_y <= aabb.m_y + aabb.m_half_height) return true;

	return false;
}

AABB MinkowskiDifference(const AABB a, const AABB b) {
	AABB ret;
	ret.m_x = a.m_x - b.m_x;
	ret.m_y = a.m_y - b.m_y;

	ret.m_half_width = a.m_half_width + b.m_half_width;
	ret.m_half_height = a.m_half_height + b.m_half_height;

	return ret;
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
