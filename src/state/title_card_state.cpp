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
}

void TitleCardState::Update() {

	MenuState::Update();

	TextStyle style;
	style.font_size = 100;
	m_game.m_text_renderer->RenderText("Arkanoid", m_game.m_window->GetWidth() * .5f, 300.0f, style);

	Vector2 cursor_pos;
	int mouse_state = SDL_GetMouseState(&cursor_pos.x, &cursor_pos.y);

	SDL_Texture* texture = m_game.m_ressource_loader->GetTexture("UI/cursor.png");
	SDL_FRect rect = { cursor_pos.x,cursor_pos.y , 50, 50 };
	SDL_RenderTexture(m_game.m_window->GetRenderer(), texture, nullptr, &rect);
}