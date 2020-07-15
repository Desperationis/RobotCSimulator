#include "stdafx.h"
#include "Window.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Test.h"
#include "RobotC.h"

using namespace RobotC::Types;
using namespace RobotC::Threads;

task test() {
	int i = 0;
	while(true) {
		std::cout << "This is working!" << std::endl;
		i++;

		delay(100);
	}
}

int main()
{
	// Initialize window and ImGui
	Window::CreateWindow(sf::VideoMode(800, 800), "RobotCSimulator", sf::Style::Close);
	ImGui::SFML::Init(*Window::rawWindow);



	startTask(test);


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
