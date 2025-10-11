#pragma once
#include <core/input_handler.h>
#include <core/game.h>
#include <memory>

class Paddle {
public:
	Paddle(int screen_width, int screen_height);

	void Update(const Game &game);
private:
	float m_position_x;
	float m_position_y;

	int m_size_x = 150;
	int m_size_y = 30;

	float m_speed = 300;

	void Input(const std::unique_ptr<InputHandler> & input_handler, const std::unique_ptr<Window> &window);
	void Render(const std::unique_ptr<Window> & window);
};