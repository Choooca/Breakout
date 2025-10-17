#pragma once
#include <state/game_state.h>
#include <vector>
#include <graphics/ui_button.h>

class MenuState : public GameState {
public:
	MenuState(Game& game) : GameState(game) {};
	void Update() override;
protected:
	std::vector<std::unique_ptr<UIButton>> m_buttons;
};