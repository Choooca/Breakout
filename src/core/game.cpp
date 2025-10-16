#include "game.h"
#include <memory>
#include <state/game_state.h>
#include <state/play_state.h>
#include <graphics/ressource_loader.h>

Game::Game() {
	m_window = std::make_unique<Window>();
	m_input_handler = std::make_unique<InputHandler>(m_window->GetWindow());
	m_ressource_loader = std::make_unique<RessourceLoader>(m_window->GetRenderer());
	m_text_renderer = std::make_unique<TextRenderer>(m_window);
}

void Game::Run() {

	ChangeState(std::make_unique<PlayState>(*this));

	while (!m_input_handler->m_quit) {
		m_input_handler->Update();

		m_window->RenderBegin();

		m_current_state->Update();
		
		m_window->RenderEnd();
	}
}

void Game::ChangeState(std::unique_ptr<GameState> state) {
	m_current_state = std::move(state);
}