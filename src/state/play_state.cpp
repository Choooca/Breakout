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
#include <core/game_event.h>

PlayState::PlayState(Game& game) :
	m_game(game),
	m_side_margin(54),
	m_top_margin(50),
	m_n_brick_x(13),
	m_n_brick_y(13),
	m_current_level_index(0),
	m_current_level_score(0),
	m_total_score(0)
{
	m_entity_factory = std::make_unique<EntityFactory>();
	m_physics_handler = std::make_unique<PhysicHandler>();
	m_coroutines = std::make_unique<CoroutineManager>();

	InitListener();

	SetModeStart();
}

PlayState::~PlayState() {
	GameEvents::Get().ClearAll();
}

void PlayState::InitListener() {

	GameEvents::Get().OnPowerUpCollected.Subscribe(
		[this]() {
			std::shared_ptr<Ball> spawn_ball = m_entity_factory->m_balls[rand() % m_entity_factory->m_balls.size()].lock();

			if (!spawn_ball) return;

			m_entity_factory->CreateEntity(ENTITY_BALL);
			std::shared_ptr<Ball> ball = m_entity_factory->m_balls.back().lock();
			ball->SetPosition(spawn_ball->GetXPos(), spawn_ball->GetYPos());
			ball->SetSize(14, 14);
			ball->SetRandomDir();
			ball->SetTexture(m_game.m_ressource_loader->GetTexture("objects/ball.png"));
		}
	);

	GameEvents::Get().OnHitBrick.Subscribe(
		[this](int score) {
			m_current_level_score += score;
		}
	);

	GameEvents::Get().OnBrickDestroyed.Subscribe(
		[this](int score, Vector2 position) {

			m_current_level_score += score;

			if (rand() % 6 == 0) {
				m_entity_factory->CreateEntity(
					ENTITY_POWERUP,
					position.x,
					position.y,
					25,
					25,
					{ 255, 255, 255, 255 },
					m_game.m_ressource_loader->GetTexture("objects/PowerUp.png")
				);
			}
		}
	);
}

void PlayState::RenderScore(Vector2 position, float size, size_t n_zero) {
	TextStyle style;
	style.font_size = size;

	std::string score_string = std::to_string(m_current_level_score + m_total_score);
	score_string = std::string(n_zero - std::min(n_zero, score_string.length()), '0') + score_string;
	std::string text = "Score : " + score_string;

	m_game.m_text_renderer->RenderText(
		text,
		position.x,
		position.y,
		style);
}

#pragma region StateMachine

void PlayState::SetModeStart() {
	m_entity_factory->Clear();

	float elapsed;
	float duration;

	m_current_update = &PlayState::UpdateStart;

	m_current_level = std::make_unique<Level>(m_current_level_index);

	m_coroutines->Start([this, elapsed = 0.0, duration = 2.0f](float delta_time) mutable {
		elapsed += delta_time;

		if (elapsed >= duration) {
			SetModeWaitUntilInput();
			return true;
		}

		return false;
		});
}

void PlayState::UpdateStart() {
	TextStyle style;
	style.font_size = 100;

	m_game.m_text_renderer->RenderText(
		m_current_level->GetName(),
		m_game.m_window->GetWidth() * .5f,
		m_game.m_window->GetHeight() * .5f,
		style);

	RenderScore({ m_game.m_window->GetWidth() * .5f , 300}, 50);

	m_coroutines->Update(m_game.m_input_handler->GetDeltaTime());
}

