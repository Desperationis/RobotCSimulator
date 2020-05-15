#pragma once
#include "RobotC.h"
#include <SFML/Graphics.hpp>
#include <Debug/ImGuiWrapper.h>
#include <imgui.h>
#include <imgui-SFML.h>
#include <deque>

/*
 * RobotDisplayer.h
 *
 * Displays the value of robot motor values, sensor values, ect.
*/

class RobotDisplayer {
public:
	template<class T>
	static std::string toStr(T arg) {
		std::stringstream buf;
		buf << arg;

		return buf.str();
	}

	template<typename T>
	static void toText(std::string label, T value) {
		std::string form = label + toStr(value);
		ImGui::Text(form.c_str());
	}

	static int isReversed(MotorPort motor) {
		if (motorReversed[motor]) {
			return -1;
		}
		return 1;
	}

	static std::deque<float> motorQueue;

	static void Update() {
		ImGui::Begin("Left Motor Info");

		motorQueue.push_back(motor[port1]);

		if (motorQueue.size() > 400) {
			motorQueue.pop_front();
		}

		float motorValue[400];

		for (int i = 0; i < motorQueue.size(); i ++ ) {
			motorValue[i] = motorQueue[i];
		}

		ImGui::PlotLines("Motor Value", motorValue, IM_ARRAYSIZE(motorValue), 0, (const char*)0, -127, 127,ImVec2(600,200));


		ImGui::End();










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

			toText(direction + motorName[i] + ": ", motor[i] * isReversed((MotorPort)i));
		}

		ImGui::End();

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
	};
};

std::deque<float> RobotDisplayer::motorQueue;