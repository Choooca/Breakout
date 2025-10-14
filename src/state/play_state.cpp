#include "play_state.h"

#include <memory>
#include <graphics/ressource_loader.h>
#include <graphics/window.h>
#include <core/game.h>
#include <graphics/background.h>
#include <cstdlib>

PlayState::PlayState(const Game& game) {

	m_entity_factory = std::make_unique<EntityFactory>();
	m_physics_handler = std::make_unique<PhysicHandler>();

	m_paddle = m_entity_factory->CreateEntity(ENTITIES::PADDLE);
	m_entity_factory->m_all_entities.back()->SetColor({255, 100, 255, 255});
	m_entity_factory->m_all_entities.back()->SetPosition(400, 800);
	m_entity_factory->m_all_entities.back()->SetSize(100, 20);
	m_entity_factory->m_all_entities.back()->m_name = "Paddle";

	m_entity_factory->CreateEntity(ENTITIES::BALL);
	m_entity_factory->m_all_entities.back()->SetColor({ 100, 255, 255, 255 });
	m_entity_factory->m_all_entities.back()->SetPosition(400, 400);
	m_entity_factory->m_all_entities.back()->SetSize(20, 20);
	m_entity_factory->m_all_entities.back()->m_name = "Ball";

	float x_step = game.m_window->GetWidth() / 15.0f;
	float y_step = 500.0f / 15.0f;
	float y_offset = 50.0f;

	for (size_t i = 0; i < 15*15; i++)
	{
		m_entity_factory->CreateEntity(ENTITIES::BRICK);
		m_entity_factory->m_all_entities.back()->SetColor({ 255, 0, 0, 255 });
		m_entity_factory->m_all_entities.back()->SetPosition((i % 15) * x_step + x_step * .5f, (i / 15) * y_step + y_step * .5f  + y_offset);
		m_entity_factory->m_all_entities.back()->SetSize(x_step, y_step);
		m_entity_factory->m_all_entities.back()->m_name = "Brick";
		m_entity_factory->m_all_entities.back()->SetTexture(game.m_ressource_loader->GetTexture("objects/brick" + std::to_string((((i % 15) % 2) + 1)) + ".png"));
		//m_entity_factory->m_all_entities.back()->SetTexture(game.m_ressource_loader->GetTexture("objects/brick1.png"));
	}

	new ParallaxBackground(game.m_ressource_loader->GetTexture("background/background2.png"), 0, 0, 1920, 1080, m_paddle, 20);

	m_all_backgrounds.push_back(std::make_unique<ParallaxBackground>(game.m_ressource_loader->GetTexture("background/background.png"), 0, 1800, 1080, 1920, m_paddle, 10));
	m_all_backgrounds.push_back(std::make_unique<ParallaxBackground>(game.m_ressource_loader->GetTexture("background/background3.png"), -40, 0, 1080, 1920, m_paddle, 50));
	m_all_backgrounds.push_back(std::make_unique<ParallaxBackground>(game.m_ressource_loader->GetTexture("background/background4.png"), -40, 0, 1080, 1920, m_paddle, 70));
}

void PlayState::Update(const Game& game) {

	for (const std::shared_ptr<Entity>& entity : m_entity_factory->m_all_entities)
		entity->Update(game);

	m_physics_handler->ProcessPhysic(m_entity_factory->m_moving_entities, m_entity_factory->m_all_entities);

	for (const std::unique_ptr<ParallaxBackground>& background : m_all_backgrounds) {
		background->Update(game);
		background->Render(game);
	}

	for (const std::shared_ptr<Entity>& entity : m_entity_factory->m_all_entities)
		entity->Render(game.m_window);


	std::erase_if(m_entity_factory->m_all_entities,
		[](const std::shared_ptr<Entity>& entity) {
			return entity->m_should_be_free;
		});

}