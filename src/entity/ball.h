#pragma once
#include <utility/aabb_utility.h>
#include <entity/moving_entity.h>
#include <array>

class Entity;
struct Vector2;

class Ball : public MovingEntity {
public:
	Ball(Vector2 position, Vector2 size, SDL_Color color, std::string name, float speed, SDL_Texture* texture);

	void Update(const std::unique_ptr<InputHandler>& input_handler, int window_height) override;
	void OnHit(Hit hit_result, std::shared_ptr<Entity> other_entity) override;

	void Render(const std::unique_ptr<Window>& window) override;

	void SetRandomDir();
	void SetDir(Vector2 dir);
private:
	
	void UpdateTrail();

	std::array<Vector2, 3> trail_pos;

	float m_dir_x;
	float m_dir_y;

	void NormalizeDir();
};