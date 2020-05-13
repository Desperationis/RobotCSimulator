#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

/*
	A wrapper for SFML input, for the aim of polling mouse input easier.
*/

class MouseInput {
public:
	MouseInput(std::shared_ptr<sf::RenderWindow> window);

	enum MOUSE_SETTING {
		NONE,
		ONE_FRAME_CLICK
	};

	enum MOUSE_STATE {
		X,
		Y,
		LEFT,
		MIDDLE,
		RIGHT,
		P_LEFT,
		P_MIDDLE,
		P_RIGHT,
		SCROLL
	};

	/**
	*  \brief Polls the mouse.
	*  \param event The event to be polled.
	*/
	static void pollEvents(sf::Event& event);

	/**
	*  \brief Gets the state of one of the attributes of the mouse.
	*  \param state The state of the mouse you want, denoted by MOUSE_STATE.
	*  \param setting A special setting you want, such as MOUSE_SETTING.
	*  \return int The value of the state.
	*/
	static int getMouseState(MOUSE_STATE state, MOUSE_SETTING setting = MOUSE_SETTING::NONE);

private:
	/**
	*  \brief Updates the value of the mouse states.
	*/
	static void updateMouse();

	/**
	*  \brief Gets the state of one of the attributes of the mouse.
	*  \param current The current value of the state.
	*  \param past The past value of the state.
	*  \param setting A special setting you want, such by MOUSE_SETTING.
	*  \return int The value of the state after a setting has been applied.
	*/
	static int applyMouseSetting(MOUSE_STATE current, MOUSE_STATE past, MOUSE_SETTING setting);

private:
	// A vector of integers that denote the mouse information.
	static std::vector<int> mouseStates;

	static std::shared_ptr<sf::RenderWindow> window;

};
