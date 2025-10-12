#pragma once
#include <core/input_handler.h>
#include <core/game.h>
#include <memory>
#include <entity/entity.h>

class Paddle : public Entity {
public:
	Paddle(float position_x, float position_y, float width, float height, Color color);

	void Update(const Game &game) override;

private:

	float m_speed;

	void Input(const std::unique_ptr<InputHandler> & input_handler, const std::unique_ptr<Window> &window);

};