#include <entity/entity.h>

Entity::Entity(float position_x, float position_y, float width, float height, Color color)
	: m_position_x(position_x),
	  m_position_y(position_y),
	  m_width(width),
	  m_height(height),
	  m_color(color),
	  m_should_be_free(false){}

void Entity::SetColor(Color color) {
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

void Entity::Render(const std::unique_ptr<Window>& window) {
	SDL_SetRenderDrawColor(window->GetRenderer(), m_color.Red, m_color.Green, m_color.Blue, m_color.Alpha);

	SDL_FRect paddle_rect = { m_position_x - m_width * .5f, m_position_y - m_height * .5f, m_width, m_height };
	SDL_RenderFillRect(window->GetRenderer(), &paddle_rect);
}