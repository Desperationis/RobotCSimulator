/*****************************************************************//**
 * \file   Core.h
 * \brief  Runs the logic of the program.
 *********************************************************************/

#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

/**
 * The core of the application's logic. Updates and renders the window and utilities.
 */
class Core {
public:
	/**
	 * Constructs the core.
	 * 
	 * \param windowMode The sf::VideoMode of the window.
	 * \param windowTitle The name of the title of the window.
	 * \param windowVsync Whether or not vsync should be enabled or disabled.
	 * \param windowFramerate The target framerate of the window.
	 */
	Core(sf::VideoMode windowMode, const std::string windowTitle, const bool windowVsync = false, const unsigned int windowFramerate = 60);

	/**
	 * Renders the window and all utilities / classes.
	 */
	void Render();

	/**
	 * Poll window and input events.
	 */
	void PollEvents();

	/**
	 * Whether or not the program is supposed to be running.
	 * 
	 * \return A bool telling if the program is supposed to be running.
	 */
	bool IsRunning() const;

private:
	/**
	 * Re-creates or creates the window based on windowInfo and a chosen 
	 * style.
	 * 
	 * \param style sf::Style of the new window.
	 */
	void CreateWindowWithStyle(sf::Uint32 style);

private:
	/**
	 * sf::Event that is used to poll events.
	 */
	sf::Event event;

	/**
	 * The window, duh.
	 */
	std::shared_ptr<sf::RenderWindow> window;

	/**
	 * Is the window fullscreen? IS IT?
	 */
	bool isFullscreen;

	/**
	 * Basic window info. Used to switch between fullscreen and normal with ease.
	 */
	struct {
		int framerate;
		bool vsync;
		std::string title;
		sf::Vector2u size;
		sf::VideoMode mode;
	} windowInfo;
};
