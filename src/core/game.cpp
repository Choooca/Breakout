#include "game.h"
#include <entity/entity_factory.h>
#include <entity/entity.h>
#include <vector>
#include <memory>
#include <utility/aabb_utility.h>
#include <core/physic_handler.h>

Game::Game() {
	m_window = std::make_unique<Window>();
	m_input_handler = std::make_unique<InputHandler>(m_window->GetWindow());
}

void Game::Run() {

	std::unique_ptr<EntityFactory> entity_factory = std::make_unique<EntityFactory>();
	std::unique_ptr<PhysicHandler> physic_handler = std::make_unique<PhysicHandler>();

	int paddle_index = entity_factory->CreateEntity(ENTITIES::PADDLE);
	entity_factory->m_all_entities[paddle_index]->SetColor({255, 100, 255, 255});
	entity_factory->m_all_entities[paddle_index]->SetPosition(400, 550);
	entity_factory->m_all_entities[paddle_index]->SetSize(100, 20);
	entity_factory->m_all_entities[paddle_index]->m_name = "Paddle";
	
	int ball_index = entity_factory->CreateEntity(ENTITIES::BALL);
	entity_factory->m_all_entities.back()->SetColor({100, 255, 255, 255});
	entity_factory->m_all_entities.back()->SetPosition(400, 400);
	entity_factory->m_all_entities.back()->SetSize(20, 20);
	entity_factory->m_all_entities.back()->m_name = "Ball";

	entity_factory->CreateEntity(ENTITIES::BRICK);
	entity_factory->m_all_entities.back()->SetColor({255, 0, 0, 255});
	entity_factory->m_all_entities.back()->SetPosition(100, 100);
	entity_factory->m_all_entities.back()->SetSize(100, 100);
	entity_factory->m_all_entities.back()->m_name = "Brick";

	entity_factory->CreateEntity(ENTITIES::BRICK);
	entity_factory->m_all_entities.back()->SetColor({ 255, 0, 0, 255 });
	entity_factory->m_all_entities.back()->SetPosition(700, 100);
	entity_factory->m_all_entities.back()->SetSize(100, 100);
	entity_factory->m_all_entities.back()->m_name = "Brick";

	AABB moving_aabb = { 400, 400, 20, 20 };
	AABB cursor_aabb = { 400, 400, 5, 5 };
	AABB static_aabb = { 300, 300, 20, 20 };

	while (!m_input_handler->m_quit) {
		m_input_handler->Update();

		m_window->RenderBegin();

		for (const std::shared_ptr<Entity>& entity : entity_factory->m_all_entities)
			entity->Update(*this);

		physic_handler->ProcessPhysic(entity_factory->m_moving_entities, entity_factory->m_all_entities);

		for (const std::shared_ptr<Entity>& entity : entity_factory->m_all_entities)
			entity->Render(m_window);

		std::erase_if(entity_factory->m_all_entities,
			[](const std::shared_ptr<Entity>& entity) {
				return entity->m_should_be_free;
			});
		
		m_window->RenderEnd();
	}
}