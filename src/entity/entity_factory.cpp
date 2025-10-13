#include "entity_factory.h"
#include <entity/ball.h>
#include <entity/paddle.h>
#include <entity/brick.h>

std::shared_ptr<Entity> EntityFactory::CreateEntity(ENTITIES entity_type) {
	return CreateEntity(entity_type, 0.0f, 0.0f, 10.0f, 10.0f, { 255, 255, 255, 255 });
}

std::shared_ptr<Entity> EntityFactory::CreateEntity(ENTITIES entity_type, float position_x, float position_y, float width, float height, Color color) {

	switch (entity_type)
	{
	case PADDLE:
		all_entities.push_back(std::make_shared<Paddle>(position_x, position_y, width, height, color));
		break;
	case BALL:
		all_entities.push_back(std::make_shared<Ball>(position_x, position_y, width, height, color));
		break;
	case BRICK:
		all_entities.push_back(std::make_shared<Brick>(position_x, position_y, width, height, color));
		break;
	default:
		break;
	}

	return all_entities.back();

}