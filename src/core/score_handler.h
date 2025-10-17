#pragma once
#include <string>

class ScoreHandler {
public:

	ScoreHandler();

	int UpdateHighScore(int score);
	int GetHighScore();

private:
	std::string m_file_path;

};