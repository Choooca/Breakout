#include "play_state.h"

#include <memory>
#include <graphics/ressource_loader.h>
#include <graphics/window.h>
#include <core/game.h>
#include <graphics/background.h>
#include <cstdlib>
#include <entity/power_up.h>
#include <entity/ball.h>
#include <iostream>

PlayState::PlayState(Game& game, std::string level_string_path) : 
	m_level_string_path(level_string_path), m_side_margin(54), m_top_margin(50),  m_n_brick_x(13), m_n_brick_y(13), m_should_change_level(false)
{
	m_entity_factory = std::make_unique<EntityFactory>();
	m_physics_handler = std::make_unique<PhysicHandler>();
	m_coroutines = std::make_unique<CoroutineManager>();

	SetModePlay(game);
}

void PlayState::SetModePlay(Game& game) {

	m_entity_factory->Clear();

	m_paddle = m_entity_factory->CreateEntity(ENTITIES::ENTITY_PADDLE);
	m_entity_factory->m_all_entities.back()->SetColor({ 255, 100, 255, 255 });
	m_entity_factory->m_all_entities.back()->SetPosition(400, 800);
	m_entity_factory->m_all_entities.back()->SetSize(100, 20);

	m_entity_factory->CreateEntity(ENTITIES::ENTITY_BALL);
	m_entity_factory->m_all_entities.back()->SetPosition(400, 700);
	m_entity_factory->m_all_entities.back()->SetSize(14, 14);
	m_entity_factory->m_all_entities.back()->SetTexture(game.m_ressource_loader->GetTexture("objects/ball.png"));

	CreateWall(game);

	m_current_level = std::make_unique<Level>(m_level_string_path, game, *this, m_entity_factory);

	m_current_update = &PlayState::UpdatePlay;
}

void PlayState::UpdatePlay(Game& game) {
	for (const std::shared_ptr<Entity>& entity : m_entity_factory->m_all_entities)
		entity->Update(game, *this);

	m_physics_handler->ProcessPhysic(*this, game);

	for (const std::shared_ptr<Entity>& entity : m_entity_factory->m_all_entities)
		entity->Render(game.m_window);

	DestroyQueue();

	CheckWinCondition(game);
}

void PlayState::SetModeLose(Game& game) {
	float elapsed;
	float duration;

	m_current_update = &PlayState::UpdateLose;

	m_coroutines->Start([this, elapsed = 0.0, duration = 2.0f, &game](float delta_time) mutable {
		elapsed += delta_time;

		if (elapsed >= duration) {
			m_should_change_level = true;
			return false;
		}

		return true;
		});
}
void PlayState::UpdateLose(Game& game) {
	for (const std::shared_ptr<Entity>& entity : m_entity_factory->m_all_entities)
		entity->Render(game.m_window);

	if (m_coroutines == nullptr) return;

	m_coroutines->Update(game.m_input_handler->GetDeltaTime());
	
	if(m_should_change_level)
		game.ChangeState(new PlayState(game, "level1.txt"));

}

void PlayState::SetModeWin(Game& game) {
	float elapsed;
	float duration;

	m_current_update = &PlayState::UpdateWin;

	m_coroutines->Start([this, elapsed = 0.0, duration = 2.0f, &game](float delta_time) mutable {
		elapsed += delta_time;

		std::cout << elapsed;

		if (elapsed >= duration) {
			this->m_current_update = nullptr;
			m_should_change_level = true;
			return false;
		}

		return true;
		});

}
void PlayState::UpdateWin(Game& game) {

	for (const std::shared_ptr<Entity>& entity : m_entity_factory->m_all_entities)
		entity->Render(game.m_window);

	if (m_coroutines == nullptr) return;

	m_coroutines->Update(game.m_input_handler->GetDeltaTime());

	if (m_should_change_level)
		game.ChangeState(new PlayState(game, "level2.txt"));
}

void PlayState::CreateWall(const Game &game) {
	m_entity_factory->CreateEntity(ENTITIES::ENTITY_WALL);
	m_entity_factory->m_all_entities.back()->SetColor({ 200, 200, 200, 255 });
	m_entity_factory->m_all_entities.back()->SetPosition(GetSideMargin() * .5f, game.m_window->GetHeight() * .5f);
	m_entity_factory->m_all_entities.back()->SetSize(GetSideMargin(), game.m_window->GetHeight());
	m_entity_factory->m_all_entities.back()->m_name = "Wall";

	m_entity_factory->CreateEntity(ENTITIES::ENTITY_WALL);
	m_entity_factory->m_all_entities.back()->SetColor({ 200, 200, 200, 255 });
	m_entity_factory->m_all_entities.back()->SetPosition(game.m_window->GetWidth() - GetSideMargin() * .5f, game.m_window->GetHeight() * .5f);
	m_entity_factory->m_all_entities.back()->SetSize(GetSideMargin(), game.m_window->GetHeight());
	m_entity_factory->m_all_entities.back()->m_name = "Wall";

	m_entity_factory->CreateEntity(ENTITIES::ENTITY_WALL);
	m_entity_factory->m_all_entities.back()->SetColor({ 200, 200, 200, 255 });
	m_entity_factory->m_all_entities.back()->SetPosition(game.m_window->GetWidth() * .5f, GetTopMargin() * .5f);
	m_entity_factory->m_all_entities.back()->SetSize(game.m_window->GetWidth(), GetTopMargin());
	m_entity_factory->m_all_entities.back()->m_name = "Wall";
}

void PlayState::Update(Game& game) {
	if (m_current_update) (this->*m_current_update)(game);
	
}

void PlayState::DestroyQueue() {
	std::erase_if(m_entity_factory->m_all_entities,
		[](const std::shared_ptr<Entity>& entity) {
			return entity->m_should_be_free;
		});

	std::erase_if(m_entity_factory->m_moving_entities,
		[](const std::weak_ptr<MovingEntity>& entity) {
			return entity.expired(); 
		});

	std::erase_if(m_entity_factory->m_balls,
		[](const std::weak_ptr<Ball>& entity) {
			return entity.expired();
		});

	std::erase_if(m_entity_factory->m_bricks,
		[](const std::weak_ptr<Brick>& entity) {
			return entity.expired();
		});

}

void PlayState::CheckWinCondition(Game &game) {
	if (m_entity_factory->m_bricks.size() == 0) {
		SetModeWin(game);
		return;
	}

	if (m_entity_factory->m_balls.size() == 0) {
		SetModeLose(game);
	}
}