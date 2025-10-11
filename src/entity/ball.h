#pragma once
#include <entity/entity.h>

class Ball : public Entity {
public:

	Ball(int screen_width, int screen_height);

	void Update(const Game& game) override;

protected:

	void Render(const std::unique_ptr<Window>& window) override;

private:

	float m_speed;
};