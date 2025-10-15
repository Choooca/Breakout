#include "play_state.h"

#include <memory>
#include <graphics/ressource_loader.h>
#include <graphics/window.h>
#include <core/game.h>
#include <graphics/background.h>
#include <cstdlib>

PlayState::PlayState(const Game& game) :
	m_side_margin(54), m_top_margin(50),  m_n_brick_x(13), m_n_brick_y(13)
{
	m_entity_factory = std::make_unique<EntityFactory>();
	m_physics_handler = std::make_unique<PhysicHandler>();

	m_paddle = m_entity_factory->CreateEntity(ENTITIES::PADDLE);
	m_entity_factory->m_all_entities.back()->SetColor({255, 100, 255, 255});
	m_entity_factory->m_all_entities.back()->SetPosition(400, 800);
	m_entity_factory->m_all_entities.back()->SetSize(100, 20);
	m_entity_factory->m_all_entities.back()->m_name = "Paddle";

	m_entity_factory->CreateEntity(ENTITIES::BALL);
	m_entity_factory->m_all_entities.back()->SetColor({ 100, 255, 255, 255 });
	m_entity_factory->m_all_entities.back()->SetPosition(400, 700);
	m_entity_factory->m_all_entities.back()->SetSize(14, 14);
	m_entity_factory->m_all_entities.back()->m_name = "Ball";
	m_entity_factory->m_all_entities.back()->SetTexture(game.m_ressource_loader->GetTexture("objects/ball.png"));

	CreateWall(game);

	m_current_level = std::make_unique<Level>("level1.txt", game, *this , m_entity_factory);
}

void PlayState::CreateWall(const Game &game) {
	m_entity_factory->CreateEntity(ENTITIES::WALL);
	m_entity_factory->m_all_entities.back()->SetColor({ 200, 200, 200, 255 });
	m_entity_factory->m_all_entities.back()->SetPosition(GetSideMargin() * .5f, game.m_window->GetHeight() * .5f);
	m_entity_factory->m_all_entities.back()->SetSize(GetSideMargin(), game.m_window->GetHeight());
	m_entity_factory->m_all_entities.back()->m_name = "Wall";

	m_entity_factory->CreateEntity(ENTITIES::WALL);
	m_entity_factory->m_all_entities.back()->SetColor({ 200, 200, 200, 255 });
	m_entity_factory->m_all_entities.back()->SetPosition(game.m_window->GetWidth() - GetSideMargin() * .5f, game.m_window->GetHeight() * .5f);
	m_entity_factory->m_all_entities.back()->SetSize(GetSideMargin(), game.m_window->GetHeight());
	m_entity_factory->m_all_entities.back()->m_name = "Wall";

	m_entity_factory->CreateEntity(ENTITIES::WALL);
	m_entity_factory->m_all_entities.back()->SetColor({ 200, 200, 200, 255 });
	m_entity_factory->m_all_entities.back()->SetPosition(game.m_window->GetWidth() * .5f, GetTopMargin() * .5f);
	m_entity_factory->m_all_entities.back()->SetSize(game.m_window->GetWidth(), GetTopMargin());
	m_entity_factory->m_all_entities.back()->m_name = "Wall";
}

void PlayState::Update(const Game& game) {

	for (const std::shared_ptr<Entity>& entity : m_entity_factory->m_all_entities)
		entity->Update(game, *this);

	m_physics_handler->ProcessPhysic(m_entity_factory->m_moving_entities, m_entity_factory->m_all_entities);

	for (const std::shared_ptr<Entity>& entity : m_entity_factory->m_all_entities)
		entity->Render(game.m_window);

	std::erase_if(m_entity_factory->m_all_entities,
		[](const std::shared_ptr<Entity>& entity) {
			return entity->m_should_be_free;
		});

}