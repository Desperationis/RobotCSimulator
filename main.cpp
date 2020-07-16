#include "stdafx.h"
#include "Window.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "PeripheralTable.h"
#include "RobotC.h"
#include "RobotCProgram\Program.h"

int main()
{
	// Initialize window and ImGui
	Window::CreateWindow(sf::VideoMode(1920, 1000), "RobotCSimulator", sf::Style::Resize | sf::Style::Close);
	ImGui::SFML::Init(*Window::rawWindow);

	// Add objects to the window.
	Window::AddObject(std::make_shared<PeripheralTable>());

	// Run the RobotC program
	SetUp();
	startTask(programMain);

	sf::Clock deltaClock;
	while (Window::rawWindow->isOpen()) {
		// Poll window events
		Window::PollEvents();


		// Update and render window.
		ImGui::SFML::Update(*Window::rawWindow, deltaClock.restart());
		ImGui::ShowDemoWindow();
		Window::Render();
	}

	// Stop all tasks, and wait for them to join again.
	printf("main.cpp: Waiting for all tasks to end...");
	stopAllTasks();
	for(int i = 0; i < threads.size(); i++) {
		threads[i]->join();
	}
}
