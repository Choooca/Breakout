#include "physic_handler.h"
#include <utility/aabb_utility.h>

void PhysicHandler::ProcessPhysic(std::shared_ptr<Entity> ball, std::vector<std::shared_ptr<Entity>> all_entities) {
	for (const std::shared_ptr<Entity> entity : all_entities) {
		if (ball == entity) continue;

		Hit hit_result = AABBCollideAABB({ ball->GetXPos(), ball->GetYPos(), ball->GetWidth() * .5f, ball->GetHeight() * .5f },
										 { entity->GetXPos(), entity->GetYPos(), entity->GetWidth() * .5f, entity->GetHeight() * .5f });

		if (hit_result.is_hit) {
			ball->OnHit(hit_result);
			entity->OnHit(hit_result);
		}
	}
}