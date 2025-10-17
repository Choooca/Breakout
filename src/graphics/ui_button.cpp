#include "ui_button.h"
#include <string>

UIButton::UIButton(SDL_Texture* texture, std::function<void()> func, std::string text, Vector2 position, Vector2 size) :
	m_texture(texture), m_func(func), m_position(position), m_text(text), m_size(size), m_color({ 255, 255,255,255 }) {}

void UIButton::Update(Vector2 cursor_pos, int mouse_state) {
	AABB button_aabb = {
		m_position.x,
		m_position.y,
		m_size.x * .5f,
		m_size.y * .5f
	};

	if (PointCollideAABB(cursor_pos, button_aabb)) {
		m_color = { 200,200,200,255 };
		if (mouse_state & SDL_BUTTON_LMASK) {
			m_func();
		}
	}
	else m_color = { 255, 255,255,255 };
}

void UIButton::Render(SDL_Renderer* renderer, const std::unique_ptr<TextRenderer>& text_renderer){

	SDL_SetTextureAlphaMod(m_texture, m_color.a);
	SDL_SetTextureColorMod(m_texture, m_color.r, m_color.g, m_color.b);
	SDL_FRect rect = { m_position.x - m_size.x * .5f, m_position.y - m_size.y * .5f, m_size.x, m_size.y };
	SDL_RenderTexture(renderer, m_texture, nullptr, &rect);

	TextStyle style;
	style.font_size = m_size.y * .5f;
	style.color = { 0,0,0, 255 };
	text_renderer->RenderText(m_text, m_position.x, m_position.y, style);
}