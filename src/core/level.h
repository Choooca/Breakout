#pragma once
#include <string>
#include <core/game.h>
#include <entity/entity_factory.h>
#include <memory>

class PlayState;

class Level {
public:
	Level(std::string level_path);

	inline std::string GetName() { return m_level_name; };

	void GenerateLevel(const Game& game, const PlayState& state, const std::unique_ptr<EntityFactory>& entity_factory);

private:

	std::string m_level_name;
	std::string m_level_string;

	std::string LoadLevelFile(std::string level_path);
};