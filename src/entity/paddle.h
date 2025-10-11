#pragma once
#include <core/input_handler.h>
#include <core/game.h>
#include <memory>
#include <entity/entity.h>

class Paddle : public Entity {
public:
	Paddle(int screen_width, int screen_height);

	void Update(const Game &game) override;

protected:

	void Render(const std::unique_ptr<Window> & window) override;

private:

	float m_speed;

	void Input(const std::unique_ptr<InputHandler> & input_handler, const std::unique_ptr<Window> &window);

};