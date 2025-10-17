#include "menu_state.h"
#include "graphics/ui_button.h"
#include <SDL3/SDL.h>
#include <core/game.h>

void MenuState::Update() {

	Vector2 cursor_pos;
	int mouse_state = SDL_GetMouseState(&cursor_pos.x, &cursor_pos.y);

	for (const std::unique_ptr<UIButton> &button : m_buttons) {
		button->Update(cursor_pos,  mouse_state);
		button->Render(m_game.m_window->GetRenderer(), m_game.m_text_renderer );
	}
	
	TextStyle style;
	style.font_size = 40;
	m_game.m_text_renderer->RenderText(
		"High Score : " + std::to_string(m_game.m_score_handler->GetHighScore()),
		m_game.m_window->GetWidth() * .5f,
		800.0f,
		style);

	SDL_Texture* texture = m_game.m_ressource_loader->GetTexture("UI/cursor.png");
	SDL_FRect rect = { cursor_pos.x,cursor_pos.y , 50, 50 };
	SDL_RenderTexture(m_game.m_window->GetRenderer(), texture, nullptr, &rect);

}