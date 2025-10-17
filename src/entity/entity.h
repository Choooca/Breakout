#pragma once
#include <utility/aabb_utility.h>
#include <memory>
#include <vector>
#include <string>
#include <SDL3/SDL.h>
#include <utility/coroutine.h>
#include <core/input_handler.h>

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
	Entity(Vector2 position, Vector2 size, SDL_Color color, std::string name, SDL_Texture* texture);
	~Entity() = default;

	void SetColor(SDL_Color color) { m_color = color; };
	void SetPosition(Vector2 position) { m_position = position; };
	void SetSize(Vector2 size) { m_size = size; };
	void SetTexture(SDL_Texture* texture) { m_texture = texture; };

	inline Vector2 GetPosition() const { return m_position; };
	inline Vector2 GetSize() const { return m_size; };

	inline bool GetUpdateEnable() { return m_update_enable; }
	virtual void SetUpdateEnable(bool is_enable);

	inline uint32_t GetFlag() const { return m_flag; };
	inline uint32_t GetCollisionMask() const { return m_collide_mask; };

	inline bool GetColliding() const { return m_colliding; };

	virtual void Update(const std::unique_ptr<InputHandler>& input_handler, int window_height);
	void UpdateCoroutine(const std::unique_ptr<InputHandler>& input_handler);
	virtual void Render(const std::unique_ptr<Window>& window);

	virtual void OnHit(Hit hit_result, std::shared_ptr<Entity> other_entity) {};

	virtual void ModifyBallDirection(float &dir_x, float &dir_y, const Hit& hit_result);

	bool m_should_be_free;

	std::string m_name;

	std::unique_ptr<CoroutineManager> m_coroutines;

protected:
	
	bool m_update_enable;

	Vector2 m_position;

	Vector2 m_render_offset;

	Vector2 m_size;

	uint32_t m_flag;
	uint32_t m_collide_mask;

	SDL_Color m_color;

	float m_elapsed;

	bool m_colliding;
	
	SDL_Texture* m_texture;

};