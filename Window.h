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
#include "WindowObjects/WindowObject.h"

/**
 * Makes creation, event handling, and rendering of a window easy!
 */
namespace Window {
	static std::unique_ptr<sf::RenderWindow> rawWindow;
	static std::vector<std::shared_ptr<WindowObject>> objects;

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
	 * Generic function that adds an object that derives from WindowObject
	 * to the list of drawables.
	 * 
	 * \param object - std::shared_ptr<T> that derives from WindowObject.
	 */
	template <class T>
	void AddObject(std::shared_ptr<T> object) {
		auto drawable = std::dynamic_pointer_cast<WindowObject>(object);

		if (drawable) {
			objects.push_back(drawable);
		}
		else {
			printf("Window.h: \"%s\" did not derive from WindowObject! \n", typeid(T).name());
		}
	}

	void Update() {
		for (unsigned int i = 0; i < objects.size(); i++) {
			objects[i]->Update();
		}
	}

	void Render() {
		rawWindow->clear();

		// Draw all object to the screen.
		for (unsigned int i = 0; i < objects.size(); i++) {
			rawWindow->draw(*objects[i]);
		}

		// Render ImGui on top of objects.
		ImGui::SFML::Render(*rawWindow);

		rawWindow->display();
	}

	void PollEvents() {
		sf::Event sfEvent;

		while (rawWindow->pollEvent(sfEvent)) {

			// Let ImGui know about events too
			ImGui::SFML::ProcessEvent(sfEvent);

			if (sfEvent.type == sf::Event::Closed) {
				rawWindow->close();
			}
			
			if (sfEvent.type == sf::Event::KeyReleased) {
				if(sfEvent.key.code == sf::Keyboard::Escape) {
					rawWindow->close();
				}
			}
		}
	}
};