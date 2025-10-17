#pragma once
#include "game_state.h"
#include <memory>
#include <graphics/background.h>
#include <entity/entity_factory.h>
#include <core/physics_handler.h>
#include <vector>
#include <entity/paddle.h>
#include <core/level.h>

class Game;
class RessourceLoader;

class PlayState : public GameState {
public :
	PlayState(Game& game);
	~PlayState();

	void Update() override;
	
	inline float GetSideMargin() const { return m_side_margin; };
	inline float GetTopMargin() const { return m_top_margin; };
	inline int GetNXBrick() const { return m_n_brick_x; };
	inline int GetNYBrick() const { return m_n_brick_y; };

	std::unique_ptr<EntityFactory> m_entity_factory;
	std::unique_ptr<PhysicHandler> m_physics_handler;
	std::unique_ptr<Level> m_current_level;

private:
	void (PlayState::*m_current_update)() = nullptr;
	std::unique_ptr<CoroutineManager> m_coroutines;

	int m_health_point;
	const int m_max_health_point = 3;

	int m_total_score;
	int m_current_level_score;
	int m_n_brick_x;
	int m_n_brick_y;
	int m_current_level_index;
	float m_side_margin;
	float m_top_margin;

	void RenderScore(Vector2 position, float size, size_t n_zero = 7);
	void RenderHealthPoint(Vector2 position, float size, float padding = 10.0f, bool is_center = false);

	void InitListener();

	void DestroyQueue();
	void CheckWinCondition();

	void RestartLevel();
	void NextLevel();

#pragma region StateMachine

	void SetModeStart();
	void UpdateStart();

	void SetModeWaitUntilInput();
	void UpdateWaitUntilInput();

	void SetModePlay();
	void UpdatePlay();

	void SetModeLose();
	void UpdateLose();

	void SetModeWin();
	void UpdateWin();

#pragma endregion
	
};