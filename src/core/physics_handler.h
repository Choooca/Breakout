#pragma once
#include <memory>
#include <vector>

class Entity;
class MovingEntity;
class PlayState;
class Game;

class PhysicHandler {
public:
	void ProcessPhysic(const PlayState& state, const Game& game);
	
};