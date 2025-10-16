#include <entity/entity.h>
#include <core/game.h>
#include <graphics/window.h>
#include "power_up.h"
#include <iostream>

Entity::Entity(float position_x, float position_y, float width, float height, SDL_Color color, std::string name, SDL_Texture* texture)
	: m_position_x(position_x),
	  m_position_y(position_y),
	  m_width(width),
	  m_height(height),
	  m_color(color),
	  m_should_be_free(false),
	  m_name(name),
	  m_texture(texture),
	  m_colliding(true),
	  m_render_offset_x(0),
	  m_render_offset_y(0){
	m_coroutines = std::make_unique<CoroutineManager>();
}

void Entity::Update(const Game& game, const PlayState& state) {
	m_coroutines->Update(game.m_input_handler->GetDeltaTime());
}

void Entity::SetColor(SDL_Color color) {
	m_color = color;
}

void Entity::SetPosition(float x, float y) {
	m_position_x = x;
	m_position_y = y;
}

void Entity::SetSize(float width, float height) {
	m_width = width;
	m_height = height;
}

void Entity::SetTexture(SDL_Texture* texture) {
	m_texture = texture;
}

void Entity::Render(const std::unique_ptr<Window>& window) {
	Vector2 position = {
		m_position_x - m_width * .5f + m_render_offset_x,
		m_position_y - m_height * .5f + m_render_offset_y
	};

	if (!m_texture) {
		SDL_SetRenderDrawColor(window->GetRenderer(), m_color.r, m_color.g, m_color.b, m_color.a);
		SDL_FRect paddle_rect = { position.x, position.y, m_width, m_height };
		SDL_RenderFillRect(window->GetRenderer(), &paddle_rect);
		return;
	}
	
	SDL_SetTextureAlphaMod(m_texture, m_color.a);
	SDL_SetTextureColorMod(m_texture, m_color.r, m_color.g, m_color.b);
	SDL_FRect rect = { position.x, position.y, m_width, m_height };
	SDL_RenderTexture(window->GetRenderer(), m_texture, nullptr, &rect);
}

void Entity::ModifyBallDirection(float& dir_x, float& dir_y, const Hit& hit_result) {

	Vector2 normal = hit_result.normal;

	float dot = dir_x * normal.x + dir_y * normal.y;

	dir_x = dir_x - 2.0f * dot * normal.x;
	dir_y = dir_y - 2.0f * dot * normal.y;
}
