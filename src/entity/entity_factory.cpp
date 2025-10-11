#include "entity_factory.h"
#include <entity/ball.h>
#include <entity/paddle.h>

std::shared_ptr<Entity> EntityFactory::CreateEntity(ENTITIES entity_type, int screen_width, int screen_height) {

	switch (entity_type)
	{
	case PADDLE:
		all_entities.push_back(std::make_shared<Paddle>(screen_width, screen_width));
		break;
	case BALL:
		all_entities.push_back(std::make_shared<Ball>(screen_width, screen_width));
		break;
	default:
		break;
	}

	return all_entities.back();

}