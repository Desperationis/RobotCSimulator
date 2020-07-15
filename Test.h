#pragma once
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

struct Test : public sf::Drawable {
	Test() = default;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {

		ImGui::Begin("Test");
		ImGui::Text("HIIII");
		ImGui::End();

	}
};