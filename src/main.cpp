#include <iostream>
#include "render/window.h"
#include "handler/input_handler.h"
#include <memory>

int main(int argc, char* argv[]) {
	
	std::unique_ptr<Window> window = std::make_unique<Window>();
	std::unique_ptr<InputHandler> input = std::make_unique<InputHandler>(window->GetWindow());

	while (!input->m_quit) {
		input->Update();

		window->RenderBegin();

		window->RenderEnd();
	}

	return 0;
}