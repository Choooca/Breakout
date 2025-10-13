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

	std::shared_ptr<Entity> paddle = entity_factory->CreateEntity(ENTITIES::PADDLE);
	paddle->SetColor({ 255, 100, 255, 255 });
	paddle->SetPosition(400, 550);
	paddle->SetSize(100, 20);
	
	std::shared_ptr<Entity> ball = entity_factory->CreateEntity(ENTITIES::BALL);
	ball->SetColor({ 100, 255, 255, 255 });
	ball->SetPosition(400, 400);
	ball->SetSize(20, 20);

	std::weak_ptr<Entity> cursor = entity_factory->CreateEntity(ENTITIES::BRICK);
	cursor.lock()->SetColor({255, 0, 0, 255});
	cursor.lock()->SetPosition(100, 100);
	cursor.lock()->SetSize(20, 20);

	while (!m_input_handler->m_quit) {
		m_input_handler->Update();

		m_window->RenderBegin();

		for (const std::shared_ptr<Entity>& entity : entity_factory->m_all_entities)
			entity->Update(*this);

		physic_handler->ProcessPhysic(ball, entity_factory->m_all_entities);

		for (const std::shared_ptr<Entity>& entity : entity_factory->m_all_entities)
			entity->Render(m_window);

		std::erase_if(entity_factory->m_all_entities,
			[](const std::shared_ptr<Entity> entity) {
				return entity->m_should_be_free;
			});


		m_window->RenderEnd();
	}
}