#include <iostream>
#include <memory>
#include "ROBOTC/ProgramRunner.h"
#include "World.h"
#include "ROBOTC\RobotC.h"

// Only define extern variables ONCE
std::array<int, 10> motor;
std::array<bool, 10> motorReversed;
std::array<std::string, 10> motorName;
std::array<int, 16> vexRT;

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