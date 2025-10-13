#pragma once
#include <memory>
#include <vector>
#include <entity/entity.h>
#include <entity/moving_entity.h>

class EntityFactory {
public:
	int CreateEntity(ENTITIES entity_type);
	int CreateEntity(ENTITIES entity_type, float position_x, float position_y, float width, float height, Color color);

	std::vector<std::shared_ptr<Entity>> m_all_entities;
	std::vector<std::shared_ptr<MovingEntity>> m_moving_entities;
};