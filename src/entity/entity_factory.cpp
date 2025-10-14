#include "entity_factory.h"
#include <entity/ball.h>
#include <entity/paddle.h>
#include <entity/brick.h>
#include <entity/moving_entity.h>

std::shared_ptr<Entity> EntityFactory::CreateEntity(ENTITIES entity_type) {
	return CreateEntity(entity_type, 0.0f, 0.0f, 10.0f, 10.0f, { 255, 255, 255, 255 });
}

std::shared_ptr<Entity> EntityFactory::CreateEntity(ENTITIES entity_type, float position_x, float position_y, float width, float height, Color color) {

	switch (entity_type)
	{
	case PADDLE: {
		std::shared_ptr<Paddle> paddle = std::make_shared<Paddle>(position_x, position_y, width, height, color, "", 500.0f);
		m_all_entities.push_back(paddle);
		m_moving_entities.push_back(paddle);
		break;
	}
	case BALL:{
		std::shared_ptr<Ball> ball = std::make_shared<Ball>(position_x, position_y, width, height, color, "", 500.0f);
		m_all_entities.push_back(ball);
		m_moving_entities.push_back(ball);
		break;
	}
	case BRICK:
		m_all_entities.push_back(std::make_shared<Brick>(position_x, position_y, width, height, color, ""));
		break;
	default:
		break;
	}

	return m_all_entities.back();

}