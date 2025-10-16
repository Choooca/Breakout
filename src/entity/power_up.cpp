#include "power_up.h"
#include <core/game.h>
#include <iostream>
#include <entity/entity_factory.h>
#include <entity/ball.h>
#include <cstdlib>
#include <core/game_event.h>

PowerUp::PowerUp(float position_x, float position_y, float width, float height, SDL_Color color, std::string name, float speed, SDL_Texture* texture)
	: MovingEntity(position_x, position_y, width, height, color, name, speed, texture) {
	m_flag = EntityFlags::FLAG_POWERUP;
	m_collide_mask = EntityFlags::FLAG_PADDLE;
}

void PowerUp::Update(const std::unique_ptr<InputHandler>& input_handler, int window_height) {
	Entity::Update(input_handler, window_height);

	m_velocity_y = input_handler->GetDeltaTime() * m_speed;
}

void PowerUp::OnHit(Hit hit_result, std::shared_ptr<Entity> other_entity) {
	
	GameEvents::Get().OnPowerUpCollected.Invoke();

	m_should_be_free = true;
}