#pragma once
#include <memory>
#include <entity/moving_entity.h>
#include <map>

class PlayState;
class Entity;
class Game;
class InputHandler;

class Paddle : public MovingEntity {
public:
	Paddle(Vector2 position, Vector2 size, SDL_Color color, std::string name, float speed, SDL_Texture* texture);

	void Update(const std::unique_ptr<InputHandler>& input_handler, int window_height) override;

	void ModifyBallDirection(float &dir_x, float &dir_y, const Hit& hit_result) override;

	void Render(const std::unique_ptr<Window>& window) override;
	void OnHit(Hit hit_result, std::shared_ptr<Entity> other_entity) override;
private:

	std::map < std::weak_ptr<Entity>, float, std::owner_less<std::weak_ptr<Entity>>> m_colliding_balls;

	float m_max_influence;

	float m_move_scale_factor;

	void Input(const std::unique_ptr<InputHandler>& input_handler);

	void HitAnim(float duration);

};