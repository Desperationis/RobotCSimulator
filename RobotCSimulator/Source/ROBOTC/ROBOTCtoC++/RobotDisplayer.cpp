#include "RobotDisplayer.h"
#include <SFML/Graphics.hpp>
#include <ImGuiWrapper/ImGuiWrapper.h>
#include <imgui.h>
#include <imgui-SFML.h>

std::vector<std::deque<float>> RobotDisplayer::motorValues;

RobotDisplayer::RobotDisplayer() {
	// Initialize all motor plot graphs.
	for (int i = 0; i < 10; i++) {
		motorValues.push_back(std::deque<float>());
	}
}

void RobotDisplayer::Update() {
	DisplayMotorGraphs();
	DisplayMotorValues();
	DisplayControllerValues();
	DisplaySensorValues();
};

void RobotDisplayer::DisplayMotorValues() {
	ImGui::Begin("Motor Info");

	// Update Motor Ports.
	for (int i = 0; i < motor.max_size(); i++) {
		if (Cortex::motorInfo[i]->name != "<none>") {
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

			toText("Port " + std::to_string(i) + " " + direction + Cortex::motorInfo[i]->name + ": ", motor[i] * isReversed((MotorPort)i));
		}
	}

	ImGui::End();
}

void RobotDisplayer::DisplayControllerValues() {
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

void RobotDisplayer::DisplayMotorGraphs() {
	ImGui::Begin("Motor Graphs");

	for (int i = 0; i < 10; i++) {
		// Only display motor values that are being used.
		if (Cortex::motorInfo[i]->name != "<none>") {

			// Push back current motor value
			motorValues[i].push_back(motor[i]);

			// Limit its size.
			if (motorValues[i].size() > 400) {
				motorValues[i].pop_front();
			}

			// ImGUI buffer.
			float motorValue[400];
			for (int j = 0; j < motorValues[i].size(); j++) {
				motorValue[j] = motorValues[i][j];
			}

			ImGui::PlotLines(Cortex::motorInfo[i]->name.c_str(), motorValue, IM_ARRAYSIZE(motorValue), 0, (const char*)0, -127, 127, ImVec2(400, 200));
		}
	}
	ImGui::End();
}

void RobotDisplayer::DisplaySensorValues() {
	ImGui::Begin("Sensor Info");

	for (int i = 0; i < Cortex::sensorInfo.max_size(); i++) {
		if (Cortex::sensorInfo[i]->name != "<none>") {
			toText(Cortex::sensorInfo[i]->name + ": ", floor(SensorValue[i]));
		}
	}

	ImGui::End();
}
