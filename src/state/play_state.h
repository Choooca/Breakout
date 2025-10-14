#pragma once
#include "game_state.h"
#include <memory>

class Game;
class EntityFactory;
class PhysicHandler;

class PlayState : public GameState {
public :
	PlayState();

	void Update(const Game &game) override;

private:
	std::unique_ptr<EntityFactory> m_entity_factory;
	std::unique_ptr<PhysicHandler> m_physics_handler;
};