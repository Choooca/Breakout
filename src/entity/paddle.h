#pragma once
#include <memory>
#include <entity/moving_entity.h>

class Entity;
class Game;
class InputHandler;

class Paddle : public MovingEntity {
public:
	Paddle(float position_x, float position_y, float width, float height, Color color, std::string name, float speed);

	void Update(const Game &game) override;

	void ModifyBallDirection(float &dir_x, float &dir_y, const Hit& hit_result) override;

private:

	float m_max_influence;

	void Input(const std::unique_ptr<InputHandler> & input_handler, const std::unique_ptr<Window> &window);

};