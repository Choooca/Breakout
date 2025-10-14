#pragma once
#include <memory>
#include <state/game_state.h>
#include <graphics/ressource_loader.h>
#include <core/input_handler.h>
#include <graphics/window.h>

class Game {
public:
	Game();
	
	void Run();

	void ChangeState(GameState* state);

	std::unique_ptr<Window> m_window;
	std::unique_ptr<InputHandler> m_input_handler;
	std::unique_ptr<RessourceLoader> m_ressource_loader;

private:

	std::unique_ptr<GameState> m_current_state;

};