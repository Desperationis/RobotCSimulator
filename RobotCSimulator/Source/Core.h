#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

/*
	The core of the application. Updates and renders the window and utilities.
*/

class Core {
public:
	Core(sf::VideoMode mode, const std::string windowTitle, const bool vsync = false, const unsigned int framerate = 1000000);

	void Render();
	void PollEvents();
	bool IsRunning() const;

private:
	// Window
	sf::Event event;
	std::shared_ptr<sf::RenderWindow> window;

	// Window Info
	bool isFullscreen;
	int framerate;
	bool vsync;
	std::string windowTitle;
};
