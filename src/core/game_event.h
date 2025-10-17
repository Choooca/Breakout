#pragma once
#include <vector>
#include <functional>
#include <memory>
#include <utility/math_utils.h>

template<typename... Args>
class Event {
public:

	void Subscribe(std::function<void(Args...)> listener) {
		m_listeners.push_back(listener);
	}

	void Invoke(Args... args) {
		for (std::function<void(Args...)> func : m_listeners)
			func(args...);
	}

	void Clear() {
		m_listeners.clear();
	}

private:

	std::vector<std::function<void(Args...)>> m_listeners;
};


class GameEvents {
public:

	Event<int, Vector2> OnBrickDestroyed;
	Event<> OnPowerUpCollected;
	Event<int> OnHitBrick;
	Event<> OnPaddleHit;

	static GameEvents& Get() {
		static GameEvents instance;
		return instance;
	}

	GameEvents(const GameEvents&) = delete;
	GameEvents& operator=(const GameEvents&) = delete;

	void ClearAll() {
		OnBrickDestroyed.Clear();
		OnPowerUpCollected.Clear();
		OnHitBrick.Clear();
		OnPaddleHit.Clear();
	}

private:

	GameEvents() = default;

};