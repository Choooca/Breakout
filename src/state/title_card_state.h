#pragma once
#include <state/game_state.h>
#include <memory>
#include <utility/math_utils.h>
#include <state/menu_state.h>

class Game;
class UIButton;

class TitleCardState : public MenuState {
public:
	TitleCardState(Game& game);
	void Update();
};