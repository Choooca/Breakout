#pragma once
#include <state/game_state.h>
#include <memory>
#include <utility/math_utils.h>
#include <string>

class Game;
class UIButton;

class GameOverState : public GameState {
public:
	GameOverState(Game& game, int score);
	void Update();

private:
	Game& m_game;

	int m_score_to_show;
	std::string m_score_string;

	std::unique_ptr<UIButton> m_quit_button;
	std::unique_ptr<UIButton> m_menu_button;
	std::unique_ptr<UIButton> m_retry_button;
};