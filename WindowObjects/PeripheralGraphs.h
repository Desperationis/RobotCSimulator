/*****************************************************************//**
 * \file   PeripheralGraphs.h
 * \brief  Displays the graphs of peripherals.
 * 
 * \author smart
 * \date   July 2020
 *********************************************************************/
#pragma once
#include <SFML/Graphics.hpp>
#include "../stdafx.h"
#include "../RobotC.h"
#include "WindowObject.h"
#include "ImGuiGraph.h"

using namespace RobotC::Types;
using namespace RobotC::Functions;

/**
 * Displays the graphs of peripherals in a value vs frame format.
 */
class PeripheralGraphs : public WindowObject {
public:

	struct MotorGraph {
		MotorGraph() = default;
		std::unique_ptr<ImGuiGraph> graph;
		MotorInfo info;
	};

	struct SensorGraph {
		SensorGraph() = default;
		std::unique_ptr<ImGuiGraph> graph;
		SensorInfo info;
	};

	PeripheralGraphs() {
		int maxSize = 800;
		sf::Vector2f range(-100, 100);
		sf::Vector2f size(100, 100);

		// Make motor graphs that are configured.
		for (unsigned int port = port1; port != MAX_MOTOR_PORT; port++) {
			
			if(motorConfigInfo.find((MotorPort)port) != motorConfigInfo.end()) {
				
				std::shared_ptr<MotorGraph> motorGraph = std::make_shared<MotorGraph>();
				motorGraph->info = motorConfigInfo[(MotorPort)port];
				if(motorGraph->info.reversed) {
					motorGraph->info.name += " (reversed)";
				}
				motorGraph->graph = std::make_unique<ImGuiGraph>(motorGraph->info.name.c_str(), maxSize, range, size);
				motorGraphs.push_back(motorGraph);
			}

		}

		size = sf::Vector2f (100, 800);
		range = sf::Vector2f(-32768, 32768);

		// Make sensor graphs that are configured.
		for (unsigned int port = dgtl1; port != MAX_SENSOR_PORT; port++) {

			if (sensorConfigInfo.find((SensorPort)port) != sensorConfigInfo.end()) {

				std::shared_ptr<SensorGraph> sensorGraph = std::make_shared<SensorGraph>();
				sensorGraph->info = sensorConfigInfo[(SensorPort)port];
				sensorGraph->graph = std::make_unique<ImGuiGraph>(sensorGraph->info.name.c_str(), maxSize, range, size);
				sensorGraphs.push_back(sensorGraph);
			}

		}
	}

	/**
	 * Updates the values of the graphs.
	 */
	void Update() {
		// Update the values of the motor graph.
		for (int i = 0; i < motorGraphs.size(); i++) {
			std::shared_ptr<MotorGraph> motorGraph = motorGraphs[i];
			MotorPort port = motorGraph->info.motorPort;
			int reversed = motorGraph->info.reversed ? -1 : 1;
			motorGraph->graph->PushValue(motor[port] * reversed);
		}

		// Update the values of the sensor graph.
		for (int i = 0; i < sensorGraphs.size(); i++) {
			std::shared_ptr<SensorGraph> sensorGraph = sensorGraphs[i];
			SensorPort port = sensorGraph->info.sensorPort;
			sensorGraph->graph->PushValue(SensorValue[port]);
		}
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		ImGui::Begin("Peripheral Graphs");

		ImGui::SetNextItemOpen(true);
		if(ImGui::TreeNode("Motor Graphs")) {
			// Put motorGraphs into 2 seperate columns.
			ImGui::Columns(2);
			for(int i = 0; i < motorGraphs.size(); i++) {
				motorGraphs[i]->graph->SetDimensions(sf::Vector2f(ImGui::GetColumnWidth(), 100));
				motorGraphs[i]->graph->DrawGraph();

				ImGui::NextColumn();
			}
			ImGui::TreePop();
		}
		ImGui::Columns(1);

		if (ImGui::TreeNode("Sensor Graphs")) {
			// Put sensorGraphs into 2 seperate columns.
			ImGui::Columns(2);
			for (int i = 0; i < sensorGraphs.size(); i++) {
				sensorGraphs[i]->graph->SetDimensions(sf::Vector2f(ImGui::GetColumnWidth(), 800));
				sensorGraphs[i]->graph->DrawGraph();
				ImGui::NextColumn();
			}
			ImGui::TreePop();
		}

		ImGui::End();
	}


private:
	std::vector<std::shared_ptr<MotorGraph>> motorGraphs;
	std::vector<std::shared_ptr<SensorGraph>> sensorGraphs;
};