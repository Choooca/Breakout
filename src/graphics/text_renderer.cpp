#include "text_renderer.h"
#include <format>
#include <core/game.h>

TextRenderer::TextRenderer(const std::unique_ptr<Window>& window) : m_window(window) {

	if (TTF_Init() < 0)
		fprintf(stderr, "Failed to init SDL_ttf : %s\n", SDL_GetError());
}

TextRenderer::~TextRenderer() {

	for (auto& [key, font] : m_fonts) {
		TTF_CloseFont(font);
	}

	m_fonts.clear();

	TTF_Quit();

}

TTF_Font* TextRenderer::GetFont(const std::string& font_path, int size) {

	std::string key = font_path + std::to_string(size);

	auto it = m_fonts.find(key);
	if (it != m_fonts.end()) {
		return it->second;
	}

	TTF_Font* font = TTF_OpenFont((std::string(FONTS_PATH) + "/" + font_path).c_str(), size);
	if (!font) {
		fprintf(stderr, "Failed to load font : %s\n", font_path);
		return nullptr;
	}

	m_fonts[key] = font;
	return font;

}

void TextRenderer::RenderText(const std::string& text, float x, float y, const TextStyle& style) {
	
	TTF_Font* font = GetFont(style.path, style.font_size);

	if (!font) return;

	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), text.length(), style.color);
	if (!surface) {
		fprintf(stderr, "Failed to render text : %\n", SDL_GetError());
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_window->GetRenderer(), surface);

	if (!texture) {
		SDL_DestroySurface(surface);
		fprintf(stderr, "Failed to create texture : %s\n", SDL_GetError());
		return;
	}

	SDL_FRect dest = { x - surface->w * .5f, y - surface->h * .5f, surface->w, surface->h };
	SDL_RenderTexture(m_window->GetRenderer(), texture, nullptr, &dest);

	SDL_DestroyTexture(texture);
	SDL_DestroySurface(surface);


}
