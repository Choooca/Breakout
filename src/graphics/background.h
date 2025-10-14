#pragma once
#include <string>

class SDL_Texture;
class Window;
class Game;

class Background {
public:
	
	Background(SDL_Texture* background_texture, float position_x, float position_y, float width, float height);

	virtual void Render(const Game &game);
	virtual void Update(const Game& game) {};

protected:

	float m_position_x;
	float m_position_y;

	SDL_Texture* m_background_texture;

	float m_width;
	float m_height;
};