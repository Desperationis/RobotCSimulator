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
#include "WindowObject.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "RobotC.h"

using namespace RobotC::Types;
using namespace RobotC::Peripherals;

/**
 * Displays the values of peripherals using ImGui.
 * Motor, sensor, and vexRT values are included.
 */
struct PeripheralTable : public WindowObject {
	PeripheralTable() = default;

	/**
	 * Template function to increment a continous 
	 * enumeration. Can fail when enumeration isn't 
	 * continous (e.x. enum1 = 0, enum2 = 1, enum 3 = 5)
	 * 
	 * \param enumeration - An enumeration, of any kind!
	 * \return The next enumeration.
	 */
	template <class T>
	T IncrementEnum(T enumeration) const {
		int increment = static_cast<int>(enumeration) + 1;
		return static_cast<T>(increment);
	}

	void ShowMotorValues() const {
		// Iterate through all ports of MotorPort
		for (MotorPort index = port1; index != MAX_MOTOR_PORT; index = IncrementEnum(index)) {
			byte portValue = motor[index];
			const char* portName = motorPortMap[index];
			ImGui::Text("%s: %i", portName, portValue);
		}
	}

	void ShowSensorValues() const {
		// Iterate through all ports of SensorPort
		for (SensorPort index = dgtl1; index != MAX_SENSOR_PORT; index = IncrementEnum(index)) {
			int16_t portValue = SensorValue[index];
			const char* portName = sensorPortMap[index];
			ImGui::Text("%s: %i", portName, portValue);
		}
	}

	void ShowRTValues() const {
		// Iterate through all ports of vexRT
		for (VexRT index = Btn5U; index != MAX_VEX_RT_PORT; index = IncrementEnum(index)) {
			byte portValue = vexRT[index];
			const char* portName = vexRTPortMap[index];
			ImGui::Text("%s: %i", portName, portValue);
		}
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		
		// Make the GUI window.
		ImGui::Begin("Peripherals");

		// Start a 3-column table.
		ImGui::Text("Peripheral Values:");
		ImGui::Columns(3, "mycolumns3");
		ImGui::Separator();

		// Fill the first row with titles.
		ImGui::Text("motor[]");
		ImGui::NextColumn();
		ImGui::Text("SensorValue[]");
		ImGui::NextColumn();
		ImGui::Text("vexRT[]");
		ImGui::NextColumn();

		// Add a separator between the data and titles.
		ImGui::Separator();

		// Fill in each column with port values.
		ShowMotorValues();
		ImGui::NextColumn();

		ShowSensorValues();
		ImGui::NextColumn();

		ShowRTValues();
		ImGui::NextColumn();

		// End the window.
		ImGui::End();

	}
};