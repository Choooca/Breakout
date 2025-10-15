#include "level.h"
#include <fstream>
#include <sstream>
#include <format>
#include <state/play_state.h>

Level::Level(std::string level_path, const Game& game, const PlayState& state, const std::unique_ptr<EntityFactory>& entity_factory) {

	std::string level_string = LoadLevelFile(level_path);

	float x_step = (game.m_window->GetWidth() - state.GetSideMargin() * 2.0f) / state.GetNXBrick();
	float y_step = 400.0f / state.GetNYBrick();

	for (size_t i = 0; i < state.GetNXBrick() * state.GetNYBrick(); i++)
	{
		char c = '0';

		if (level_string.length() > i) {
			c = level_string[i];
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
			entity_factory->m_all_entities.back()->SetTexture(game.m_ressource_loader->GetTexture("objects/brick1.png"));
			break;

		case '2':

			entity_factory->CreateEntity(ENTITIES::ENTITY_WALL);
			entity_factory->m_all_entities.back()->SetColor({ 100, 100, 100, 255 });
			entity_factory->m_all_entities.back()->SetPosition(
				state.GetSideMargin() + (i % state.GetNXBrick()) * x_step + x_step * .5f,
				(i / state.GetNYBrick()) * y_step + y_step * .5f + state.GetTopMargin()
			);
			entity_factory->m_all_entities.back()->SetSize(x_step, y_step);
			entity_factory->m_all_entities.back()->SetTexture(game.m_ressource_loader->GetTexture("objects/brick1.png"));
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
	}

	std::stringstream buffer;
	buffer << level_file.rdbuf();
	level_file.close();
	
	std::string string_level = buffer.str();
	string_level.erase(
		std::remove_if(
			string_level.begin(),
			string_level.end(),
			[](unsigned char c) {return !std::isprint(c);
			}),
		string_level.end()
	);

	return string_level;

}
