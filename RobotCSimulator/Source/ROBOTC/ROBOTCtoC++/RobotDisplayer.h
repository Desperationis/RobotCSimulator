#pragma once
#include "RobotC.h"
#include <SFML/Graphics.hpp>
#include <ImGuiWrapper/ImGuiWrapper.h>
#include <imgui.h>
#include <imgui-SFML.h>
#include <deque>
#include <vector>

/*
 * RobotDisplayer.h
 *
 * Displays the value of robot motor values, sensor values, ect.
*/

class RobotDisplayer {
public:
	static std::vector<std::deque<float>> motorQueue;

	RobotDisplayer() {
		// Initialize all motor plot graphs.
		for (int i = 0; i < 10; i++) {
			motorQueue.push_back(std::deque<float>());
		}
	}

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

	static void DisplayMotorValues() {
		ImGui::Begin("Robot Info");

		// Update Motor Ports.
		for (int i = 0; i < 10; i++) {
			std::string direction;

			if (motor[i] > 0) {
				direction = "(Forward) ";
			}
			else if (motor[i] < 0) {
				direction = "(Backward) ";
			}
			else if (motor[i] == 0) {
				direction = "(Still) ";
			}

			toText(direction + motorInfo[i]->name + ": ", motor[i] * isReversed((MotorPort)i));
		}

		ImGui::End();
	}

	static void DisplayControllerValues() {
		ImGui::Begin("Controller Info");

		toText("VexRT Btn 5U: ", vexRT[Btn5U]);
		toText("VexRT Btn 5D: ", vexRT[Btn5D]);
		toText("VexRT Btn 6U: ", vexRT[Btn6U]);
		toText("VexRT Btn 6D: ", vexRT[Btn6D]);
		toText("VexRT Btn 7U: ", vexRT[Btn7U]);
		toText("VexRT Btn 7D: ", vexRT[Btn7D]);
		toText("VexRT Btn 7L: ", vexRT[Btn7L]);
		toText("VexRT Btn 7R: ", vexRT[Btn7R]);
		toText("VexRT Btn 8U: ", vexRT[Btn8U]);
		toText("VexRT Btn 8D: ", vexRT[Btn8D]);
		toText("VexRT Btn 8L: ", vexRT[Btn8L]);
		toText("VexRT Btn 8R: ", vexRT[Btn8R]);
		toText("VexRT Ch 1: ", vexRT[Ch1]);
		toText("VexRT Ch 2: ", vexRT[Ch2]);
		toText("VexRT Ch 3: ", vexRT[Ch3]);
		toText("VexRT Ch 4: ", vexRT[Ch4]);

		ImGui::End();
	}

	static void DisplayMotorGraphs() {
		ImGui::Begin("Motor Graphs");

		for (int i = 0; i < 10; i++) {
			// Only display motor values that are being used.
			if (motorInfo[i]->name != "<none>") {

				// Push back current motor value
				motorQueue[i].push_back(motor[i]);

				// Limit its size.
				if (motorQueue[i].size() > 400) {
					motorQueue[i].pop_front();
				}

				// ImGUI buffer.
				float motorValue[400];
				for (int j = 0; j < motorQueue[i].size(); j++) {
					motorValue[j] = motorQueue[i][j];
				}

				ImGui::PlotLines(motorInfo[i]->name.c_str(), motorValue, IM_ARRAYSIZE(motorValue), 0, (const char*)0, -127, 127, ImVec2(600, 200));
			}
		}
		ImGui::End();
	}


	static void Update() {
		DisplayMotorGraphs();
		DisplayMotorValues();
		DisplayControllerValues();
	};
};

std::vector<std::deque<float>> RobotDisplayer::motorQueue;