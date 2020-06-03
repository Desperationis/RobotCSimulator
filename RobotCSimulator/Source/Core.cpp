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

Core::Core(sf::VideoMode mode, const std::string windowTitle, const bool vsync, const unsigned int framerate) {
	// Create window
	sf::ContextSettings settings;
	window = std::make_shared<sf::RenderWindow>(mode, windowTitle, sf::Style::Close);
	window->setFramerateLimit(framerate);
	window->setVerticalSyncEnabled(vsync);
	srand(static_cast<unsigned int>(time(0)));

	// Debug window information
	this->framerate = framerate;
	this->vsync = vsync;
	this->windowTitle = windowTitle;
	this->isFullscreen = false;

	// Initialize utilities
	ImGuiWrapper::ImGuiWrapper(window);
	RobotDisplayer::RobotDisplayer();
	robotAvatar = std::make_shared<RobotAvatar>();

	// Setup handler (Aborts program forcefully)
	auto previous_handler = std::signal(SIGABRT, signal_handler);
}

void Core::Render() {
	window->clear(sf::Color(0, 0, 0, 255));

	// Update utilities
	DeltaClock::Update();
	ImGuiWrapper::Update();
	VEXController::Update();
	RobotDisplayer::Update();

	robotAvatar->Update();
	window->draw(*robotAvatar);

	ImGui::ShowMetricsWindow();
	ImGuiWrapper::Render();


	window->display();
}

bool Core::IsRunning() const {
	return window->isOpen();
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
					window->create(sf::VideoMode(window->getSize().x, window->getSize().y), windowTitle, sf::Style::Close);
				}
				else {
					window->create(sf::VideoMode(window->getSize().x, window->getSize().y), windowTitle, sf::Style::Fullscreen);
				}

				window->setFramerateLimit(framerate);
				window->setVerticalSyncEnabled(vsync);

				isFullscreen = !isFullscreen;
				break;
			}
		}
	}
}