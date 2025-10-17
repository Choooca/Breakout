#pragma once
#include <SDL3/SDL.h>
#include <utility/math_utils.h>
#include <functional>
#include <memory>
#include "utility/aabb_utility.h"
#include <graphics/text_renderer.h>

class UIButton {
public :

	UIButton(SDL_Texture* texture, std::function<void()> func, std::string text, Vector2 position, Vector2 size);
	~UIButton() = default;

	void Update(Vector2 cursor_pos, int mouse_state);

	void Render(SDL_Renderer* renderer, const std::unique_ptr<TextRenderer>& text_renderer);

private:

	SDL_Color m_color;

	std::string m_text;

	Vector2 m_position;
	Vector2 m_size;
	SDL_Texture* m_texture;

	std::function<void()> m_func;
};