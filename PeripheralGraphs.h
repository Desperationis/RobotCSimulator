/*****************************************************************//**
 * \file   PeripheralGraphs.h
 * \brief  Displays the graphs of peripherals.
 * 
 * \author smart
 * \date   July 2020
 *********************************************************************/
#pragma once
#include <SFML/Graphics.hpp>
#include "stdafx.h"
#include "WindowObject.h"
#include "RobotC.h"
#include "ImGuiGraph.h"

using namespace RobotC::Types;
using namespace RobotC::Functions;

/**
 * Displays the graphs of peripherals in a value
 * vs frame format.
 */
class PeripheralGraphs : public WindowObject {
public:
	PeripheralGraphs() {
		int maxSize = 800;
		sf::Vector2f range(-100, 100);
		sf::Vector2f size(100, 100);

		for (MotorPort port = port1; port != MAX_MOTOR_PORT; port = IncrementEnum(port)) {
			// Make a new ImGuiGraph, with the current motor name, maxSize, range, and canvas size.
			const char* motorName = motorPortMap[port];
			motorGraphs.push_back(std::make_unique<ImGuiGraph>(motorName, maxSize, range, size));
		}
	}

	/**
	 * Updates the values of the graphs.
	 */
	void Update() {
		
		// Update the values of the motor graph.
		for (int i = 0; i < motorGraphs.size(); i++) {

			// Only update if the motor is actually configured
			if(motorConfigInfo.find((MotorPort)i) != motorConfigInfo.end()) {
				motorGraphs[i]->AddValue(motor[i]);
				motorGraphs[i]->Update();
			}

		}
	
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		ImGui::Begin("Peripheral Graphs");

		if(ImGui::TreeNode("Motor Graphs")) {
			// Put motorGraphs into 3 seperate columns.
			ImGui::Columns(3);
			for(int i = 0; i < motorGraphs.size(); i++) {
				motorGraphs[i]->SetSize(sf::Vector2f(ImGui::GetColumnWidth(), 100));
				motorGraphs[i]->DrawGraph();

				if ((i + 1) % 3 == 0) {
					ImGui::NextColumn();
				}
			}
			ImGui::TreePop();
		}



		ImGui::Columns(1);

		ImGui::End();
	}


private:

	std::vector<std::unique_ptr<ImGuiGraph>> motorGraphs;


};