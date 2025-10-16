#include "coroutine.h"

Coroutine::Coroutine(std::function<bool(float)> func) : m_update_func(func), m_finished(false){}

void Coroutine::Update(float delta_time) {
	if (m_finished) return;
	m_finished = !m_update_func(delta_time);
}

void CoroutineManager::Start(std::function<bool(float)> func) {
	m_coroutines.emplace_back(func);
}

void CoroutineManager::Update(float delta_time) {
	
	for (Coroutine& coroutine : m_coroutines) coroutine.Update(delta_time);

	m_coroutines.erase(
		std::remove_if(m_coroutines.begin(), m_coroutines.end(),
			[delta_time](Coroutine& coroutine) {
				return coroutine.IsFinished();
			}),
		m_coroutines.end()
		);
}