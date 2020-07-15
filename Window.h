/*****************************************************************//**
 * \file   Window.h
 * \brief  A namespace meant to control the window.
 * 
 * \author smart
 * \date   July 2020
 *********************************************************************/

#pragma once
#include <SFML/Graphics.hpp>
#include "stdafx.h"
#include "imgui.h"
#include "imgui-SFML.h"

/**
 * Makes creation, event handling, and rendering of a window easy!
 */
namespace Window {
	/**
	 * sf::RenderWindow responsible for managing the window.
	 */
	static std::unique_ptr<sf::RenderWindow> rawWindow;


	/**
	 * sf::Drawable's to be drawn on screen.
	 */
	static std::vector<std::shared_ptr<sf::Drawable>> objects;


	/**
	 * Creates, or recreates, the window.
	 * 
	 * \param videoMode - sf::VideoMode representing the dimensions of the window.
	 * \param title - The title of the window, as a std::string.
	 * \param style - sf::Style enumeration of the type of window needed.
	 */
	void CreateWindow(sf::VideoMode videoMode, std::string title, unsigned int style) {
		if (!rawWindow) {
			rawWindow = std::make_unique<sf::RenderWindow>(videoMode, title, style);
		}
		else {
			rawWindow->create(videoMode, title, style);
		}
	}

	/**
	 * Generic function that adds an object that derives from sf::Drawable
	 * to the list of drawables.
	 * 
	 * \param object - A std::shared_ptr<T> that derives from sf::Drawable.
	 */
	template <class T>
	void AddObject(std::shared_ptr<T> object) {
		auto drawable = std::dynamic_pointer_cast<sf::Drawable>(object);

		if (drawable) {
			objects.push_back(drawable);
		}
		else {
			printf("Window.h: \"%s\" did not derive from sf::Drawable! \n", typeid(T).name());
		}
	}

	/**
	 * Renders all objects onto the window.
	 */
	void Render() {
		rawWindow->clear();

		for (unsigned int i = 0; i < objects.size(); i++) {
			rawWindow->draw(*objects[i]);
		}

		// Render ImGui on top of objects.
		ImGui::SFML::Render(*rawWindow);

		rawWindow->display();
	}

	/**
	 * Polls window events!
	 */
	void PollEvents() {
		sf::Event sfEvent;

		while (rawWindow->pollEvent(sfEvent)) {

			// Let ImGui know about events too
			ImGui::SFML::ProcessEvent(sfEvent);

			switch(sfEvent.type) {
			
			case sf::Event::Closed:
				rawWindow->close();
				break;

			default:
				break;

			}
		}
	}
};