#include <iostream>
#include <memory>
#include "ROBOTC/ProgramRunner.h"
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
	World world(sf::VideoMode(900, 900), "RobotCSimulator", false, 120);

	// Game Loop
	while (world.isRunning()) {
		world.pollEvents();
		world.render();
	}

	return 0;
}