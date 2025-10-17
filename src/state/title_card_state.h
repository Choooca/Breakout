#pragma once
#include <state/game_state.h>
#include <memory>
#include <utility/math_utils.h>

class Game;
class UIButton;

class TitleCardState : public GameState{
public:
	TitleCardState(Game& game);
	void Update();

private:
	Game& m_game;

	std::unique_ptr<UIButton> m_start_button;
};