#pragma once
#include <state/game_state.h>
#include <memory>
#include <utility/math_utils.h>
#include <string>
#include <state/menu_state.h>

class Game;
class UIButton;

class GameOverState : public MenuState {
public:
	GameOverState(Game& game, int score);
	void Update();

private:

	int m_score_to_show;
	std::string m_score_string;
};