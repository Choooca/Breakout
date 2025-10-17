#include "title_card_state.h"
#include <core/game.h>
#include <graphics/ui_button.h>
#include <state/play_state.h>

TitleCardState::TitleCardState(Game& game) : m_game(game) {
	m_start_button = std::make_unique<UIButton>(
		game.m_ressource_loader->GetTexture("UI/Button.png"),
		[&game]() { game.ChangeState(std::make_unique<PlayState>(game)); },
		"Play",
		Vector2{ m_game.m_window->GetWidth() * .5f, 500.0f},
		Vector2{300.0f, 120.0f}
	);
}

void TitleCardState::Update() {

	TextStyle style;
	style.font_size = 100;
	m_game.m_text_renderer->RenderText("Arkanoid", m_game.m_window->GetWidth() * .5f, 300.0f, style);

	Vector2 cursor_pos;
	int mouse_state = SDL_GetMouseState(&cursor_pos.x, &cursor_pos.y);

	m_start_button->Render(m_game.m_window->GetRenderer(), m_game.m_text_renderer);
	
	SDL_Texture* texture = m_game.m_ressource_loader->GetTexture("UI/cursor.png");
	SDL_FRect rect = { cursor_pos.x,cursor_pos.y , 50, 50 };
	SDL_RenderTexture(m_game.m_window->GetRenderer(), texture, nullptr, &rect);
	
	m_start_button->Update(cursor_pos, mouse_state);
}