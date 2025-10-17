#include "menu_state.h"
#include "graphics/ui_button.h"
#include <SDL3/SDL.h>
#include <core/game.h>

void MenuState::Update() {

	Vector2 cursor_pos; 
	int mouse_state;
	mouse_state = SDL_GetMouseState(&cursor_pos.x, &cursor_pos.y);
	
	for (const std::unique_ptr<UIButton> &button : m_buttons) {
		button->Update(cursor_pos,  mouse_state);
		button->Render(m_game.m_window->GetRenderer(), m_game.m_text_renderer );
	}
}