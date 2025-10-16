#pragma once
#include <memory>
#include <state/game_state.h>
#include <graphics/ressource_loader.h>
#include <core/input_handler.h>
#include <graphics/window.h>
#include <graphics/text_renderer.h>
#include <core/score_handler.h>

class Game {
public:
	Game();
	
	void Run();

	void ChangeState(std::unique_ptr<GameState> state);

	std::unique_ptr<Window> m_window;
	std::unique_ptr<InputHandler> m_input_handler;
	std::unique_ptr<RessourceLoader> m_ressource_loader;
	std::unique_ptr<TextRenderer> m_text_renderer;

private:

	std::unique_ptr<GameState> m_current_state;

};