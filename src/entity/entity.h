#pragma once
#include <utility/aabb_utility.h>
#include <memory>
#include <vector>
#include <string>
#include <SDL3/SDL.h>
#include <utility/coroutine.h>

class Window;
class Game;
class Vector2;
class PlayState;

enum ENTITIES {
	PADDLE,
	BALL,
	BRICK,
	WALL
};

struct Color {
	float red;
	float green;
	float blue;
	float alpha;
};

class Entity {
public:
	Entity(float position_x, float position_y, float width, float height, Color color, std::string name, SDL_Texture* texture);

	void SetColor(Color color);
	void SetPosition(float x, float y);
	void SetSize(float width, float height);
	void SetTexture(SDL_Texture* texture);

	inline float GetXPos() const { return m_position_x; };
	inline float GetYPos() const { return m_position_y; };
	inline float GetWidth() const { return m_width; };
	inline float GetHeight() const { return m_height; };

	inline bool GetColliding() const { return m_colliding; };

	virtual void Update(const Game& game, const PlayState& state);
	virtual void Render(const std::unique_ptr<Window>& window);

	virtual void OnHit(Hit hit_result, std::weak_ptr<Entity> other_entity) {};

	virtual void ModifyBallDirection(float &dir_x, float &dir_y, const Hit& hit_result);

	bool m_should_be_free;

	std::string m_name;

	std::unique_ptr<CoroutineManager> m_coroutines;

protected:
	float m_position_x;
	float m_position_y;

	float m_render_offset_x;
	float m_render_offset_y;

	float m_width;
	float m_height;

	Color m_color;

	float m_elapsed;

	bool m_colliding;
	
	SDL_Texture* m_texture;

};