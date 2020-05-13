#pragma once
#include "RobotC.h"
#include <SFML/Graphics.hpp>
#include <Debug/Debug.h>
#include <imgui.h>
#include <imgui-SFML.h>
std::array<int, 10> motor;

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

	static void Update() {

		ImGui::Begin("Robot Info");

		toText("Port 1: ", motor[port1]);
		toText("FPS: ", Debug::getFps());

		ImGui::End();
	};
};