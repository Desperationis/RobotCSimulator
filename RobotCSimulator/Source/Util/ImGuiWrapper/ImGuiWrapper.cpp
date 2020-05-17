#include "ImGuiWrapper.h"

std::shared_ptr<sf::RenderWindow> ImGuiWrapper::window;
sf::Clock ImGuiWrapper::deltaTime;
sf::Clock ImGuiWrapper::fpsTime;
unsigned int ImGuiWrapper::countedFrames;


ImGuiWrapper::ImGuiWrapper(std::shared_ptr<sf::RenderWindow> window) {
	ImGui::SFML::Init(*window);
	this->window = window;
};

void ImGuiWrapper::PollEvents(sf::Event& event) {
	ImGui::SFML::ProcessEvent(event);
};

void ImGuiWrapper::Update() {
	// reset average FPS timer every 3 seconds to give precise results
	countedFrames++;
	if (fpsTime.getElapsedTime().asMilliseconds() > 3000) {
		countedFrames = 0;
		fpsTime.restart();
	}

	ImGui::SFML::Update(*window, deltaTime.restart());
};

void ImGuiWrapper::Render() {
	ImGui::SFML::Render(*window);
};

std::string ImGuiWrapper::IntToStr(int integer) {
	std::stringstream buf; buf << integer;
	return buf.str();
}