void PlayState::SetModeWaitUntilInput() {
	m_entity_factory->CreateEntity(ENTITIES::ENTITY_PADDLE);
	m_entity_factory->m_all_entities.back()->SetColor({ 255, 100, 255, 255 });
	m_entity_factory->m_all_entities.back()->SetPosition(m_game.m_window->GetWidth() * .5f, 800);
	m_entity_factory->m_all_entities.back()->SetSize(100, 20);

	m_entity_factory->CreateEntity(ENTITIES::ENTITY_BALL);
	m_entity_factory->m_all_entities.back()->SetPosition(m_game.m_window->GetWidth() * .5f, 700);
	m_entity_factory->m_all_entities.back()->SetSize(14, 14);
	m_entity_factory->m_all_entities.back()->SetTexture(m_game.m_ressource_loader->GetTexture("objects/ball.png"));

	m_current_level->GenerateLevel(m_game, *this, m_entity_factory);

	m_current_update = &PlayState::UpdateWaitUntilInput;
}

void PlayState::UpdateWaitUntilInput() {
	for (const std::shared_ptr<Entity>& entity : m_entity_factory->m_all_entities)
		entity->Render(m_game.m_window);

	RenderScore({ 150 , GetTopMargin() * .5f }, 30);

	TextStyle style;
	style.font_size = 60;

	m_game.m_text_renderer->RenderText(
		"PRESS SPACE",
		m_game.m_window->GetWidth() * .5f,
		600,
		style);

	if (m_game.m_input_handler->GetKey(SDLK_SPACE)) SetModePlay();
}

void PlayState::SetModePlay() {

	m_entity_factory->m_balls[0].lock()->SetDir({ .01, 1.0f });
	m_current_update = &PlayState::UpdatePlay;
}

void PlayState::UpdatePlay() {
	for (const std::shared_ptr<Entity>& entity : m_entity_factory->m_all_entities) {
		entity->UpdateCoroutine(m_game.m_input_handler);
		if(entity->GetUpdateEnable()) entity->Update(m_game.m_input_handler, m_game.m_window->GetHeight());
	}

	m_physics_handler->ProcessPhysic(m_entity_factory->m_moving_entities, m_entity_factory->m_all_entities);

	for (const std::shared_ptr<Entity>& entity : m_entity_factory->m_all_entities)
		entity->Render(m_game.m_window);

	RenderScore({150 , GetTopMargin() * .5f }, 30);

	DestroyQueue();

	CheckWinCondition();
}

void PlayState::SetModeLose() {
	float elapsed;
	float duration;

	m_current_update = &PlayState::UpdateLose;

	m_coroutines->Start([this, elapsed = 0.0, duration = 2.0f](float delta_time) mutable {
		elapsed += delta_time;

		if (elapsed >= duration) {
			RestartLevel();
			return true;
		}

		return false;
		});
}

void PlayState::UpdateLose() {
	for (const std::shared_ptr<Entity>& entity : m_entity_factory->m_all_entities)
		entity->Render(m_game.m_window);

	m_coroutines->Update(m_game.m_input_handler->GetDeltaTime());
}

void PlayState::SetModeWin() {
	float elapsed;
	float duration;

	m_total_score += m_current_level_score;
	m_current_level_score = 0;

	m_current_update = &PlayState::UpdateWin;

	m_coroutines->Start([this, elapsed = 0.0, duration = 2.0f](float delta_time) mutable {
		elapsed += delta_time;

		if (elapsed >= duration) {
			NextLevel();
			return true;
		}

		return false;
		});

}
void PlayState::UpdateWin() {

	for (const std::shared_ptr<Entity>& entity : m_entity_factory->m_all_entities)
		entity->Render(m_game.m_window);

	m_coroutines->Update(m_game.m_input_handler->GetDeltaTime());
}

#pragma endregion

void PlayState::Update() {
	if (m_current_update) (this->*m_current_update)();
	
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

void PlayState::CheckWinCondition() {
	if (m_entity_factory->m_bricks.size() == 0) {
		SetModeWin();
		return;
	}

	if (m_entity_factory->m_balls.size() == 0) {
		SetModeLose();
	}
}

void PlayState::RestartLevel() {
	m_current_level_score = 0;
	m_entity_factory->Clear();
	SetModeStart();
}

void PlayState::NextLevel() {
	m_entity_factory->Clear();
	m_current_level_index++;
	SetModeStart();
}