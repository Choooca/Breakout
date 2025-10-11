#pragma once
#include <SDL3/SDL.h>

class InputHandler {
public:
	InputHandler(SDL_Window* window);
	~InputHandler();

	void Update();
	bool GetKey(int key_code) const;
	
	bool m_quit;
	float m_delta_time;

private:
	void CalculateDeltaTime();
	
	float m_current_time;
	float m_last_time;

	bool m_keys[128] = { false };
};