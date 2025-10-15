#pragma once
#include <functional>
#include <vector>

class Coroutine {
public:
	Coroutine(std::function<bool(float)> func);

	void Update(float delta_time);

	inline bool IsFinished() const { return m_finished; };
private:
	std::function<bool(float)> m_update_func;
	bool m_finished;
};

class CoroutineManager {
public:

	void Start(std::function<bool(float)> func);

	void Update(float delta_time);

private:

	std::vector<Coroutine> m_coroutines;
};