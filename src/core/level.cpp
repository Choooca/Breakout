#include "level.h"
#include <fstream>
#include <sstream>
#include <format>
#include <state/play_state.h>

Level::Level(std::string level_path) {
	m_level_string = LoadLevelFile(level_path);
}
	

void Level::GenerateLevel(const Game& game, const PlayState& state, const std::unique_ptr<EntityFactory>& entity_factory) {
	float x_step = (game.m_window->GetWidth() - state.GetSideMargin() * 2.0f) / state.GetNXBrick();
	float y_step = 400.0f / state.GetNYBrick();

	for (size_t i = 0; i < state.GetNXBrick() * state.GetNYBrick(); i++)
	{
		char c = '0';

		if (m_level_string.length() > i) {
			c = m_level_string[i];
		}

		switch (c)
		{
		case '0':
			continue;
		case '1':

			entity_factory->CreateEntity(ENTITIES::ENTITY_BRICK);
			entity_factory->m_all_entities.back()->SetColor({ 255, 255, 255, 255 });
			entity_factory->m_all_entities.back()->SetPosition(
				state.GetSideMargin() + (i % state.GetNXBrick()) * x_step + x_step * .5f,
				(i / state.GetNYBrick()) * y_step + y_step * .5f + state.GetTopMargin()
			);
			entity_factory->m_all_entities.back()->SetSize(x_step, y_step);
			entity_factory->m_all_entities.back()->SetTexture(game.m_ressource_loader->GetTexture("objects/brick.png"));
			break;
		
		case '2':
			entity_factory->CreateEntity(ENTITIES::ENTITY_HARD_BRICK);
			entity_factory->m_all_entities.back()->SetColor({ 255, 255, 255, 255 });
			entity_factory->m_all_entities.back()->SetPosition(
				state.GetSideMargin() + (i % state.GetNXBrick()) * x_step + x_step * .5f,
				(i / state.GetNYBrick()) * y_step + y_step * .5f + state.GetTopMargin()
			);
			entity_factory->m_all_entities.back()->SetSize(x_step, y_step);
			entity_factory->m_all_entities.back()->SetTexture(game.m_ressource_loader->GetTexture("objects/brick_hard.png"));
			break;
		case '3':

			entity_factory->CreateEntity(ENTITIES::ENTITY_WALL);
			entity_factory->m_all_entities.back()->SetColor({ 100, 100, 100, 255 });
			entity_factory->m_all_entities.back()->SetPosition(
				state.GetSideMargin() + (i % state.GetNXBrick()) * x_step + x_step * .5f,
				(i / state.GetNYBrick()) * y_step + y_step * .5f + state.GetTopMargin()
			);
			entity_factory->m_all_entities.back()->SetSize(x_step, y_step);
			entity_factory->m_all_entities.back()->SetTexture(game.m_ressource_loader->GetTexture("objects/wall.png"));
			break;

		default:
			break;
		}

	}
}

std::string Level::LoadLevelFile(std::string level_path) {

	std::ifstream level_file(std::string(LEVELS_PATH) + "/" + level_path);

	if (!level_file.is_open()) {
		fprintf(stderr, "Failed to load file : %s", level_path);
		return "";
	}

	std::string result;
	std::string line;
	bool first_line = true;

	while (std::getline(level_file, line)) {
		
		line.erase(
			std::remove_if(
				line.begin(),
				line.end(),
				[](unsigned char c) {return !std::isprint(c);}
			),
			line.end()
		);

		if (first_line) {
			m_level_name = line;
			first_line = false;
			continue;
		}

		result += line;

	}

	level_file.close();

	return result;

}
