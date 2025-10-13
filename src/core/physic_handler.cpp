#include "physic_handler.h"
#include <utility/aabb_utility.h>
#include <iostream>
#include <windows.h>

void PhysicHandler::ProcessPhysic(std::vector<std::shared_ptr<MovingEntity>> move_entities, std::vector<std::shared_ptr<Entity>>& all_entities) {
	
	for (size_t i = 0; i < move_entities.size(); i++) {
		
		std::shared_ptr<MovingEntity> entity_a = move_entities[i];

		for (size_t j = i + 1; j < move_entities.size(); j++) {

			std::shared_ptr<MovingEntity> entity_b = move_entities[j];

			Collision collision = SweepMovingAABB(
				{ entity_a->GetXPos(), entity_a->GetYPos(), entity_a->GetWidth() * .5f, entity_a->GetHeight() * .5f },
				{ entity_a->GetXVelocity(), entity_a->GetYVelocity() },
				{ entity_b->GetXPos(), entity_b->GetYPos(),entity_b->GetWidth() * .5f,  entity_b->GetHeight() * .5f },
				{ entity_b->GetXVelocity(), entity_b->GetYVelocity() }
			);

			if (collision.hit) {
				entity_a->OnHit(collision.A, entity_b);
				entity_b->OnHit(collision.B, entity_a);
			}
		}
	}


	for (const std::shared_ptr<MovingEntity>& move_entity : move_entities) {

		for (const std::shared_ptr<Entity>& entity : all_entities) {
			if (std::find(move_entities.begin(), move_entities.end(), entity) != move_entities.end()) continue;

			Collision collision = SweepMovingAABB(
				{ move_entity->GetXPos(), move_entity->GetYPos(), move_entity->GetWidth() * .5f, move_entity->GetHeight() * .5f },
				{ move_entity->GetXVelocity(), move_entity->GetYVelocity() },
				{ entity->GetXPos(), entity->GetYPos(),entity->GetWidth() * .5f,  entity->GetHeight() * .5f },
				{0, 0}
			);

			if (collision.hit) {
				move_entity->OnHit(collision.A, entity);
				entity->OnHit(collision.B, move_entity);
			}
		}
	}


	for (const std::shared_ptr<MovingEntity>& move_entity : move_entities) {
		move_entity->SetPosition(
			move_entity->GetXPos() + move_entity->GetXVelocity(),
			move_entity->GetYPos() + move_entity->GetYVelocity());
	}
}
