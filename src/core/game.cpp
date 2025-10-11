#include "game.h"
#include <entity/paddle.h>


Game::Game() {
	m_window = std::make_unique<Window>();
	m_input_handler = std::make_unique<InputHandler>(m_window->GetWindow());
}

void Game::Run() {
	std::unique_ptr<Paddle> paddle = std::make_unique<Paddle>(m_window->GetWidth(), m_window->GetHeight());

	while (!m_input_handler->m_quit) {
		m_input_handler->Update();

		m_window->RenderBegin();

		paddle->Update(*this);

		m_window->RenderEnd();
	}
}