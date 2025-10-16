#pragma once

struct Vector2;
class Game;


class ScoreHandler {
public:

	ScoreHandler();

	void AddScore(int score);
	void RenderScore(Game& game, Vector2 position, float size);

private:

	int m_current_score;

	size_t m_nzero;
};