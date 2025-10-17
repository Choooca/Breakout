#include "sound_handler.h"
#include <algorithm>

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

SoundHandler::SoundHandler() {

	m_is_initialized = false;

	m_engine = std::make_unique<ma_engine>();

	ma_result result = ma_engine_init(NULL, m_engine.get());
	if (result != MA_SUCCESS) {
		fprintf(stderr, "Failed to initialize audio engine\n");
		m_engine.reset();
		return;
	}

	m_is_initialized = true;
}

SoundHandler::~SoundHandler() {
	StopAllSound();

	if (m_engine) {
		ma_engine_uninit(m_engine.get());
		m_engine.reset();
	}
}

void SoundHandler::StartSound(std::string path, bool loop) {
	if (!m_is_initialized) return;

	std::string total_path = std::string(SOUNDS_PATH) + "/" + path;

	std::unique_ptr<ma_sound> sound = std::make_unique<ma_sound>();

	ma_result result = ma_sound_init_from_file(
		m_engine.get(),
		total_path.c_str(),
		MA_SOUND_FLAG_DECODE,
		NULL,
		NULL,
		sound.get()
	);


	if (result != MA_SUCCESS) {
		fprintf(stderr, "Failed to load sound : %s", total_path.c_str());
		return;
	}

	ma_sound_set_looping(sound.get(), loop ? MA_TRUE : MA_FALSE);
	ma_sound_start(sound.get());

	m_playing_sound.push_back(std::move(sound));
}

void SoundHandler::Update() {
	std::erase_if(m_playing_sound,
		[](const std::unique_ptr<ma_sound>& sound) {
			if (!ma_sound_is_playing(sound.get())) {
				ma_sound_uninit(sound.get());
				return true;
			}
			return false;
		});
}

void SoundHandler::StopAllSound() {
	for (auto& sound : m_playing_sound) {
		ma_sound_stop(sound.get());
		ma_sound_uninit(sound.get());
	}

	m_playing_sound.clear();
}