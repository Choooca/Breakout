#include "parallax_background.h"
#include <core/game.h>
#include <iostream>
#include <cmath>

ParallaxBackground::ParallaxBackground(
	SDL_Texture* background_texture,
	float position_x,
	float position_y,
	float width,
	float height,
	std::weak_ptr<Entity> followed_entity,
	float move_factor) :
	Background(background_texture, position_x, position_y, width, height),
	m_followed_entity(followed_entity),
	m_move_factor(move_factor){

	m_base_position_x = followed_entity.lock()->GetXPos();
	m_base_position_y = followed_entity.lock()->GetYPos();

}


void ParallaxBackground::Update(const Game& game) {
	m_position_y += m_move_factor * game.m_input_handler->GetDeltaTime();
}

void ParallaxBackground::Render(const Game& game) {

	m_position_y = std::fmod(m_position_y, m_height);

	SDL_FRect rect = { m_position_x,m_position_y, m_width, m_height };
	SDL_RenderTexture(game.m_window->GetRenderer(), m_background_texture, nullptr, &rect);
	
	rect = { m_position_x,m_position_y - m_height, m_width, m_height };
	SDL_RenderTexture(game.m_window->GetRenderer(), m_background_texture, nullptr, &rect);
}