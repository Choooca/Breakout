#pragma once
#include <memory>
#include <vector>
#include <entity/entity.h>

enum ENTITIES {
	PADDLE,
	BALL
};

class EntityFactory {
public:
	std::shared_ptr<Entity> CreateEntity(ENTITIES entity_type, int screen_width, int screen_height);
	std::vector<std::shared_ptr<Entity>> all_entities;
};