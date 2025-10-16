#pragma once
#include <string>
#include <entity/entity.h>

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

class ParallaxBackground : public Background {
public:
	ParallaxBackground(
		SDL_Texture* background_texture,
		float position_x,
		float position_y,
		float width,
		float height,
		std::weak_ptr<Entity> followed_entity,
		float move_factor
	);

	void Update(const Game& game) override;
	void Render(const Game& game) override;
private:

	std::weak_ptr<Entity> m_followed_entity;
	float m_move_factor;

	float m_base_position_x;
	float m_base_position_y;
};