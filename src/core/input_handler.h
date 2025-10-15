#pragma once
#include <SDL3/SDL.h>

class InputHandler {
public:
	InputHandler(SDL_Window* window);
	~InputHandler();

	void Update();
	bool GetKey(int key_code) const;
	
	inline float GetDeltaTime() { return m_delta_time; }

	bool m_quit;

private:
	void CalculateDeltaTime();
	
	float m_delta_time;
	float m_current_time;
	float m_last_time;

	bool m_keys[128] = { false };
};