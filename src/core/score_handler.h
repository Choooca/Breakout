#pragma once

struct Vector2;
class Game;


class ScoreHandler {
public:

	ScoreHandler(Game &game);

	void AddScore(int score);
	void RenderScore(Vector2 position, float size);

private:

	Game& m_game;

	int m_current_score;

	size_t m_nzero;
};