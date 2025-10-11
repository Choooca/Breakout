#pragma once
#include <core/input_handler.h>
#include <render/window.h>
#include <memory>

class Game {
public:
	Game();
	
	void Run();

	std::unique_ptr<Window> m_window;
	std::unique_ptr<InputHandler> m_input_handler;
};