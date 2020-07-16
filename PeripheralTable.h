/*****************************************************************//**
 * \file   PeripheralTable.h
 * \brief  Displays the values of peripherals.
 * 
 * \author smart
 * \date   July 2020
 *********************************************************************/
#pragma once
#include <SFML/Graphics.hpp>
#include "stdafx.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "RobotC.h"

using namespace RobotC::Peripherals;

/**
 * Displays the values of peripherals using ImGui.
 * Motor, sensor, and vexRT values are included.
 */
struct PeripheralTable : public sf::Drawable {
	PeripheralTable() = default;

	void ShowMotorValues() const {
		for (unsigned int index = 0; index < motor.size(); index++) {
			int motorValue = motor[index];
			ImGui::Text("Motor %i: %i", index, motorValue);
		}
	}

	void ShowSensorValues() const {
		for (unsigned int index = 0; index < SensorValue.size(); index++) {
			int sensorValue = SensorValue[index];
			ImGui::Text("Sensor %i: %i", index, sensorValue);
		}
	}

	void ShowRTValues() const {
		for (unsigned int index = 0; index < vexRT.size(); index++) {
			int rtValue = vexRT[index];
			ImGui::Text("vexRT %i: %i", index, rtValue);
		}
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {

		ImGui::Begin("Peripherals");
		ImGui::Text("Peripheral Values:");
		ImGui::Columns(3, "mycolumns3");  // 3-ways, with border
		ImGui::Separator();

		ImGui::Text("motor[]");
		ImGui::NextColumn();
		ImGui::Text("SensorValue[]");
		ImGui::NextColumn();
		ImGui::Text("vexRT[]");
		ImGui::NextColumn();
		ImGui::Separator();

		ShowMotorValues();
		ImGui::NextColumn();
		
		ShowSensorValues();
		ImGui::NextColumn();
		
		ShowRTValues();
		ImGui::NextColumn();


		ImGui::End();

	}
};