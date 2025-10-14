#pragma once
#include <graphics/background.h>
#include <memory>
#include <entity/entity.h>

class ParallaxBackground :  public Background {
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