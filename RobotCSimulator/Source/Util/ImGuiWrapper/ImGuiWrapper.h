/*****************************************************************//**
 * \file   ImGuiWrapper.h
 * \brief  A wrapper for ImGUI.
 *********************************************************************/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <Time/DeltaClock.h>
#include "imgui-SFML.h"
#include "imgui.h"

/**
 * A static wrapper for ImGUI's eccentric workflow and function names.
 */
class ImGuiWrapper {
public:
	/**
	 * Initializes the wrapper. Should be called only once.
	 * 
	 * \param window The sf::RenderWindow this wrapper will draw to.
	 */
	ImGuiWrapper(std::shared_ptr<sf::RenderWindow> window);

	/**
	 * Polls ImGui events.
	 * 
	 * \param The sf::Event holding the information.
	 */
	static void PollEvents(sf::Event& event);

	/**
	 * \brief Updates ImGui. Should only be called once per frame.
	 */
	static void Update();

	/**
	 * Renders ImGui. Should only be called once per frame.
	 */
	static void Render();


private:
	/**
	 * A shared pointer of the current window, passed in at
	 * construction.
	 */
	static std::shared_ptr<sf::RenderWindow> window;
};