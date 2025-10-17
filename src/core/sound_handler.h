#pragma once
#include <iostream>
#include <vector>

typedef struct ma_engine ma_engine;
typedef struct ma_sound ma_sound;

class SoundHandler {
public:

	SoundHandler();
	~SoundHandler();

	void Update();

	void StartSound(std::string path, bool loop = false);

private:

	void StopAllSound();

	bool m_is_initialized;

	std::unique_ptr<ma_engine> m_engine;
	std::vector<std::unique_ptr<ma_sound>> m_playing_sound;
};
