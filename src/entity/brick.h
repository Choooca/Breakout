#pragma once
#include <entity/entity.h>

class EntityFactory;

class Brick : public Entity {
public:

	Brick(Vector2 position, Vector2 size, SDL_Color color, std::string name, SDL_Texture* texture, bool indestrutible, int health_point, int score);

	void OnHit(Hit hit_result, std::shared_ptr<Entity> other_entity) override;

private:
	
	void HitAnim(float duration = 1.0f);
	void DeathAnim(float duration = 1.0f, float max_scale_factor = 1.1f);

	bool m_indestrutible = false;

	int m_health_point;
	int m_base_health_point;
	int m_score;
};