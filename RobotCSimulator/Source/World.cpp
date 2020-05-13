#include "World.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <csignal>
#include <Input/MouseInput.h>
#include <Debug/Debug.h>
#include <DeltaClock.h>
#include "..//ROBOTC///RobotDisplayer.h"

void signal_handler(int signal)
{
	if (signal == SIGABRT) {
		std::cerr << "SIGABRT received. Aborting program....\n";
	}
	std::_Exit(EXIT_FAILURE);
}

World::World(sf::VideoMode mode, const std::string windowTitle, const bool vsync, const unsigned int framerate) {
	// create window
	sf::ContextSettings settings;
	window = std::make_shared<sf::RenderWindow>(mode, windowTitle, sf::Style::Close);
	window->setFramerateLimit(framerate);
	window->setVerticalSyncEnabled(vsync);
	srand(static_cast<unsigned int>(time(0)));

	// initialize window information
	this->framerate = framerate;
	this->vsync = vsync;
	this->windowTitle = windowTitle;
	this->isFullscreen = false;

	// initiate utilities
	MouseInput::MouseInput(window);
	Debug::Debug(window);

	// Setup handler
	auto previous_handler = std::signal(SIGABRT, signal_handler);

}

void World::render() {
	window->clear(sf::Color(0, 0, 0, 255));

	Debug::update();

	RobotDisplayer::Update();

	Debug::render();
	DeltaClock::update();

	window->display();
}

const bool World::isRunning() const {
	return window->isOpen();
}


void World::pollEvents() {
	while (window->pollEvent(event)) {
		MouseInput::pollEvents(event);
		Debug::pollEvents(event);

		switch (event.type) {
		case sf::Event::Closed:
			window->close();
			break;

		case sf::Event::KeyReleased:
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