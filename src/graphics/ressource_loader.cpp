#include "ressource_loader.h"
#include <format>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

RessourceLoader::RessourceLoader(SDL_Renderer* renderer) {
	m_renderer = renderer;
}

RessourceLoader::~RessourceLoader() {
	for (auto& [path, texture] : m_loaded_texture) {
		SDL_DestroyTexture(texture);
	}

	m_loaded_texture.clear();
}

SDL_Texture* RessourceLoader::GetTexture(std::string path) {
	if (m_loaded_texture.find(path) != m_loaded_texture.end()) {
		return m_loaded_texture.at(path);
	}

	int width, height, channels;
	unsigned char* data = stbi_load((std::string(TEXTURES_PATH) + "/" + path).c_str(), &width, &height, &channels, 0);

	if (!data) {
		fprintf(stderr, "Failed to load image : %s\n", path);
		fprintf(stderr, "stbi error : %s\n", stbi_failure_reason());
		return nullptr;
	}

	SDL_PixelFormat pixel_format;
	switch (channels)
	{
	case 3:
		pixel_format = SDL_PIXELFORMAT_RGB24;
		break;
	case 4:
		pixel_format = SDL_PIXELFORMAT_RGBA32;
		break;
	default:
		fprintf(stderr, "%d channel(s) isn't supported\n", channels);
		stbi_image_free(data);
		return nullptr;
	}

	SDL_Surface* surface = SDL_CreateSurfaceFrom(width, height, pixel_format, data, channels * width);

	if (!surface) {
		fprintf(stderr, "Failed to create surface %s\n", SDL_GetError());
		stbi_image_free(data);
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);

	SDL_DestroySurface(surface);
	stbi_image_free(data);

	if (!texture) {
		fprintf(stderr, "Failed to create texture %s\n", SDL_GetError());
		return nullptr;
	}

	m_loaded_texture[path] = texture;

	return texture;
}