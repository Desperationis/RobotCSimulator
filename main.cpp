#include "stdafx.h"
#include "Window.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Test.h"
#include "RobotC.h"
#include "programref\Program.h"

using namespace RobotC::Types;
using namespace RobotC::Threads;
using namespace RobotC::Types;
using namespace RobotC::Peripherals;
using namespace RobotC::Functions;

int main()
{
	// Initialize window and ImGui
	Window::CreateWindow(sf::VideoMode(800, 800), "RobotCSimulator", sf::Style::Close);
	ImGui::SFML::Init(*Window::rawWindow);

	// Run the program
	SetUp();
	startTask(programMain);


	// Add objects
	Window::AddObject(std::make_shared<Test>());

	sf::Clock deltaClock;
	while (Window::rawWindow->isOpen()) {
		// Poll window events
		Window::PollEvents();

		// Update and render window.
		ImGui::SFML::Update(*Window::rawWindow, deltaClock.restart());
		Window::Render();
	}
}
