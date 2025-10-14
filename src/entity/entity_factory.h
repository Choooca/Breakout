#pragma once
#include <memory>
#include <vector>
#include <entity/entity.h>

class MovingEntity;

class EntityFactory {
public:
	std::shared_ptr<Entity> CreateEntity(ENTITIES entity_type);
	std::shared_ptr<Entity> CreateEntity(ENTITIES entity_type, float position_x, float position_y, float width, float height, Color color);

	std::vector<std::shared_ptr<Entity>> m_all_entities;
	std::vector<std::shared_ptr<MovingEntity>> m_moving_entities;
};