#include "title_card_state.h"
#include <core/game.h>
#include <graphics/ui_button.h>
#include <state/play_state.h>

TitleCardState::TitleCardState(Game& game) : MenuState(game) {
	m_buttons.push_back(std::make_unique<UIButton>(
		game.m_ressource_loader->GetTexture("UI/Button.png"),
		[&game]() { game.ChangeState(std::make_unique<PlayState>(game)); },
		"Play",
		Vector2{ m_game.m_window->GetWidth() * .5f, 500.0f},
		Vector2{300.0f, 120.0f})
	);

	m_buttons.push_back(std::make_unique<UIButton>(
		game.m_ressource_loader->GetTexture("UI/Button.png"),
		[&game]() { game.m_input_handler->m_quit = true; },
		"Quit",
		Vector2{ m_game.m_window->GetWidth() * .5f, 600.0f },
		Vector2{ 150.0f, 60.0f })
	);
}

void TitleCardState::Update() {

	MenuState::Update();

	TextStyle style;
	style.font_size = 100;
	m_game.m_text_renderer->RenderText("Arkanoid", m_game.m_window->GetWidth() * .5f, 300.0f, style);
}