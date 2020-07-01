#include "ImGuiWrapper.h"

std::shared_ptr<sf::RenderWindow> ImGuiWrapper::window;


ImGuiWrapper::ImGuiWrapper(std::shared_ptr<sf::RenderWindow> window) {
	ImGui::SFML::Init(*window);
	this->window = window;
};

void ImGuiWrapper::PollEvents(sf::Event& event) {
	ImGui::SFML::ProcessEvent(event);
};

void ImGuiWrapper::Update() {
	ImGui::SFML::Update(*window, DeltaClock::GetTime());
};

void ImGuiWrapper::Render() {
	ImGui::SFML::Render(*window);
};