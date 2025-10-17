#include "entity_factory.h"
#include <entity/ball.h>
#include <entity/paddle.h>
#include <entity/brick.h>
#include <entity/moving_entity.h>
#include <entity/power_up.h>

std::shared_ptr<Entity> EntityFactory::CreateEntity(ENTITIES entity_type) {
	return CreateEntity(entity_type, { 0.0f, 0.0f }, { 10.0f, 10.0f }, { 255, 255, 255, 255 }, nullptr);
}

std::shared_ptr<Entity> EntityFactory::CreateEntity(ENTITIES entity_type, Vector2 position, Vector2 size, SDL_Color color, SDL_Texture* texture) {

	switch (entity_type)
	{
	case ENTITY_PADDLE: {
		std::shared_ptr<Paddle> paddle = std::make_shared<Paddle>(position, size, color, "Paddle", 800.0f, texture);
		m_all_entities.push_back(paddle);
		m_moving_entities.push_back(paddle);
		break;
	}
	case ENTITY_BALL:{
		std::shared_ptr<Ball> ball = std::make_shared<Ball>(position, size, color, "Ball", 500.0f, texture);
		m_all_entities.push_back(ball);
		m_moving_entities.push_back(ball);
		m_balls.push_back(ball);
		break;
	}
	case ENTITY_BRICK: {
		std::shared_ptr<Brick> brick = std::make_shared<Brick>(position, size, color, "Brick", texture, false, 2, 100);
		m_all_entities.push_back(brick);
		m_bricks.push_back(brick);
		break;
	}
	case ENTITY_HARD_BRICK : {
		std::shared_ptr<Brick> brick = std::make_shared<Brick>(position, size, color, "HardBrick", texture, false, 4, 300);
			m_all_entities.push_back(brick);
			m_bricks.push_back(brick);
			break;
		}
	case ENTITY_WALL:
		m_all_entities.push_back(std::make_shared<Brick>(position, size, color, "Wall", texture, true, 1, 0));
		break;
	case ENTITY_POWERUP: {
		std::shared_ptr<PowerUp> powerup = std::make_shared<PowerUp>(position, size, color, "", 150.0f, texture);
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

	m_all_entities.clear();
	m_moving_entities.clear();
	m_balls.clear();
	m_bricks.clear();

}