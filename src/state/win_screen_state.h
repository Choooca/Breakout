#pragma once
#include <state/game_state.h>
#include <memory>
#include <utility/math_utils.h>
#include <state/menu_state.h>
#include <string>

class Game;
class UIButton;

class WinScreenState : public MenuState {
public:
	WinScreenState(Game& game, int score);
	void Update();

private:

	int m_score_to_show;
	std::string m_score_string;
};