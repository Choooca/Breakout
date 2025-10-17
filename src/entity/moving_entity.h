#pragma once
#include<entity/entity.h>
#include <SDL3/SDL.h>

class MovingEntity : public Entity {
public:

	MovingEntity(Vector2 position, Vector2 size, SDL_Color color, std::string name, float speed, SDL_Texture* texture);

	inline Vector2 GetVelocity() { return m_velocity; };

	void OnHit(Hit hit_result, std::shared_ptr<Entity> other_entity) override;

	void SetUpdateEnable(bool is_enable) override;

protected:

	float m_speed;
	Vector2 m_velocity;
	
};