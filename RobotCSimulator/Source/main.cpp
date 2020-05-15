#include <memory>
#include "ROBOTC/ProgramRunner.h"
#include "ROBOTC/DefineGlobalOnce.h"
#include "Core.h"

/*
 * main.cpp
 *
 * The main program.
 */
int main()
{
	// Run ROBOTC program
	std::unique_ptr<ProgramRunner> programRunner = std::make_unique<ProgramRunner>();
	programRunner->RunProgram();

	// Create Window
	Core world(sf::VideoMode(900, 900), "RobotCSimulator", false, 120);

	// Program Loop
	while (world.IsRunning()) {
		world.PollEvents();
		world.Render();
	}

	return 0;
}