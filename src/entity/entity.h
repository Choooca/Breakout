#pragma once
#include <utility/aabb_utility.h>
#include <memory>
#include <core/game.h>
#include <render/window.h>
#include <vector>

enum ENTITIES {
	PADDLE,
	BALL,
	BRICK
};

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

	inline float GetXPos() const { return m_position_x; };
	inline float GetYPos() const { return m_position_y; };
	inline float GetWidth() const { return m_width; };
	inline float GetHeight() const { return m_height; };

	virtual void Update(const Game& game) = 0;
	virtual void Render(const std::unique_ptr<Window>& window);

	virtual void OnHit(Hit hit_result) {};

	bool m_should_be_free;

protected:
	float m_position_x;
	float m_position_y;

	float m_width;
	float m_height;

	Color m_color;
};