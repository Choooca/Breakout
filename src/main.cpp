#include <iostream>
#include <core/game.h>
#include <memory>
#include <utility/aabb_utility.h>

int main(int argc, char* argv[]) {

    std::unique_ptr<Game> game = std::make_unique<Game>();
	
    game->Run();

	return 0;
}