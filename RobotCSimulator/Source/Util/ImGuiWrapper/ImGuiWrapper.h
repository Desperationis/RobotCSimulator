#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <sstream>
#include "imgui-SFML.h"
#include "imgui.h"

/*
	A wrapper for ImGUI with additional functionality.
*/

class ImGuiWrapper {
public:
	ImGuiWrapper(std::shared_ptr<sf::RenderWindow> window);

	/**
	*  \brief Polls ImGui.
	*  \param event The event to be polled.
	*/
	static void PollEvents(sf::Event& event);

	/**
	*  \brief Updates ImGui. Important: Should only be called once per frame.
	*/
	static void Update();

	/**
	*  \brief Renders ImGui. Important: Should only be called once per frame.
	*/
	static void Render();

	/**
	*  \brief Converts an integer to a string
	*  \return int The integer to be stringified.
	*/
	static std::string IntToStr(int integer);

private:
	static sf::Clock deltaTime;
	static sf::Clock fpsTime;
	static unsigned int countedFrames;
	static std::shared_ptr<sf::RenderWindow> window;
};