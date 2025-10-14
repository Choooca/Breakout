#pragma once

class Game;

class GameState {
public:
	virtual ~GameState() = default;

	virtual void Update(const Game &game) = 0;
};