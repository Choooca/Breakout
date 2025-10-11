#pragma once
#include <memory>
#include <core/game.h>
#include <render/window.h>

class Entity {
public:
	Entity(float position_x, float position_y, float width, float height);

	virtual void Update(const Game& game) = 0;
protected:
	float m_position_x;
	float m_position_y;

	int m_width;
	int m_height;

	virtual void Render(const std::unique_ptr<Window>& window) = 0;
};