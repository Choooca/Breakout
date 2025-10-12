#include "game.h"
#include <entity/entity_factory.h>
#include <entity/entity.h>
#include <vector>
#include <memory>

Game::Game() {
	m_window = std::make_unique<Window>();
	m_input_handler = std::make_unique<InputHandler>(m_window->GetWindow());
}

void Game::Run() {

	std::unique_ptr<EntityFactory> entity_factory = std::make_unique<EntityFactory>();
	

	std::shared_ptr<Entity> paddle = entity_factory->CreateEntity(ENTITIES::PADDLE);
	paddle->SetColor({ 255, 100, 255, 255 });
	paddle->SetPosition(400, 550);
	paddle->SetSize(100, 20);
	
	std::shared_ptr<Entity> ball = entity_factory->CreateEntity(ENTITIES::BALL);
	ball->SetColor({ 100, 255, 255, 255 });
	ball->SetPosition(400, 200);
	ball->SetSize(20, 20);

	while (!m_input_handler->m_quit) {
		m_input_handler->Update();

		m_window->RenderBegin();

		for (const std::shared_ptr<Entity>& entity : entity_factory->all_entities)
			entity->Update(*this);

		for (const std::shared_ptr<Entity>& entity : entity_factory->all_entities)
			entity->Render(m_window);

		m_window->RenderEnd();
	}
}