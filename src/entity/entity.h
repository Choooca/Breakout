#pragma once
#include <utility/aabb_utility.h>
#include <memory>
#include <core/game.h>
#include <render/window.h>
#include <vector>
#include <string>

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
	Entity(float position_x, float position_y, float width, float height, Color color, std::string name);

	void SetColor(Color color);
	void SetPosition(float x, float y);
	void SetSize(float width, float height);

	inline float GetXPos() const { return m_position_x; };
	inline float GetYPos() const { return m_position_y; };
	inline float GetWidth() const { return m_width; };
	inline float GetHeight() const { return m_height; };

	virtual void Update(const Game& game) {};
	virtual void Render(const std::unique_ptr<Window>& window);

	virtual void OnHit(Hit hit_result, std::weak_ptr<Entity> other_entity) {};

	bool m_should_be_free;

	std::string m_name;

protected:
	float m_position_x;
	float m_position_y;

	float m_width;
	float m_height;

	Color m_color;
};