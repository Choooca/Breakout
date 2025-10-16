#pragma once
#include <memory>
#include <vector>

class Entity;
class MovingEntity;
class PlayState;
class Game;

class PhysicHandler {
public:
	void ProcessPhysic(std::vector<std::weak_ptr<MovingEntity>> move_entities, std::vector<std::shared_ptr<Entity>> all_entities);

};