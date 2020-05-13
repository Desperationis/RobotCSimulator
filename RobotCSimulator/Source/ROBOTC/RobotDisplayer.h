#pragma once
#include "RobotC.h"
#include <SFML/Graphics.hpp>
#include <Debug/Debug.h>
#include <imgui.h>
#include <imgui-SFML.h>

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

	static void Update() {

		ImGui::Begin("Robot Info");

		// Update Motor Ports.
		for (int i = 0; i < 10; i++) {
			toText(motorName[i] + ": ", motor[i] * isReversed((MotorPort)i));
		}

		toText("FPS: ", Debug::getFps());

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
		
		toText("FPS: ", Debug::getFps());


		ImGui::End();
	};
};