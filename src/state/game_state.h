#pragma once

class Game;

class GameState {
public:
	GameState(Game& game) : m_game(game) {};
	virtual ~GameState() = default;

	virtual void Update() = 0;
protected :
	Game& m_game;
};