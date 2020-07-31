/*****************************************************************//**
 * \file   RobotTable.h
 * \brief  Displays the variables of a Robot.h instance.
 *
 * \author smart
 * \date   July 2020
 *********************************************************************/
#pragma once
#include <SFML/Graphics.hpp>
#include "../stdafx.h"
#include "WindowObject.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Robot.h"

/**
 * Displays the variables of a Robot.h instance by drawing their 
 * values in a ImGui window.
 */
class RobotTable : public WindowObject {
public:
	RobotTable(std::shared_ptr<Robot> robot) {
		this->robot = robot;
	};

	void ImGuiDraw() override {
		const auto delta = DeltaClock::GetDelta();
		const auto robotPtr = robot.lock();
		ImGui::Begin("Robot");

		if(robotPtr) {

			char buffer[20];
			sprintf_s(buffer, "Speed (px / s): %i", robotPtr->speed);
			ImGui::SliderInt(buffer, &robotPtr->speed, 1, 300);
			ImGui::Text("Position x (px): %g", robotPtr->getPosition().x);
			ImGui::Text("Position y (px): %g", robotPtr->getPosition().y);
			ImGui::Text("Angle (degrees): %g", robotPtr->getRotation());
			ImGui::Text("Velocity (px/s): %g", sqrt(pow(robotPtr->velocity.x, 2) + pow(robotPtr->velocity.y, 2)) / delta);
			ImGui::Checkbox("Render ICC: ", &robotPtr->renderICC);
		}
		else {
			ImGui::Text("Robot not connected. Check if a pointer to it exists.");
		}

		ImGui::End();
	}


private:
	std::weak_ptr<Robot> robot;
};