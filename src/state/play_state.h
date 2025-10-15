#pragma once
#include "game_state.h"
#include <memory>
#include <graphics/background.h>
#include <entity/entity_factory.h>
#include <core/physics_handler.h>
#include <vector>
#include <entity/paddle.h>
#include <graphics/parallax_background.h>
#include <core/level.h>

class Game;
class RessourceLoader;

class PlayState : public GameState {
public :
	PlayState(const Game& game);

	void Update(const Game &game) override;
	
	inline float GetSideMargin() const { return m_side_margin; };
	inline float GetTopMargin() const { return m_top_margin; };
	inline int GetNXBrick() const { return m_n_brick_x; };
	inline int GetNYBrick() const { return m_n_brick_y; };

private:
	std::unique_ptr<EntityFactory> m_entity_factory;
	std::unique_ptr<PhysicHandler> m_physics_handler;
	std::unique_ptr<Level> m_current_level;

	std::vector<std::unique_ptr<ParallaxBackground>> m_all_backgrounds;

	std::shared_ptr<Entity> m_paddle;

	float m_side_margin;
	float m_top_margin;

	int m_n_brick_x;
	int m_n_brick_y;

	void CreateWall(const Game &game);
};