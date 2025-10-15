#pragma once
#include <memory>
#include <entity/moving_entity.h>

class PlayState;
class Entity;
class Game;
class InputHandler;

class Paddle : public MovingEntity {
public:
	Paddle(float position_x, float position_y, float width, float height, Color color, std::string name, float speed, SDL_Texture* texture);

	void Update(const Game &game, const PlayState& state) override;

	void ModifyBallDirection(float &dir_x, float &dir_y, const Hit& hit_result) override;

	void OnHit(Hit hit_result, std::shared_ptr<Entity> other_entity, const std::unique_ptr<EntityFactory>& entity_factory, const Game& game) override;
private:

	float m_max_influence;

	void Input(const Game &game, const PlayState &state);

	void HitAnim(float duration);

};