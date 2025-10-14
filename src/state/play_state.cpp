#include "play_state.h"

#include <memory>
#include <graphics/ressource_loader.h>
#include <graphics/window.h>
#include <entity/entity_factory.h>
#include <core/physics_handler.h>
#include <core/game.h>

PlayState::PlayState() {

	m_entity_factory = std::make_unique<EntityFactory>();
	m_physics_handler = std::make_unique<PhysicHandler>();

	m_entity_factory->CreateEntity(ENTITIES::PADDLE);
	m_entity_factory->m_all_entities.back()->SetColor({255, 100, 255, 255});
	m_entity_factory->m_all_entities.back()->SetPosition(400, 550);
	m_entity_factory->m_all_entities.back()->SetSize(100, 20);
	m_entity_factory->m_all_entities.back()->m_name = "Paddle";

	m_entity_factory->CreateEntity(ENTITIES::BALL);
	m_entity_factory->m_all_entities.back()->SetColor({ 100, 255, 255, 255 });
	m_entity_factory->m_all_entities.back()->SetPosition(400, 400);
	m_entity_factory->m_all_entities.back()->SetSize(20, 20);
	m_entity_factory->m_all_entities.back()->m_name = "Ball";

	m_entity_factory->CreateEntity(ENTITIES::BRICK);
	m_entity_factory->m_all_entities.back()->SetColor({ 255, 0, 0, 255 });
	m_entity_factory->m_all_entities.back()->SetPosition(100, 100);
	m_entity_factory->m_all_entities.back()->SetSize(100, 100);
	m_entity_factory->m_all_entities.back()->m_name = "Brick";

}

void PlayState::Update(const Game& game) {

	for (const std::shared_ptr<Entity>& entity : m_entity_factory->m_all_entities)
		entity->Update(game);

	m_physics_handler->ProcessPhysic(m_entity_factory->m_moving_entities, m_entity_factory->m_all_entities);

	SDL_Texture* tex = game.m_ressource_loader->GetTexture("background/background.png");

	SDL_FRect dest = { 0,0, 1920, 1080 };
	SDL_RenderTexture(game.m_window->GetRenderer(), tex, nullptr, &dest);

	SDL_Texture* tex2 = game.m_ressource_loader->GetTexture("background/background2.png");

	SDL_FRect dest2 = { 0,0, 1920, 1080 };
	SDL_RenderTexture(game.m_window->GetRenderer(), tex2, nullptr, &dest2);

	SDL_Texture* tex3 = game.m_ressource_loader->GetTexture("background/background3.png");

	SDL_FRect dest3 = { 0,0, 1920, 1080 };
	SDL_RenderTexture(game.m_window->GetRenderer(), tex3, nullptr, &dest3);

	for (const std::shared_ptr<Entity>& entity : m_entity_factory->m_all_entities)
		entity->Render(game.m_window);


	std::erase_if(m_entity_factory->m_all_entities,
		[](const std::shared_ptr<Entity>& entity) {
			return entity->m_should_be_free;
		});

}