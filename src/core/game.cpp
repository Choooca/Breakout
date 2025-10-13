#include "game.h"
#include <entity/entity_factory.h>
#include <entity/entity.h>
#include <vector>
#include <memory>
#include <utility/aabb_utility.h>

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
	ball->SetPosition(400, 400);
	ball->SetSize(20, 20);

	std::shared_ptr<Entity> cursor = entity_factory->CreateEntity(ENTITIES::BRICK);
	cursor->SetColor({ 255, 0, 0, 255 });
	cursor->SetPosition(100, 100);
	cursor->SetSize(20, 20);

	while (!m_input_handler->m_quit) {
		m_input_handler->Update();

		m_window->RenderBegin();

		for (const std::shared_ptr<Entity>& entity : entity_factory->all_entities)
			entity->Update(*this);

		float cursor_x, cursor_y;
		SDL_GetMouseState(&cursor_x, &cursor_y);
		cursor->SetPosition(cursor_x, cursor_y);

		//Point Collide
		/*bool is_collide = false;
		for (const std::shared_ptr<Entity> entity : entity_factory->all_entities) {
			if (entity == ball) continue;
			if (PointCollideAABB({ ball->GetXPos(), ball->GetYPos() }, { cursor->GetXPos(), cursor->GetYPos(), cursor->GetWidth() * .5f, cursor->GetHeight() * .5f })) is_collide = true;
		}

		if (is_collide) ball->SetColor({ 0,255,0,255 });
		else ball->SetColor({ 255,0,0,255 });*/
	
		//Minkowski Collide
		/*AABB minkowski = MinkowskiDifference({ball->GetXPos(), ball->GetYPos(), ball->GetWidth() * .5f, ball->GetHeight() * .5f}
		, { cursor->GetXPos(), cursor->GetYPos(), cursor->GetWidth() * .5f, cursor->GetHeight() * .5f });

		SDL_SetRenderDrawColor(m_window->GetRenderer(), 255, 255, 0, 255);
		SDL_FRect minkowski_rect = { minkowski.m_x - minkowski.m_half_width, minkowski.m_y - minkowski.m_half_height, minkowski.m_half_width * 2,  minkowski.m_half_height * 2 };
		SDL_RenderFillRect(m_window->GetRenderer(), &minkowski_rect);*/

		//AABB Collide AABB
		/*bool is_collide = false;
		for (const std::shared_ptr<Entity> entity : entity_factory->all_entities) {
			if (entity == ball) continue;
			if (AABBCollideAABB({ball->GetXPos(), ball->GetYPos(), ball->GetWidth() * .5f, ball->GetHeight() * .5f },
								{ entity->GetXPos(), entity->GetYPos(), entity->GetWidth() * .5f, entity->GetHeight() * .5f })) is_collide = true;
		}

		if (is_collide) ball->SetColor({ 0,255,0,255 });
		else ball->SetColor({ 255,0,0,255 });*/

		//Penetration Vector
		AABB minkowski = MinkowskiDifference({ ball->GetXPos(), ball->GetYPos(), ball->GetWidth() * .5f, ball->GetHeight() * .5f }
		, { cursor->GetXPos(), cursor->GetYPos(), cursor->GetWidth() * .5f, cursor->GetHeight() * .5f });

		Vector2 pv = AABBPenetrationVector(minkowski);
		if(AABBCollideAABB({ ball->GetXPos(), ball->GetYPos(), ball->GetWidth() * .5f, ball->GetHeight() * .5f }
		, { cursor->GetXPos(), cursor->GetYPos(), cursor->GetWidth() * .5f, cursor->GetHeight() * .5f })) cursor->SetPosition(cursor->GetXPos() + pv.m_x, cursor->GetYPos() + pv.m_y);


		for (const std::shared_ptr<Entity>& entity : entity_factory->all_entities)
			entity->Render(m_window);

		m_window->RenderEnd();
	}
}