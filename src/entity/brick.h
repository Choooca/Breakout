#pragma once
#include <entity/entity.h>

class EntityFactory;

class Brick : public Entity {
public:

	Brick(float position_x, float position_y, float width, float height, SDL_Color color, std::string name, SDL_Texture* texture, bool indestrutible, int health_point);

	void OnHit(Hit hit_result, std::shared_ptr<Entity> other_entity, const std::unique_ptr<EntityFactory>& entity_factory, const Game& game) override;

private:
	
	void HitAnim(float duration = 1.0f);
	void DeathAnim(float duration = 1.0f, float max_scale_factor = 1.1f);

	bool m_indestrutible = false;

	int m_health_point;
};