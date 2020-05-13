#include "World.h"
#include <cstdlib>
#include <ctime>
#include <Input/MouseInput.h>
#include <Debug/Debug.h>
#include <DeltaClock.h>
#include "ECS/ECS.h"
#include "ECS/Factory.h"
#include "ECS/Registerer.h"

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
	Log::Log("Source\\log.txt");
	MouseInput::MouseInput(window);
	Debug::Debug(window);

	ecs = std::make_shared<ECS>();
	Registerer registerer = Registerer(ecs, window, "Source\\SystemBlueprints.xml");
	factory = std::make_shared<Factory>(ecs, "Source\\EntityBlueprints.xml");


	// load entities
	factory->loadEntity("Player");

	for (int i = 0; i < 21; i++) {
		Entity wall = factory->loadEntity("Wall");

		auto& drawable = ecs->getComponent<DrawableComponent>(wall);
		auto& position = ecs->getComponent<PositionComponent>(wall);
		auto rectangle = std::dynamic_pointer_cast<sf::RectangleShape>(drawable.drawable);

		position.pos.x = (rectangle->getLocalBounds().width + 10) * i - 10;
		position.pos.y = 900 - rectangle->getLocalBounds().height;
	}
}

void World::render() {
	window->clear(sf::Color(0, 0, 0, 255));

	Debug::update();
	// if there's a huge unexpected lag spike, stop updating all systems
	if (DeltaClock::getDelta() < 0.1) {
		ecs->updateSystems(ecs);
	}
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