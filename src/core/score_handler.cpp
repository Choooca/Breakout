#include "score_handler.h"
#include <iostream>
#include <fstream>
#include <format>

ScoreHandler::ScoreHandler() {
	m_file_path = std::string(ASSETS_PATH) + "/" "data/high_score.txt";
}


int ScoreHandler::UpdateHighScore(int score) {
	int current_high_score = GetHighScore();

	if (score <= current_high_score)
		return current_high_score;

	std::ofstream file(m_file_path);

	if (!file) {
		fprintf(stderr, "Failed to load file : ", m_file_path);
		return 0;
	}

	file << score;
	file.close();

	return score;
}

int ScoreHandler::GetHighScore() {

	std::ifstream file(m_file_path);

	if (!file) {
		std::ofstream create_file(m_file_path);
		if (create_file) {
			create_file << 0;
			create_file.close();
		} 
		else fprintf(stderr, "Failed to create file : %s", m_file_path);
		return 0;
	}

	int high_score = 0;
	file >> high_score;
	file.close();

	return high_score;
}