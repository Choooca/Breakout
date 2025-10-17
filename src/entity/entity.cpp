#include <entity/entity.h>
#include <core/game.h>
#include <graphics/window.h>
#include "power_up.h"
#include <iostream>
#include <core/input_handler.h>

Entity::Entity(Vector2 position, Vector2 size, SDL_Color color, std::string name, SDL_Texture* texture)
	: m_position(m_position),
	  m_size(size),
	  m_color(color),
	  m_should_be_free(false),
	  m_name(name),
	  m_texture(texture),
	  m_colliding(true),
	  m_render_offset(0),
	  m_update_enable(true){
	m_coroutines = std::make_unique<CoroutineManager>();
}

void Entity::SetUpdateEnable(bool is_enable) {
	m_update_enable = is_enable;
}

void Entity::Update(const std::unique_ptr<InputHandler>& input_handler, int window_height) {}

void Entity::UpdateCoroutine(const std::unique_ptr<InputHandler>& input_handler) {
	m_coroutines->Update(input_handler->GetDeltaTime());
}

void Entity::Render(const std::unique_ptr<Window>& window) {
	Vector2 position = {
		m_position.x - m_size.x * .5f + m_render_offset.x,
		m_position.y - m_size.y * .5f + m_render_offset.y
	};

	if (!m_texture) {
		SDL_SetRenderDrawColor(window->GetRenderer(), m_color.r, m_color.g, m_color.b, m_color.a);
		SDL_FRect paddle_rect = { position.x, position.y, m_size.x, m_size.y };
		SDL_RenderFillRect(window->GetRenderer(), &paddle_rect);
		return;
	}
	
	SDL_SetTextureAlphaMod(m_texture, m_color.a);
	SDL_SetTextureColorMod(m_texture, m_color.r, m_color.g, m_color.b);
	SDL_FRect rect = { position.x, position.y, m_size.x, m_size.y };
	SDL_RenderTexture(window->GetRenderer(), m_texture, nullptr, &rect);
}

void Entity::ModifyBallDirection(float& dir_x, float& dir_y, const Hit& hit_result) {

	Vector2 normal = hit_result.normal;

	float dot = dir_x * normal.x + dir_y * normal.y;

	dir_x = dir_x - 2.0f * dot * normal.x;
	dir_y = dir_y - 2.0f * dot * normal.y;
}
