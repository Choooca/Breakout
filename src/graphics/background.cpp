#include "background.h"
#include <SDL3/SDL.h>
#include <graphics/window.h>
#include <core/game.h>

Background::Background(SDL_Texture* background_texture, float position_x, float position_y, float width, float height) :
	m_background_texture(background_texture),
	m_position_x(position_x),
	m_position_y(position_y),
	m_width(width),
	m_height(height){

}

void Background::Render(const Game& game) {
	SDL_FRect rect = { m_position_x,m_position_y, m_width, m_height};
	SDL_RenderTexture(game.m_window->GetRenderer(), m_background_texture, nullptr, &rect);

}