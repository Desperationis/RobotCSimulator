#include "MouseInput.h"

std::vector<int> MouseInput::mouseStates;
std::shared_ptr<sf::RenderWindow> MouseInput::window;

MouseInput::MouseInput(std::shared_ptr<sf::RenderWindow> window) {
	this->window = window;
	for (int i = 0; i < 20; i++) {
		mouseStates.push_back(0);
	}
}

void MouseInput::pollEvents(sf::Event& event) {
	switch (event.type) {
	case sf::Event::MouseWheelScrolled:
		mouseStates[MOUSE_STATE::SCROLL] = static_cast<int>(event.mouseWheelScroll.delta);
		break;
	}
	updateMouse();
}

int MouseInput::getMouseState(MOUSE_STATE state, MOUSE_SETTING setting) {
	switch (state) {
	case MOUSE_STATE::LEFT:
		return applyMouseSetting(MOUSE_STATE::LEFT, MOUSE_STATE::P_LEFT, setting);
		break;
	case MOUSE_STATE::MIDDLE:
		return applyMouseSetting(MOUSE_STATE::MIDDLE, MOUSE_STATE::P_MIDDLE, setting);
		break;
	case MOUSE_STATE::RIGHT:
		return applyMouseSetting(MOUSE_STATE::RIGHT, MOUSE_STATE::P_RIGHT, setting);
		break;
	case MOUSE_STATE::X:
		return mouseStates[MOUSE_STATE::X];
		break;
	case MOUSE_STATE::Y:
		return mouseStates[MOUSE_STATE::Y];
		break;
	case MOUSE_STATE::SCROLL:
		return mouseStates[MOUSE_STATE::SCROLL];
		break;
	default:
		return -69420;
		break;
	}
};

int MouseInput::applyMouseSetting(MOUSE_STATE current, MOUSE_STATE past, MOUSE_SETTING setting) {
	// Applies a special "rule" to the value of a state, and returns an int accrodingly.
	if (setting == MOUSE_SETTING::ONE_FRAME_CLICK) {
		return mouseStates[current] && !mouseStates[past];
	}
	return mouseStates[current];
};

void MouseInput::updateMouse() {
	// reset scroll counter
	mouseStates[MOUSE_STATE::SCROLL] = 0;

	// get current position
	mouseStates[MOUSE_STATE::X] = sf::Mouse::getPosition(*window).x;
	mouseStates[MOUSE_STATE::Y] = sf::Mouse::getPosition(*window).y;

	// get past button presses
	mouseStates[MOUSE_STATE::P_LEFT] = mouseStates[MOUSE_STATE::LEFT];
	mouseStates[MOUSE_STATE::P_RIGHT] = mouseStates[MOUSE_STATE::RIGHT];
	mouseStates[MOUSE_STATE::P_MIDDLE] = mouseStates[MOUSE_STATE::MIDDLE];

	// get current button presses
	mouseStates[MOUSE_STATE::LEFT] = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	mouseStates[MOUSE_STATE::RIGHT] = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
	mouseStates[MOUSE_STATE::MIDDLE] = sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle);
};