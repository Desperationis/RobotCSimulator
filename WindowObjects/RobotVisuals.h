/*****************************************************************//**
 * \file   RobotVisuals.h
 * \brief  Displays the innerworkings of a Robot.h instance via drawing stuff.
 *
 * \author smart
 * \date   July 2020
 *********************************************************************/
#pragma once
#include "../stdafx.h"
#include <SFML/Graphics.hpp>
#include "WindowObject.h"
#include "Robot.h"

/**
 * Shows the user how a Robot.h object works by drawing 
 * shapes representing stuff, such as the ICC.
 */
class RobotVisuals : public WindowObject {
public:
	RobotVisuals(std::shared_ptr<Robot> robot) {
		this->robot = robot;
		ICC.setRadius(2.0f);
		ICC.setOrigin(sf::Vector2f(2.0f, 2.0f));
		ICC.setFillColor(sf::Color::Red);
	};

	void Update() override {
		auto robotPtr = robot.lock();
		
		if(robotPtr) {
			if (robotPtr->renderICC) {
				ICC.setPosition(robotPtr->ICCPosition);
			}
		}
		else if (!error) {
			printf("RobotVisuals.h: Not connected to robot. Check if a pointer to it exists.\n");
			error = true;
		}
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		auto robotPtr = robot.lock();

		if (robotPtr) {
			if (robotPtr->renderICC) {
				target.draw(ICC);
			}
		}
	}

private:
	sf::CircleShape ICC;
	std::weak_ptr<Robot> robot;
	bool error = false;
};