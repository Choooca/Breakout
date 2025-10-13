#pragma once
#include <memory>
#include <vector>
#include <entity/entity.h>
#include <entity/moving_entity.h>

class PhysicHandler {
public:
	void ProcessPhysic(std::vector<std::shared_ptr<MovingEntity>> move_entities, std::vector<std::shared_ptr<Entity>>& all_entities);
	
};