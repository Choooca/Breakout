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
	std::shared_ptr<Entity> paddle = entity_factory->CreateEntity(ENTITIES::PADDLE, m_window->GetWidth(), m_window->GetHeight());
	std::shared_ptr<Entity> ball = entity_factory->CreateEntity(ENTITIES::BALL, m_window->GetWidth(), m_window->GetHeight());

	while (!m_input_handler->m_quit) {
		m_input_handler->Update();

		m_window->RenderBegin();

		for (const std::shared_ptr<Entity>& entity : entity_factory->all_entities) {
			entity->Update(*this);
		}

		m_window->RenderEnd();
	}
}