#pragma once
#include <utility/aabb_utility.h>
#include <entity/moving_entity.h>
#include <array>

class Entity;

class Ball : public MovingEntity {
public:
	Ball(float position_x, float position_y, float width, float height, Color color, std::string name, float speed, SDL_Texture* texture);

	void Update(const Game& game, const PlayState& state) override;
	void OnHit(Hit hit_result, std::weak_ptr<Entity> other_entity) override;

	void Render(const std::unique_ptr<Window>& window) override;

private:
	
	void UpdateTrail();

	std::array<Vector2, 3> trail_pos;

	float m_dir_x;
	float m_dir_y;
};