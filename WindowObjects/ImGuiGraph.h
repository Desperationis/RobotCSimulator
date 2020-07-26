/*****************************************************************//**
 * \file   ImGuiGraph.h
 * \brief  A wrapper for ImGui::PlotLines.
 * 
 * \author smart
 * \date   July 2020
 *********************************************************************/
#pragma once
#include "../stdafx.h"
#include "WindowObject.h"
#include "imgui.h"
#include "imgui-SFML.h"

class ImGuiGraph : public WindowObject {
public:
	ImGuiGraph(std::string label, int maxPoints, sf::Vector2f range, sf::Vector2f dimensions) : MAX_POINTS(maxPoints), LABEL(label), RANGE(range) {
		SetDimensions(dimensions);

		for (int i = 0; i < MAX_POINTS; i++) {
			values.push_back(i);
		}
	}

	void SetDimensions(sf::Vector2f dimensions) {
		if (dimensions.x > 0 && dimensions.y > 0) {
			this->dimensions = dimensions;
		}
		else {
			printf("ImGuiGraph.h: The size (%f, %f) had negative values!", dimensions.x, dimensions.y);
		}
	}

	void PushValue(float value) {
		values.push_back(value);
		values.pop_front();

		for (int i = 0; i < values.size(); i++) {
			buffer[i] = values[i];
		}
	}

	/**
	 * Should be called after ImGui::Begin().
	 */
	void DrawGraph() {
		ImGui::PlotLines("", buffer, MAX_POINTS, 0, LABEL.c_str(), RANGE.x, RANGE.y, dimensions);
	}

private:
	const unsigned int MAX_POINTS;
	const std::string LABEL;
	const sf::Vector2f RANGE;
	float buffer[1000];

	std::deque<float> values;
	sf::Vector2f dimensions;
};