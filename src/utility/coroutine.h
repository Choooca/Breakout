#pragma once
#include <functional>
#include <vector>

class CoroutineManager {
public:

	void Start(std::function<bool(float)> func);

	void Update(float delta_time);

	void Clear();

private:

	std::vector<std::function<bool(float)>> m_coroutines;
	std::vector<std::function<bool(float)>> m_pending_coroutines;
};