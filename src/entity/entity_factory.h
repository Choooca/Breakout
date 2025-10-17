#pragma once
#include <memory>
#include <vector>
#include <entity/entity.h>
#include <SDL3/SDL.h>

enum ENTITIES {
	ENTITY_PADDLE,
	ENTITY_BALL,
	ENTITY_BRICK,
	ENTITY_HARD_BRICK,
	ENTITY_WALL,
	ENTITY_POWERUP
};

class MovingEntity;
class Ball;
class Brick;

class EntityFactory {
public:
	std::shared_ptr<Entity> CreateEntity(ENTITIES entity_type);
	std::shared_ptr<Entity> CreateEntity(ENTITIES entity_type, Vector2 position, Vector2 size, SDL_Color color, SDL_Texture* texture);

	std::vector<std::shared_ptr<Entity>> m_all_entities;
	std::vector<std::weak_ptr<MovingEntity>> m_moving_entities;
	std::vector<std::weak_ptr<Ball>> m_balls;
	std::vector<std::weak_ptr<Brick>> m_bricks;

	void Clear();
};