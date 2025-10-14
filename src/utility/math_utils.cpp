#include "math_utils.h"

void ReflectVector(float& vec_x, float& vec_y, float normal_x, float normal_y) {

	float dot = vec_x * normal_x + vec_y * normal_y;

	vec_x = vec_x - 2.0f * dot * normal_x;
	vec_y = vec_y - 2.0f * dot * normal_y;
}
