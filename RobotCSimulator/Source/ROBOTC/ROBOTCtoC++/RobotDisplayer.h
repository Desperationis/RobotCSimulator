#pragma once
#include "RobotC.h"
#include <deque>
#include <vector>
#include <sstream>

/*
 * RobotDisplayer.h
 *
 * Displays the value of robot motor values, sensor values, ect. in ImGui.
*/

class RobotDisplayer {
public:
	RobotDisplayer();

	static void Update();

private:
	static std::vector<std::deque<float>> motorValues;

	static void DisplayMotorValues();

	static void DisplayControllerValues();

	static void DisplayMotorGraphs();

	static void DisplaySensorValues();



	// Template Functions
	template<class T>
	static std::string toStr(T arg) {
		// Converts a generic argument into a string.
		std::stringstream buf;
		buf << arg;

		return buf.str();
	}

	template<typename T>
	static void toText(std::string label, T value) {
		// Conjoins string and value together in ImGui and displays it.
		std::string form = label + toStr(value);
		ImGui::Text(form.c_str());
	}

	static int isReversed(MotorPort motor) {
		// Returns a positive-negative based integer.
		if (motorInfo[motor]->reversed) {
			return -1;
		}
		return 1;
	}
};