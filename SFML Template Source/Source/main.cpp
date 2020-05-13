#include <iostream>
#include <memory>
#include "ProgramRunner.h"
#include "World.h"

/*
 * main.cpp
 *
 * The main program.
 */
int main()
{
	// Run ROBOTC program.
	std::unique_ptr<ProgramRunner> programRunner = std::make_unique<ProgramRunner>();
	programRunner->RunProgram();

	// Create Window
	World world(sf::VideoMode(900, 900), "SFML Template", false, 120);

	// Game Loop
	while (world.isRunning()) {
		world.pollEvents();
		world.render();
	}

	system("pause");
	return 0;
}