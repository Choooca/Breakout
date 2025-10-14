#pragma once
#include "game_state.h"
#include <memory>
#include <graphics/background.h>
#include <entity/entity_factory.h>
#include <core/physics_handler.h>
#include <vector>
#include <entity/paddle.h>
#include <graphics/parallax_background.h>

class Game;
class RessourceLoader;

class PlayState : public GameState {
public :
	PlayState(const Game& game);

	void Update(const Game &game) override;

private:
	std::unique_ptr<EntityFactory> m_entity_factory;
	std::unique_ptr<PhysicHandler> m_physics_handler;

	std::vector<std::unique_ptr<ParallaxBackground>> m_all_backgrounds;

	std::shared_ptr<Entity> m_paddle;
};