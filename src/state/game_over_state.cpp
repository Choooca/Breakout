#include "game_over_state.h"
#include <core/game.h>
#include <graphics/ui_button.h>
#include <state/play_state.h>
#include <state/title_card_state.h>

GameOverState::GameOverState(Game& game, int score) : MenuState(game), m_score_to_show(score) {
	m_buttons.push_back(std::make_unique<UIButton>(
		game.m_ressource_loader->GetTexture("UI/Button.png"),
		[&game]() { game.ChangeState(std::make_unique<TitleCardState>(game)); },
		"Menu",
		Vector2{ m_game.m_window->GetWidth() * .25f, 500.0f },
		Vector2{ 150.0f, 60.0f })
	);

	
	m_buttons.push_back(std::make_unique<UIButton>(
		game.m_ressource_loader->GetTexture("UI/Button.png"),
		[&game]() { game.m_input_handler->m_quit = true; },
		"Quit",
		Vector2{ m_game.m_window->GetWidth() * .75f, 500.0f },
		Vector2{ 150.0f, 60.0f })
	);

	m_buttons.push_back(std::make_unique<UIButton>(
		game.m_ressource_loader->GetTexture("UI/Button.png"),
		[&game]() { game.ChangeState(std::make_unique<PlayState>(game)); },
		"Retry",
		Vector2{ m_game.m_window->GetWidth() * .5f, 500.0f },
		Vector2{ 150.0f, 60.0f })
	);

	m_score_string = "Score : " + std::to_string(score);
}

void GameOverState::Update() {

	MenuState::Update();

	TextStyle style;
	style.font_size = 100;
	m_game.m_text_renderer->RenderText("GameOver", m_game.m_window->GetWidth() * .5f, 300.0f, style);
	m_game.m_text_renderer->RenderText(m_score_string, m_game.m_window->GetWidth() * .5f, 400.0f, style);
}