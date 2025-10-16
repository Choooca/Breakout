#pragma once 
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <memory>
#include <unordered_map>
#include <graphics/window.h>

class Game;

struct TextStyle {
	SDL_Color color = { 255, 255, 255, 255 };
	int font_size = 24;
	std::string path = "upheavtt.ttf";
};

class TextRenderer {
	
public:

	TextRenderer(const std::unique_ptr<Window> &window);
	~TextRenderer();

	void RenderText(const std::string& text, float x, float y, const TextStyle& style = TextStyle());

private:

	const std::unique_ptr<Window>& m_window;

	TTF_Font* GetFont(const std::string& font_path, int size);

	std::unordered_map<std::string, TTF_Font*> m_fonts;
};