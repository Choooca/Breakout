#pragma once
#include <string>
#include <core/game.h>
#include <entity/entity_factory.h>
#include <memory>

class PlayState;

class Level {
public:
	Level(std::string level_path, const Game &game, const PlayState &state, const std::unique_ptr<EntityFactory> &entity_factory);

private:

	std::string LoadLevelFile(std::string level_path);
};