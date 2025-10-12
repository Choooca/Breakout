#pragma once
#include <memory>
#include <core/game.h>
#include <render/window.h>

struct Color {
	float Red;
	float Green;
	float Blue;
	float Alpha;
};

class Entity {
public:
	Entity(float position_x, float position_y, float width, float height, Color color);

	void SetColor(Color color);
	void SetPosition(float x, float y);
	void SetSize(float width, float height);

	virtual void Update(const Game& game) = 0;
	virtual void Render(const std::unique_ptr<Window>& window);

protected:
	float m_position_x;
	float m_position_y;

	float m_width;
	float m_height;

	Color m_color;

};