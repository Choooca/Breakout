#include "score_handler.h"
#include <utility/math_utils.h>
#include <graphics/text_renderer.h>
#include <core/game.h>
#include <algorithm>

ScoreHandler::ScoreHandler(Game& game) : m_game(game), m_current_score(0), m_nzero(6) {}

void ScoreHandler::AddScore(int score) {
	m_current_score += score;
}

void ScoreHandler::RenderScore(Vector2 position, float size) {
	TextStyle style;
	style.font_size = size;

	std::string score_string = std::to_string(m_current_score);
	score_string = std::string(6 - std::min(m_nzero, score_string.length()), '0') + score_string;
	std::string text = "Score : " + score_string;

	m_game.m_text_renderer->RenderText(
		text,
		position.x,
		position.y,
		style);
}