#pragma once
#include <entity/entity.h>

class Brick : public Entity {
public:

	Brick(float position_x, float position_y, float width, float height, Color color, std::string name, SDL_Texture* texture, bool indestrutible, int health_point);

	void OnHit(Hit hit_result, std::weak_ptr<Entity> other_entity) override;

private:
	
	void HitAnim(float duration = 1.0f);
	void DeathAnim(float duration = 1.0f, float max_scale_factor = 1.1f);

	bool m_indestrutible = false;

	int m_health_point;
};