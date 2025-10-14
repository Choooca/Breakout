#pragma once
#include <memory>
#include <vector>

class Entity;
class MovingEntity;

class PhysicHandler {
public:
	void ProcessPhysic(std::vector<std::shared_ptr<MovingEntity>> move_entities, std::vector<std::shared_ptr<Entity>>& all_entities);
	
};