#pragma once
#include <memory>
#include <entity/entity.h>

class PhysicHandler {
public:
	void ProcessPhysic(std::shared_ptr<Entity> ball, std::vector<std::shared_ptr<Entity>> all_entities);
};