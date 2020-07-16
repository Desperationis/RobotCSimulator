/*****************************************************************//**
 * \file   ImGuiGraph.h
 * \brief  A Wrapper for ImGui's PlotLines.
 * 
 * \author smart
 * \date   July 2020
 *********************************************************************/
#pragma once
#include "stdafx.h"
#include "WindowObject.h"
#include "imgui.h"
#include "imgui-SFML.h"

/**
 * A wrapper for ImGui's PlotLines.
 */
class ImGuiGraph : public WindowObject {
public:
	/**
	 * Contructs the graph.
	 * 
	 * \param label - The label of the graph, shown in the top center of it.
	 * \param _maxSize - Maximum amount of points to be visible at any given time.
	 * \param range - The minimum and maximum range, given as a sf::Vector2f.
	 * \param size - The size of the graph, given as sf::Vector2f.
	 */
	ImGuiGraph(const char* label, int _maxSize, sf::Vector2f range, sf::Vector2f size) : maxSize(_maxSize) {
		this->label = label;
		this->range = range;
		SetSize(size);

		// Set all the deque's values to 0
		for (int i = 0; i < maxSize; i++) {
			graphValues.push_back(i);
		}
	}

	void SetSize(sf::Vector2f size) {
		if (size.x > 0 && size.y > 0) {
			this->size = size;
		}
		else {
			printf("ImGuiGraph.h: The size (%f, %f) had negative values!", size.x, size.y);
		}
	
	}


	/**
	 * Adds a float to the graph. Size will be held constant.
	 * 
	 * \param value - The float to be added to the graph.
	 */
	void AddValue(float value) {
		// Add value to deque.
		graphValues.push_back(value);

		// If it's too big, limit it's size.
		if (graphValues.size() > maxSize) {
			graphValues.pop_front();
		}
	}

	/**
	 * Copy the value of deque onto buffer.
	 */
	void Update() {
		for (int i = 0; i < graphValues.size(); i++) {
			buffer[i] = graphValues[i];
		}
	}

	/**
	 * Manually renders the graph once ImGui::Begin() is called.
	 */
	void DrawGraph() {
		ImGui::PlotLines("", buffer, maxSize, 0, label, range.x, range.y, size);
		//ImGui::PlotHistogram()
	}

private:
	/**
	 * Deque holding the actual values of the graph.
	 */
	std::deque<float> graphValues;

	/**
	 * Label of the graph.
	 */
	const char* label;

	/**
	 * Buffer ImGui uses to display the graph.
	 */
	float buffer[1000];

	/**
	 * Maximum size of the deque.
	 */
	const int maxSize;

	/**
	 * Range of values shown.
	 */
	sf::Vector2f range;


	/**
	 * Size of the graph, in pixels.
	 */
	ImVec2 size;
};