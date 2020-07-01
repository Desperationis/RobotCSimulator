#include "Core.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <csignal>
#include <ImGuiWrapper/ImGuiWrapper.h>
#include <Time/DeltaClock.h>
#include "../ROBOTC/ROBOTCtoC++/RobotDisplayer.h"
#include "../ROBOTC/ROBOTCtoC++/VEXController.h"
#include "../ROBOTC/RobotAvatar/RobotAvatar.h"

void signal_handler(int signal)
{
	// Used to make sure out program exits "safely"
	if (signal == SIGABRT) {
		std::cerr << "SIGABRT received. Aborting program....\n";
	}
	std::_Exit(EXIT_FAILURE);
}

std::shared_ptr<RobotAvatar> robotAvatar;

Core::Core(sf::VideoMode windowMode, const std::string windowTitle, const bool windowVsync, const unsigned int windowFramerate) {
	// Create window
	srand(static_cast<unsigned int>(time(0)));

	this->isFullscreen = false;

	// Window information (Used for fullscreen)
	windowInfo.mode = windowMode;
	windowInfo.framerate = windowFramerate;
	windowInfo.vsync = windowVsync;
	windowInfo.title = windowTitle;
	windowInfo.size = sf::Vector2u(windowMode.width, windowMode.height);

	CreateWindowWithStyle(sf::Style::Close);

	// Initialize utilities
	ImGuiWrapper::ImGuiWrapper(window);
	RobotDisplayer::RobotDisplayer();
	robotAvatar = std::make_shared<RobotAvatar>();

	// Signal handler for abort requests (i.e. closed the window)
	// Needed to terminate threads without raising an error.
	auto previous_handler = std::signal(SIGABRT, signal_handler);
}

void Core::Render() {
	window->clear(sf::Color(0, 0, 0, 255));

	// Update / Render utilities
	DeltaClock::Update();
	ImGuiWrapper::Update();
	VEXController::Update();
	RobotDisplayer::Update();

	// Update / Render classes
	robotAvatar->Update();
	window->draw(*robotAvatar);

	// Render ImGui Elements
	ImGui::ShowMetricsWindow();
	ImGuiWrapper::Render();

	window->display();
}

bool Core::IsRunning() const {
	return window->isOpen();
}

void Core::CreateWindowWithStyle(sf::Uint32 style) {
	// Check if a pointer to the window exists.
	if(window) {
		window->create(windowInfo.mode, windowInfo.title, style);
	}
	else {
		window = std::make_shared<sf::RenderWindow>(windowInfo.mode, windowInfo.title, style);
	}
	window->setFramerateLimit(windowInfo.framerate);
	window->setVerticalSyncEnabled(windowInfo.vsync);
}


void Core::PollEvents() {
	while (window->pollEvent(event)) {
		ImGuiWrapper::PollEvents(event);

		switch (event.type) {
		case sf::Event::Closed:
			window->close();
			break;

		case sf::Event::KeyReleased:
			// Close window when "escape" is pressed
			switch (event.key.code) {
			case sf::Keyboard::Escape:
				window->close();
				std::abort();
				break;

			// Fullscreen
			case sf::Keyboard::F11:
				if (isFullscreen) {
					windowInfo.mode = sf::VideoMode(windowInfo.size.x, windowInfo.size.y);
					CreateWindowWithStyle(sf::Style::Close);
				}
				else {
					windowInfo.mode = sf::VideoMode::getDesktopMode();
					CreateWindowWithStyle(sf::Style::Fullscreen);
				}

				isFullscreen = !isFullscreen;
				break;
			}
		}
	}
}