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
class EntityFactory;

enum EntityFlags : uint32_t {
	FLAG_BRICK = 1,
	FLAG_PADDLE = 1 << 1,
	FLAG_BALL = 1 << 2,
	FLAG_POWERUP = 1 << 3
};

class Entity {
public:
	Entity(float position_x, float position_y, float width, float height, SDL_Color color, std::string name, SDL_Texture* texture);

	void SetColor(SDL_Color color);
	void SetPosition(float x, float y);
	void SetSize(float width, float height);
	void SetTexture(SDL_Texture* texture);

	inline float GetXPos() const { return m_position_x; };
	inline float GetYPos() const { return m_position_y; };
	inline float GetWidth() const { return m_width; };
	inline float GetHeight() const { return m_height; };

	inline uint32_t GetFlag() const { return m_flag; };
	inline uint32_t GetCollisionMask() const { return m_collide_mask; };

	inline bool GetColliding() const { return m_colliding; };

	virtual void Update(const Game& game, const PlayState& state);
	virtual void Render(const std::unique_ptr<Window>& window);

	virtual void OnHit(Hit hit_result, std::shared_ptr<Entity> other_entity, const std::unique_ptr<EntityFactory>& entity_factory, const Game& game) {};

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

	uint32_t m_flag;
	uint32_t m_collide_mask;

	SDL_Color m_color;

	float m_elapsed;

	bool m_colliding;
	
	SDL_Texture* m_texture;

};