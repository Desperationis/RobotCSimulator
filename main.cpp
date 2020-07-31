#include "stdafx.h"
#include "Window.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "RobotCProgram/Program.h"
#include "RobotC.h"
#include "WindowObjects/PeripheralTable.h"
#include "WindowObjects/PeripheralGraphs.h"
#include "WindowObjects/VexController.h"
#include "WindowObjects/Robot.h"
#include "WindowObjects/RobotTable.h"
#include "WindowObjects/RobotVisuals.h"
#include "Utility/DeltaClock.h"

/**
 * Code Breakdown:
 * 
 * Create window
 * Add objects to it.
 * Run task programMain (Program.h) in a different thread.
 * 
 * while window is not closed:
 *		React to motor[], SensorValue[], and vexRT[] changes with objects via graphs, virtual robots, ect.
 *		Draw it to the window.
 * 
 * Kill program threads.
 */

int main()
{
	// Initialize window and ImGui
	Window::CreateWindow(sf::VideoMode(1920, 1000), "RobotCSimulator", sf::Style::Resize | sf::Style::Close);
	ImGui::SFML::Init(*Window::rawWindow);

	// Config motors, sensors, ect.
	SetUpConfig();

	// Add objects to the window.
	Window::AddObject(std::make_shared<PeripheralTable>());
	Window::AddObject(std::make_shared<VexController>());
	Window::AddObject(std::make_shared<PeripheralGraphs>());

	std::shared_ptr<Robot> robotPtr = std::make_shared<Robot>();

	Window::AddObject(robotPtr);
	Window::AddObject(std::make_shared<RobotTable>(robotPtr));
	Window::AddObject(std::make_shared<RobotVisuals>(robotPtr));

	// Run the RobotC program
	startTask(programMain);

	while (Window::rawWindow->isOpen()) {
		// Poll window events
		Window::PollEvents();

		// Update and render window.
		ImGui::SFML::Update(*Window::rawWindow, DeltaClock::bufferTime);
		DeltaClock::ResetTimer();
		ImGui::ShowMetricsWindow();
		Window::Update();
		Window::Render();
	}

	// Stop all tasks, and wait for them to join the main thread.
	printf("main.cpp: Waiting for all tasks to end...");
	stopAllTasks();
	for(int i = 0; i < threads.size(); i++) {
		threads[i]->join();
	}
}
