#pragma once

class Game;

class GameState {
public:
	virtual ~GameState() = default;

	virtual void Update(Game &game) = 0;
};