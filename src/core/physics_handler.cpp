#include "physics_handler.h"
#include <utility/aabb_utility.h>
#include <iostream>
#include <windows.h>
#include <entity/entity.h>
#include <entity/moving_entity.h>
#include <state/play_state.h>
#include <core/game.h>

void PhysicHandler::ProcessPhysic(std::vector<std::weak_ptr<MovingEntity>> move_entities, std::vector<std::shared_ptr<Entity>> all_entities) {
	
	for (size_t i = 0; i < move_entities.size(); i++) {
		
		if (move_entities[i].expired()) continue;

		std::shared_ptr<MovingEntity> entity_a = move_entities[i].lock();

		if (!entity_a->GetColliding()) continue;


		for (size_t j = i + 1; j < move_entities.size(); j++) {

			if (move_entities[j].expired()) continue;

			std::shared_ptr<MovingEntity> entity_b = move_entities[j].lock();

			if (!entity_b->GetColliding()) continue;

			if ((!(entity_a->GetFlag() & entity_b->GetCollisionMask())) &&
				(!(entity_b->GetFlag() & entity_a->GetCollisionMask()))) continue;


			Collision collision = SweepMovingAABB(
				{ entity_a->GetXPos(), entity_a->GetYPos(), entity_a->GetWidth() * .5f, entity_a->GetHeight() * .5f },
				{ entity_a->GetXVelocity(), entity_a->GetYVelocity() },
				{ entity_b->GetXPos(), entity_b->GetYPos(),entity_b->GetWidth() * .5f,  entity_b->GetHeight() * .5f },
				{ entity_b->GetXVelocity(), entity_b->GetYVelocity() }
			);

			if (collision.hit) {
				if (entity_b->GetFlag() & entity_a->GetCollisionMask()) entity_a->OnHit(collision.A, entity_b);
				if (entity_a->GetFlag() & entity_b->GetCollisionMask()) entity_b->OnHit(collision.B, entity_a);
			}
		}

	}


	for (const std::weak_ptr<MovingEntity>& move_entity_weak : move_entities) {

		if (move_entity_weak.expired()) continue;

		std::shared_ptr<MovingEntity> move_entity = move_entity_weak.lock();

		if (!move_entity->GetColliding()) continue;

		for (const std::shared_ptr<Entity>& entity : all_entities) {

			if (!entity->GetColliding()) continue;

			if ((!(move_entity->GetFlag() & entity->GetCollisionMask())) &&
				(!(entity->GetFlag() & move_entity->GetCollisionMask()))) continue;

			if (std::dynamic_pointer_cast<MovingEntity>(entity)) continue;

			Collision collision = SweepMovingAABB(
				{ move_entity->GetXPos(), move_entity->GetYPos(), move_entity->GetWidth() * .5f, move_entity->GetHeight() * .5f },
				{ move_entity->GetXVelocity(), move_entity->GetYVelocity() },
				{ entity->GetXPos(), entity->GetYPos(),entity->GetWidth() * .5f,  entity->GetHeight() * .5f },
				{0, 0}
			);

			if (collision.hit) {
				if (entity->GetFlag() & move_entity->GetCollisionMask()) move_entity->OnHit(collision.A, entity);
				if (move_entity->GetFlag() & entity->GetCollisionMask()) entity->OnHit(collision.B, move_entity);
			}
		}
	}


	for (const std::weak_ptr<MovingEntity>& move_entity_weak : move_entities) {

		if (!move_entity_weak.lock()) continue;
		std::shared_ptr<MovingEntity> move_entity = move_entity_weak.lock();

		move_entity->SetPosition(
			move_entity->GetXPos() + move_entity->GetXVelocity(),
			move_entity->GetYPos() + move_entity->GetYVelocity());
	}
}
