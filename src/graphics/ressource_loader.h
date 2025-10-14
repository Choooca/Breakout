#pragma once
#include <string>
#include <unordered_map>
#include <SDL3/SDL.h>

class RessourceLoader {
public:
	RessourceLoader(SDL_Renderer *renderer);
	~RessourceLoader();

	SDL_Texture* GetTexture(std::string path);

private:
	SDL_Renderer* m_renderer;

	std::unordered_map<std::string, SDL_Texture*> m_loaded_texture;
};