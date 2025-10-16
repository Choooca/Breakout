#include "entity_factory.h"
#include <entity/ball.h>
#include <entity/paddle.h>
#include <entity/brick.h>
#include <entity/moving_entity.h>
#include <entity/power_up.h>

std::shared_ptr<Entity> EntityFactory::CreateEntity(ENTITIES entity_type) {
	return CreateEntity(entity_type, 0.0f, 0.0f, 10.0f, 10.0f, { 255, 255, 255, 255 }, nullptr);
}

std::shared_ptr<Entity> EntityFactory::CreateEntity(ENTITIES entity_type, float position_x, float position_y, float width, float height, SDL_Color color, SDL_Texture* texture) {

	switch (entity_type)
	{
	case ENTITY_PADDLE: {
		std::shared_ptr<Paddle> paddle = std::make_shared<Paddle>(position_x, position_y, width, height, color, "Paddle", 800.0f, texture);
		m_all_entities.push_back(paddle);
		m_moving_entities.push_back(paddle);
		break;
	}
	case ENTITY_BALL:{
		std::shared_ptr<Ball> ball = std::make_shared<Ball>(position_x, position_y, width, height, color, "Ball", 500.0f, texture);
		m_all_entities.push_back(ball);
		m_moving_entities.push_back(ball);
		m_balls.push_back(ball);
		break;
	}
	case ENTITY_BRICK: {
		std::shared_ptr<Brick> brick = std::make_shared<Brick>(position_x, position_y, width, height, color, "Brick", texture, false, 2);
		m_all_entities.push_back(brick);
		m_bricks.push_back(brick);
		break;
	}
	case ENTITY_WALL:
		m_all_entities.push_back(std::make_shared<Brick>(position_x, position_y, width, height, color, "Wall", texture, true, 1));
		break;
	case ENTITY_POWERUP: {
		std::shared_ptr<PowerUp> powerup = std::make_shared<PowerUp>(position_x, position_y, width, height, color, "", 150.0f, texture);
		m_all_entities.push_back(powerup);
		m_moving_entities.push_back(powerup);
		break;
	}
	default:
		break;
	}

	return m_all_entities.back();

}

void EntityFactory::Clear() {

	if (m_all_entities.empty()) return;

	m_all_entities.clear();

	std::erase_if(m_moving_entities,
		[](const std::weak_ptr<MovingEntity>& entity) {
			return entity.expired();
		});

	std::erase_if(m_balls,
		[](const std::weak_ptr<Ball>& entity) {
			return entity.expired();
		});

	std::erase_if(m_bricks,
		[](const std::weak_ptr<Brick>& entity) {
			return entity.expired();
		});
}