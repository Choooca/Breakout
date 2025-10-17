#include "coroutine.h"

void CoroutineManager::Start(std::function<bool(float)> func) {
	m_pending_coroutines.emplace_back(func);
}

void CoroutineManager::Clear() {
	m_coroutines.clear();
}

void CoroutineManager::Update(float delta_time) {
	
	if (!m_pending_coroutines.empty()) {
		m_coroutines.insert(m_coroutines.end(), m_pending_coroutines.begin(), m_pending_coroutines.end());
		m_pending_coroutines.clear();
	}

	std::erase_if(m_coroutines,
		[delta_time](std::function<bool(float)>& coroutine) {
			return coroutine(delta_time);
		});
}