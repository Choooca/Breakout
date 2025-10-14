#pragma once
#include <core/input_handler.h>
#include <state/game_state.h>
#include <graphics/window.h>
#include <memory>

class Game {
public:
	Game();
	
	void Run();

	void ChangeState(GameState* state);

	std::unique_ptr<Window> m_window;
	std::unique_ptr<InputHandler> m_input_handler;

private:

	std::unique_ptr<GameState> m_current_state;

};