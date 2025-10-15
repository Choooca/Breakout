#include "power_up.h"
#include <core/game.h>
#include <iostream>
#include <entity/entity_factory.h>
#include <entity/ball.h>
#include <cstdlib>

PowerUp::PowerUp(float position_x, float position_y, float width, float height, Color color, std::string name, float speed, SDL_Texture* texture)
	: MovingEntity(position_x, position_y, width, height, color, name, speed, texture) {
	m_flag = EntityFlags::FLAG_POWERUP;
	m_collide_mask = EntityFlags::FLAG_PADDLE;
}

void PowerUp::Update(const Game& game, const PlayState& state) {
	Entity::Update(game, state);

	m_velocity_y = game.m_input_handler->GetDeltaTime() * m_speed;
}

void PowerUp::OnHit(Hit hit_result, std::shared_ptr<Entity> other_entity, const std::unique_ptr<EntityFactory>& entity_factory, const Game& game) {
	
	if (entity_factory->m_balls.size() == 0) return;
	std::shared_ptr<Ball> spawn_ball = entity_factory->m_balls[rand() % entity_factory->m_balls.size()].lock();
	m_should_be_free = true;

	if (!spawn_ball) return;

	entity_factory->CreateEntity(ENTITY_BALL);

	std::shared_ptr<Ball> ball = entity_factory->m_balls.back().lock();
	ball->SetPosition(spawn_ball->GetXPos(), spawn_ball->GetYPos());
	ball->SetSize(14, 14);
	ball->SetRandomDir();
	ball->SetTexture(game.m_ressource_loader->GetTexture("objects/ball.png"));

}