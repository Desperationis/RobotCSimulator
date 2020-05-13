#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

/*
	The "World" of the game. Updates and renders the window, utilities, and ECS.
*/

class ECS;
class Factory;
class World {
public:
	World(sf::VideoMode mode, const std::string windowTitle, const bool vsync = false, const unsigned int framerate = 1000000);

	void render();
	void pollEvents();
	const bool isRunning() const;
private:
	// Window
	sf::Event event;
	std::shared_ptr<sf::RenderWindow> window;

	// Window Info
	bool isFullscreen;
	int framerate;
	bool vsync;
	std::string windowTitle;

	// ECS
	std::shared_ptr<ECS> ecs;
	std::shared_ptr<Factory> factory;
};
